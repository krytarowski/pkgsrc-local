$NetBSD$

--- plugins/DebuggerCore/unix/netbsd/DebuggerCore.cpp.orig	2019-06-14 00:50:24.165432268 +0000
+++ plugins/DebuggerCore/unix/netbsd/DebuggerCore.cpp
@@ -0,0 +1,868 @@
+/*
+Copyright (C) 2006 - 2015 Evan Teran
+                          evan.teran@gmail.com
+
+This program is free software: you can redistribute it and/or modify
+it under the terms of the GNU General Public License as published by
+the Free Software Foundation, either version 2 of the License, or
+(at your option) any later version.
+
+This program is distributed in the hope that it will be useful,
+but WITHOUT ANY WARRANTY; without even the implied warranty of
+MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+GNU General Public License for more details.
+
+You should have received a copy of the GNU General Public License
+along with this program.  If not, see <http://www.gnu.org/licenses/>.
+*/
+
+
+// TODO(eteran): research usage of process_vm_readv, process_vm_writev
+
+#include "DebuggerCore.h"
+#include "Configuration.h"
+#include "DialogMemoryAccess.h"
+#include "edb.h"
+#include "FeatureDetect.h"
+#include "MemoryRegions.h"
+#include "PlatformCommon.h"
+#include "PlatformEvent.h"
+#include "PlatformProcess.h"
+#include "PlatformRegion.h"
+#include "PlatformState.h"
+#include "PlatformThread.h"
+#include "State.h"
+#include "string_hash.h"
+#include "Posix.h"
+#include "Unix.h"
+
+#include <QDebug>
+#include <QDir>
+#include <QSettings>
+
+#include <cerrno>
+#include <cstring>
+
+#include <cpuid.h>
+
+#include <sys/types.h>
+#include <sys/ptrace.h>
+#include <sys/mman.h>
+#include <sys/wait.h>
+#include <sys/syscall.h>   /* For SYS_xxx definitions */
+
+#include <unistd.h>
+
+namespace DebuggerCorePlugin {
+
+namespace {
+
+/**
+ * @brief disable_lazy_binding
+ */
+void disable_lazy_binding() {
+	if(setenv("LD_BIND_NOW", "1", true) == -1) {
+		perror("Failed to disable lazy binding");
+	}
+}
+
+//------------------------------------------------------------------------------
+// Name: is_numeric
+// Desc: returns true if the string only contains decimal digits
+//------------------------------------------------------------------------------
+bool is_numeric(const QString &s) {
+	for(QChar ch: s) {
+		if(!ch.isDigit()) {
+			return false;
+		}
+	}
+
+	return true;
+}
+
+}
+
+//------------------------------------------------------------------------------
+// Name: DebuggerCore
+// Desc: constructor
+//------------------------------------------------------------------------------
+DebuggerCore::DebuggerCore()
+    :
+    edbIsIn64BitSegment(true),
+    osIs64Bit(os64Bit(true),
+    USER_CS_32(0x23),
+    USER_CS_64(0x33), // RPL 0 can't appear in user segment registers, so 0xfff8 is safe
+    USER_SS(0x2b) {
+
+	Posix::initialize();
+
+	feature::detect_proc_access(&proc_mem_read_broken_, &proc_mem_write_broken_);
+}
+
+//------------------------------------------------------------------------------
+// Name: has_extension
+// Desc:
+//------------------------------------------------------------------------------
+bool DebuggerCore::has_extension(quint64 ext) const {
+	
+	Q_UNUSED(ext)
+	
+	static constexpr auto mmxHash = edb::string_hash("MMX");
+	static constexpr auto xmmHash = edb::string_hash("XMM");
+	static constexpr auto ymmHash = edb::string_hash("YMM");
+
+	if(ext == xmmHash || ext == mmxHash) {
+		return true;
+	}
+
+	quint32 eax;
+	quint32 ebx;
+	quint32 ecx;
+	quint32 edx;
+	__cpuid(1, eax, ebx, ecx, edx);
+
+	switch(ext) {
+	case mmxHash:
+		return (edx & bit_MMX);
+	case xmmHash:
+		return (edx & bit_SSE);
+	case ymmHash:
+	{
+		// Check OSXSAVE and AVX feature flags
+		if((ecx & 0x18000000) != 0x18000000) {
+			return false;
+		}
+
+		// Get XCR0, must be exactly after OSXSAVE feature check, otherwise #UD
+		__asm__ __volatile__("xgetbv" : "=a"(eax),"=d"(edx) : "c"(0));
+
+		// Check that the OS has enabled XMM and YMM state support
+		if((eax & 0x6) != 0x6) {
+			return false;
+		}
+		return true;
+	}
+	default:
+		return false;
+	}
+}
+
+//------------------------------------------------------------------------------
+// Name: page_size
+// Desc: returns the size of a page on this system
+//------------------------------------------------------------------------------
+size_t DebuggerCore::page_size() const {
+	return sysconf(_SC_PAGESIZE);
+}
+
+std::size_t DebuggerCore::pointer_size() const {
+	return pointer_size_;
+}
+
+//------------------------------------------------------------------------------
+// Name: ~DebuggerCore
+// Desc: destructor
+//------------------------------------------------------------------------------
+DebuggerCore::~DebuggerCore() {
+	end_debug_session();
+}
+
+//------------------------------------------------------------------------------
+// Name: ptrace_traceme
+// Desc:
+//------------------------------------------------------------------------------
+long DebuggerCore::ptrace_traceme() {
+	return ptrace(PTRACE_TRACEME, 0, 0, 0);
+}
+
+//------------------------------------------------------------------------------
+// Name: ptrace_continue
+// Desc:
+//------------------------------------------------------------------------------
+Status DebuggerCore::ptrace_continue(edb::tid_t tid, long status) {
+	// TODO(eteran): perhaps address this at a higher layer?
+	//               I would like to not have these events show up
+	//               in the first place if we aren't stopped on this TID :-(
+	if(util::contains(waited_threads_, tid)) {
+		Q_ASSERT(tid != 0);
+		if(ptrace(PTRACE_CONT, tid, 0, status) == -1) {
+			const char *const strError = strerror(errno);
+			qWarning() << "Unable to continue thread" << tid << ": PTRACE_CONT failed:" << strError;
+			return Status(strError);
+		}
+		waited_threads_.remove(tid);
+		return Status::Ok;
+	}
+	return Status(tr("ptrace_continue(): waited_threads_ doesn't contain tid %1").arg(tid));
+}
+
+//------------------------------------------------------------------------------
+// Name: ptrace_step
+// Desc:
+//------------------------------------------------------------------------------
+Status DebuggerCore::ptrace_step(edb::tid_t tid, long status) {
+	// TODO(eteran): perhaps address this at a higher layer?
+	//               I would like to not have these events show up
+	//               in the first place if we aren't stopped on this TID :-(
+	if(util::contains(waited_threads_, tid)) {
+		Q_ASSERT(tid != 0);
+		if(ptrace(PTRACE_SINGLESTEP, tid, 0, status)==-1) {
+			const char *const strError = strerror(errno);
+			qWarning() << "Unable to step thread" << tid << ": PTRACE_SINGLESTEP failed:" << strError;
+			return Status(strError);
+		}
+		waited_threads_.remove(tid);
+		return Status::Ok;
+	}
+	return Status(tr("ptrace_step(): waited_threads_ doesn't contain tid %1").arg(tid));
+}
+
+//------------------------------------------------------------------------------
+// Name: ptrace_set_options
+// Desc:
+//------------------------------------------------------------------------------
+Status DebuggerCore::ptrace_set_options(edb::tid_t tid, ptrace_event_t pe) {
+	Q_ASSERT(tid != 0);	
+
+	if(ptrace(PT_SET_EVENT_MASK, tid, &pe, sizeof(pe))==-1) {
+		const char *const strError = strerror(errno);
+		qWarning() << "Unable to set ptrace options " << tid << ": PT_SET_EVENT_MASK failed:" << strError;
+		return Status(strError);
+	}
+	return Status::Ok;
+}
+
+//------------------------------------------------------------------------------
+// Name: ptrace_get_event_message
+// Desc:
+//------------------------------------------------------------------------------
+Status DebuggerCore::ptrace_get_event_message(edb::tid_t tid, unsigned long *message) {
+	Q_ASSERT(util::contains(waited_threads_, tid));
+	Q_ASSERT(tid != 0);
+	Q_ASSERT(message);
+
+	if(ptrace(PTRACE_GETEVENTMSG, tid, 0, message)==-1) {
+		const char *const strError = strerror(errno);
+		qWarning() << "Unable to get event message for thread" << tid << ": PTRACE_GETEVENTMSG failed:" << strError;
+		return Status(strError);
+	}
+	return Status::Ok;
+}
+
+//------------------------------------------------------------------------------
+// Name: desired_ptrace_options
+// Desc:
+//------------------------------------------------------------------------------
+ptrace_event_t DebuggerCore::ptraceOptions() const {
+    ptrace_event_t pe = {};
+
+    pe.pe_set_event |= PTRACE_FORK;
+    pe.pe_set_event |= PTRACE_VFORK;
+    pe.pe_set_event |= PTRACE_VFORK_DONE;
+    pe.pe_set_event |= PTRACE_LWP_CREATE;
+    pe.pe_set_event |= PTRACE_LWP_EXIT;
+    pe.pe_set_event |= PTRACE_POSIX_SPAWN;
+
+    return pe;
+}
+
+//------------------------------------------------------------------------------
+// Name: handle_thread_exit
+// Desc:
+//------------------------------------------------------------------------------
+void DebuggerCore::handle_thread_exit(edb::tid_t tid, int status) {
+	Q_UNUSED(status)
+
+	threads_.remove(tid);
+}
+
+//------------------------------------------------------------------------------
+// Name: handle_thread_create_event
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_thread_create_event(edb::tid_t tid, int status) {
+
+	Q_UNUSED(status)
+
+	unsigned long message;
+	if(ptrace_get_event_message(tid, &message)) {
+
+		auto new_tid = static_cast<edb::tid_t>(message);
+
+		auto newThread = std::make_shared<PlatformThread>(this, process_, new_tid);
+
+		threads_.insert(new_tid, newThread);
+
+		int thread_status = 0;
+		if(!util::contains(waited_threads_, new_tid)) {
+			if(Posix::waitpid(new_tid, &thread_status, __WALL) > 0) {
+				waited_threads_.insert(new_tid);
+			}
+		}
+
+		// A new thread could exit before we have fully created it, no event then since it can't be the last thread
+		if(WIFEXITED(thread_status)) {
+			handle_thread_exit(tid, thread_status);
+			return nullptr;
+		}
+
+		if(!WIFSTOPPED(thread_status) || WSTOPSIG(thread_status) != SIGSTOP) {
+			qWarning("handle_event(): new thread [%d] received an event besides SIGSTOP: status=0x%x", static_cast<int>(new_tid),thread_status);
+		}
+
+		newThread->status_ = thread_status;
+
+		// copy the hardware debug registers from the current thread to the new thread
+		if(process_) {
+			if(auto cur_thread = process_->current_thread()) {
+				for(size_t i = 0; i < 8; ++i) {
+					auto new_thread = std::static_pointer_cast<PlatformThread>(newThread);
+					auto old_thread = std::static_pointer_cast<PlatformThread>(cur_thread);
+					new_thread->set_debug_register(i, old_thread->get_debug_register(i));
+				}
+			}
+		}
+
+		newThread->resume();
+	}
+
+	ptrace_continue(tid, 0);
+	return nullptr;
+}
+
+//------------------------------------------------------------------------------
+// Name: handle_event
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_event(edb::tid_t tid, int status) {
+
+	// note that we have waited on this thread
+	waited_threads_.insert(tid);
+
+	// was it a thread exit event?
+	if(WIFEXITED(status)) {
+
+		handle_thread_exit(tid,status);
+		// if this was the last thread, return nullptr
+		// so we report it to the user.
+		// if this wasn't, then we should silently
+		// procceed.
+		if(!threads_.empty()) {
+			return nullptr;
+		}
+	}
+
+    if(is_exit_trace_event(status)) {
+
+    }
+
+	// was it a thread create event?
+	if(is_clone_event(status)) {
+		return handle_thread_create_event(tid, status);
+	}
+
+	// normal event
+	auto e = std::make_shared<PlatformEvent>();
+
+	e->pid_    = process_->pid();
+	e->tid_    = tid;
+	e->status_ = status;
+	if(!ptrace_getsiginfo(tid, &e->siginfo_)) {
+		// TODO: handle no info?
+	}
+
+	// if necessary, just ignore this event
+	if(util::contains(ignored_exceptions_, e->code())) {
+		ptrace_continue(tid, resume_code(status));
+	}
+
+	/* NOTE(eteran): OK, so when we get an event, we generally want to stop
+	 * any other threads as well. So we will call stop_threads() below
+	 * which sends a SIGSTOP.
+	 *
+	 * We need to be very careful to avoid those future events causing the
+	 * active thread to be set, because we want it to remain set to the thread
+	 * which recieved the initial signal. This is all so that later when the
+	 * user clicks resume, that the correct active thread gets (or doesn't)
+	 * get signals, and the rest get resumed properly.
+	 *
+	 * To do this, we simply only alter the active_thread_ variable if this
+	 * event was the first we saw after a resume/run (phew!).*/
+	if(waited_threads_.size() == 1) {
+		active_thread_ = tid;
+	}
+
+	auto it = threads_.find(tid);
+	if(it != threads_.end()) {
+		it.value()->status_ = status;
+	}
+
+	stop_threads();
+
+	// Some breakpoint types result in SIGILL or SIGSEGV. We'll transform the
+	// event into breakpoint event if such a breakpoint has triggered.
+	if(it != threads_.end() && WIFSTOPPED(status)) {
+		const auto signo = WSTOPSIG(status);
+		if(signo == SIGILL || signo == SIGSEGV) {
+			// no need to peekuser for SIGILL, but have to for SIGSEGV
+			const auto address = signo == SIGILL ? edb::address_t::fromZeroExtended(e->siginfo_.si_addr)
+											   : (*it)->instruction_pointer();
+
+			if(edb::v1::find_triggered_breakpoint(address)) {
+				e->status_ = SIGTRAP << 8 | 0x7f;
+				e->siginfo_.si_signo = SIGTRAP;
+				e->siginfo_.si_code  = TRAP_BRKPT;
+			}
+		}
+	}
+
+	return e;
+}
+
+//------------------------------------------------------------------------------
+// Name: wait_debug_event
+// Desc: waits for a debug event, msecs is a timeout
+//       it will return nullptr if an error or timeout occurs
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::wait_debug_event(int msecs) {
+
+	if(process_) {
+		if(!Posix::wait_for_sigchld(msecs)) {
+			for(auto &thread : process_->threads()) {
+				int status;
+				const edb::tid_t tid = Posix::waitpid(thread->tid(), &status, __WALL | WNOHANG);
+				if(tid > 0) {
+					return handle_event(tid, status);
+				}
+			}
+		}
+	}
+	return nullptr;
+}
+
+//------------------------------------------------------------------------------
+// Name: attach
+// Desc:
+//------------------------------------------------------------------------------
+Status DebuggerCore::attach(edb::pid_t pid) {
+
+	end_debug_session();
+
+	lastMeansOfCapture = MeansOfCapture::Attach;
+
+	// create this, so the threads created can refer to it
+	process_ = std::make_shared<PlatformProcess>(this, pid);
+
+	if (ptrace(PTRACE_ATTACH, pid, 0, 0) == -1) {
+		process_ = nullptr;
+		return Status(std::strerror(lastErr));
+	}
+
+	const int ret = Posix::waitpid(pid, &status, 0);
+	if (ret == -1) {
+		process_ = nullptr;
+		return Status(std::strerror(lastErr));
+	}
+
+	struct ptrace_lwpinfo pl;
+	pl.pl_lwpid = 0;
+	int rv;
+	while ((rv = ptrace (PT_LWPINFO, pid, (void *)&pl, sizeof(pl))) != -1 && pl.pl_lwpid != 0) {
+		auto newThread     = std::make_shared<PlatformThread>(this, process_, pl.pl_lwpid);
+		threads_.insert(tid, newThread);
+	}
+	if (rv == -1) {
+		process_ = nullptr;
+		return Status(std::strerror(lastErr));
+	}
+
+
+	active_thread_ = pid;
+	detectCPUMode();
+	return Status::Ok;
+}
+
+//------------------------------------------------------------------------------
+// Name: detach
+// Desc:
+//------------------------------------------------------------------------------
+Status DebuggerCore::detach() {
+
+	QString errorMessage;
+
+	if(process_) {
+		stop_threads();
+		clear_breakpoints();
+
+		for(auto &thread: process_->threads()) {
+			if(ptrace(PTRACE_DETACH, thread->tid(), 0, 0)==-1) {
+				const char *const error = strerror(errno);
+				errorMessage+=tr("Unable to detach from thread %1: PTRACE_DETACH failed: %2\n").arg(thread->tid()).arg(error);
+			}
+		}
+
+		process_ = nullptr;
+		reset();
+	}
+
+	if(errorMessage.isEmpty()) {
+		return Status::Ok;
+	}
+
+	qWarning() << errorMessage.toStdString().c_str();
+	return Status(errorMessage);
+}
+
+//------------------------------------------------------------------------------
+// Name: kill
+// Desc:
+//------------------------------------------------------------------------------
+void DebuggerCore::kill() {
+	if(attached()) {
+		clear_breakpoints();
+
+		::kill(process_->pid(), SIGKILL);
+
+		pid_t ret;
+		while((ret = Posix::waitpid(-1, nullptr, __WALL)) != process_->pid() && ret != -1);
+
+		process_ = nullptr;
+		reset();
+	}
+}
+
+void DebuggerCore::detectCPUMode() {
+	cpu_mode_ = CPUMode::x86_64;
+	CapstoneEDB::init(CapstoneEDB::Architecture::ARCH_AMD64);
+	pointer_size_ = sizeof(quint64);
+}
+
+//------------------------------------------------------------------------------
+// Name: open
+// Desc:
+//------------------------------------------------------------------------------
+Status DebuggerCore::open(const QString &path, const QString &cwd, const QList<QByteArray> &args, const QString &tty) {
+
+	end_debug_session();
+
+    lastMeansOfCapture = MeansOfCapture::Launch;
+
+	static constexpr std::size_t sharedMemSize = 4096;
+
+	void *const ptr = ::mmap(nullptr, sharedMemSize, PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);
+	const auto sharedMem = static_cast<QChar*>(ptr);
+
+	std::memset(ptr, 0, sharedMemSize);
+
+	switch(pid_t pid = fork()) {
+	case 0:
+	{
+		ptrace(PT_TRACE_ME, 0, NULL, 0);
+
+		// redirect it's I/O
+		if(!tty.isEmpty()) {
+			FILE *const std_out = freopen(qPrintable(tty), "r+b", stdout);
+			FILE *const std_in  = freopen(qPrintable(tty), "r+b", stdin);
+			FILE *const std_err = freopen(qPrintable(tty), "r+b", stderr);
+
+			Q_UNUSED(std_out)
+			Q_UNUSED(std_in)
+			Q_UNUSED(std_err)
+		}
+
+		if(edb::v1::config().disableLazyBinding) {
+			disable_lazy_binding();
+		}
+
+		// do the actual exec
+		const Status status = Unix::execute_process(path, cwd, args);
+
+		static_assert(std::is_trivially_copyable<QChar>::value, "Can't copy string of QChar to shared memory");
+		QString error = status.error();
+		std::memcpy(sharedMem, error.constData(), std::min(sizeof(QChar) * error.size(), sharedMemSize - sizeof(QChar) /*prevent overwriting of last null*/ ));
+
+		// we should never get here!
+		abort();
+	}
+	case -1:
+		// error! for some reason we couldn't fork
+		reset();
+		return Status(tr("Failed to fork"));
+	default:
+		// parent
+		do {
+			reset();
+
+			int status;
+			const auto wpidRet = Posix::waitpid(pid, &status, __WALL);
+			const QString childError(sharedMem);
+            ::munmap(sharedMem, sharedMemSize);
+
+            if(wpidRet == -1) {
+		return Status(tr("waitpid() failed: %1").arg(std::strerror(errno))+(childError.isEmpty()?"" : tr(".\nError returned by child:\n%1.").arg(childError)));
+            }
+
+            if(WIFEXITED(status)) {
+		return Status(tr("The child unexpectedly exited with code %1. Error returned by child:\n%2").arg(WEXITSTATUS(status)).arg(childError));
+            }
+
+            if(WIFSIGNALED(status)) {
+		return Status(tr("The child was unexpectedly killed by signal %1. Error returned by child:\n%2").arg(WTERMSIG(status)).arg(childError));
+            }
+
+			// This happens when exec failed, but just in case it's something another return some description.
+            if(WIFSTOPPED(status) && WSTOPSIG(status) == SIGABRT) {
+				return Status(childError.isEmpty() ? tr("The child unexpectedly aborted") : childError);
+            }
+
+			// the very first event should be a STOP of type SIGTRAP
+			if(!WIFSTOPPED(status) || WSTOPSIG(status) != SIGTRAP) {
+				end_debug_session();
+				return Status(tr("First event after waitpid() should be a STOP of type SIGTRAP, but wasn't, instead status=0x%1")
+					.arg(status,0,16)+(childError.isEmpty() ? "" : tr(".\nError returned by child:\n%1.").arg(childError)));
+			}
+
+            waited_threads_.insert(pid);
+
+            const long options = ptraceOptions();
+
+            // enable following clones (threads) and other options we are concerned with
+			const auto setoptStatus=ptrace_set_options(pid, options);
+            if(!setoptStatus) {
+                end_debug_session();
+		return Status(tr("[DebuggerCore] failed to set ptrace options: %1").arg(setoptStatus.error()));
+            }
+
+            // create the process
+			process_ = std::make_shared<PlatformProcess>(this, pid);
+
+			// the PID == primary TID
+			auto newThread     = std::make_shared<PlatformThread>(this, process_, pid);
+			newThread->status_ = status;
+
+			threads_.insert(pid, newThread);
+
+            active_thread_  = pid;
+			detectCPUMode();
+
+			return Status::Ok;
+		} while(0);
+		break;
+	}
+}
+
+
+//------------------------------------------------------------------------------
+// Name: last_means_of_capture
+// Desc: Returns how the last process was captured to debug
+//------------------------------------------------------------------------------
+DebuggerCore::MeansOfCapture DebuggerCore::last_means_of_capture() const {
+	return lastMeansOfCapture;
+}
+
+//------------------------------------------------------------------------------
+// Name: reset
+// Desc:
+//------------------------------------------------------------------------------
+void DebuggerCore::reset() {
+	threads_.clear();
+	waited_threads_.clear();
+	active_thread_ = 0;
+}
+
+//------------------------------------------------------------------------------
+// Name: create_state
+// Desc:
+//------------------------------------------------------------------------------
+std::unique_ptr<IState> DebuggerCore::create_state() const {
+	return std::make_unique<PlatformState>();
+}
+
+//------------------------------------------------------------------------------
+// Name: enumerate_processes
+// Desc:
+//------------------------------------------------------------------------------
+QMap<edb::pid_t, std::shared_ptr<IProcess>> DebuggerCore::enumerate_processes() const {
+	QMap<edb::pid_t, std::shared_ptr<IProcess>> ret;
+
+	QDir proc_directory("/proc/");
+	QFileInfoList entries = proc_directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
+
+	for(const QFileInfo &info: entries) {
+		const QString filename = info.fileName();
+		if(is_numeric(filename)) {
+			const edb::pid_t pid = filename.toInt();
+
+			// NOTE(eteran): the const_cast is reasonable here.
+			// While we don't want THIS function to mutate the DebuggerCore object
+			// we do want the associated PlatformProcess to be able to trigger
+			// non-const operations in the future, at least hypothetically.
+			ret.insert(pid, std::make_shared<PlatformProcess>(const_cast<DebuggerCore*>(this), pid));
+		}
+	}
+
+	return ret;
+}
+
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+edb::pid_t DebuggerCore::parent_pid(edb::pid_t pid) const {
+
+	struct user_stat user_stat;
+	int n = get_user_stat(pid, &user_stat);
+	if(n >= 4) {
+		return user_stat.ppid;
+	}
+
+	return 0;
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc: Returns EDB's native CPU type
+//------------------------------------------------------------------------------
+quint64 DebuggerCore::cpu_type() const {
+#if defined EDB_X86 || defined EDB_X86_64
+	if(EDB_IS_32_BIT) {
+		return edb::string_hash("x86");
+	} else {
+		return edb::string_hash("x86-64");
+	}
+#elif defined EDB_ARM32
+	return edb::string_hash("arm");
+#elif defined EDB_ARM64
+	return edb::string_hash("AArch64");
+#else
+    #error "Unsupported Architecture"
+#endif
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QString DebuggerCore::stack_pointer() const {
+#if defined EDB_X86 || defined EDB_X86_64
+	if(edb::v1::debuggeeIs32Bit()) {
+		return "esp";
+	} else {
+		return "rsp";
+	}
+#elif defined EDB_ARM32 || defined EDB_ARM64
+	return "sp";
+#else
+    #error "Unsupported Architecture"
+#endif
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QString DebuggerCore::frame_pointer() const {
+#if defined EDB_X86 || defined EDB_X86_64
+	if(edb::v1::debuggeeIs32Bit()) {
+		return "ebp";
+	} else {
+		return "rbp";
+	}
+#elif defined EDB_ARM32 || defined EDB_ARM64
+	return "fp";
+#else
+    #error "Unsupported Architecture"
+#endif
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QString DebuggerCore::instruction_pointer() const {
+#if defined EDB_X86 || defined EDB_X86_64
+	if(edb::v1::debuggeeIs32Bit()) {
+		return "eip";
+	} else {
+		return "rip";
+	}
+#elif defined EDB_ARM32 || defined EDB_ARM64
+	return "pc";
+#else
+    #error "Unsupported Architecture"
+#endif
+}
+
+//------------------------------------------------------------------------------
+// Name: flag_register
+// Desc: Returns the name of the flag register as a QString.
+//------------------------------------------------------------------------------
+QString DebuggerCore::flag_register() const {
+#if defined EDB_X86 || defined EDB_X86_64
+	if(edb::v1::debuggeeIs32Bit()) {
+		return "eflags";
+	} else {
+		return "rflags";
+	}
+#elif defined EDB_ARM32 || defined EDB_ARM64
+	return "cpsr";
+#else
+    #error "Unsupported Architecture"
+#endif
+}
+
+//------------------------------------------------------------------------------
+// Name: process
+// Desc:
+//------------------------------------------------------------------------------
+IProcess *DebuggerCore::process() const {
+	return process_.get();
+}
+
+//------------------------------------------------------------------------------
+// Name: set_ignored_exceptions
+// Desc:
+//------------------------------------------------------------------------------
+void DebuggerCore::set_ignored_exceptions(const QList<qlonglong> &exceptions) {
+	ignored_exceptions_ = exceptions;
+}
+
+/**
+ * @brief DebuggerCore::exceptions
+ * @return
+ */
+QMap<qlonglong, QString> DebuggerCore::exceptions() const {
+	return Unix::exceptions();
+}
+
+/**
+ * @brief DebuggerCore::exceptionName
+ * @param value
+ * @return
+ */
+QString DebuggerCore::exceptionName(qlonglong value) {
+	return Unix::exceptionName(value);
+}
+
+/**
+ * @brief DebuggerCore::exceptionValue
+ * @param name
+ * @return
+ */
+qlonglong DebuggerCore::exceptionValue(const QString &name) {
+	return Unix::exceptionValue(name);
+}
+
+uint8_t DebuggerCore::nopFillByte() const {
+#if defined EDB_X86 || defined EDB_X86_64
+	return 0x90;
+#elif defined EDB_ARM32 || defined EDB_ARM64
+	// TODO(eteran): does this concept even make sense for a multi-byte instruction encoding?
+	return 0x00;
+#else
+	#error "Unsupported Architecture"
+#endif
+}
+
+}
