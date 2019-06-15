$NetBSD$

--- plugins/DebuggerCore/unix/netbsd/DebuggerCore.cpp.orig	2019-06-15 15:00:37.849568641 +0000
+++ plugins/DebuggerCore/unix/netbsd/DebuggerCore.cpp
@@ -0,0 +1,837 @@
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
+#include <sys/syscall.h>
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
+    osIs64Bit(true),
+    USER_CS_32(0x23),
+    USER_CS_64(0x33), // RPL 0 can't appear in user segment registers, so 0xfff8 is safe
+    USER_SS(0x2b) {
+	Posix::initialize();
+}
+
+//------------------------------------------------------------------------------
+// Name: has_extension
+// Desc:
+//------------------------------------------------------------------------------
+bool DebuggerCore::has_extension(quint64 ext) const {
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
+// Name: ptrace_set_options
+// Desc:
+//------------------------------------------------------------------------------
+Status DebuggerCore::ptrace_set_options(edb::pid_t pid) {
+	ptrace_event_t pe;
+
+	if (ptrace(PT_GET_EVENT_MASK, pid, &pe, sizeof(pe)) == -1)
+		goto fail;
+
+	pe.pe_set_event |= PTRACE_FORK;
+	pe.pe_set_event |= PTRACE_VFORK;
+	pe.pe_set_event |= PTRACE_VFORK_DONE;
+	pe.pe_set_event |= PTRACE_LWP_CREATE;
+	pe.pe_set_event |= PTRACE_LWP_EXIT;
+	pe.pe_set_event |= PTRACE_POSIX_SPAWN;
+
+	if (ptrace(PT_SET_EVENT_MASK, pid, &pe, sizeof(pe))==-1)
+		goto fail;
+
+	return Status::Ok;
+
+fail:
+	const char *const strError = strerror(errno);
+	qWarning() << "Unable to set ptrace options " << pid << ": PT_SET_EVENT_MASK failed:" << strError;
+	return Status(strError);
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::monitor_sigtrap(edb::pid_t pid) {
+	ptrace_state_t pst;
+	ptrace_siginfo_t psi;
+	lwpid_t lid;
+	int status;
+
+	ptrace(PT_GET_SIGINFO, pid, &psi, sizeof(psi));
+
+	lid = psi.psi_lwpid;
+
+	switch (psi.psi_siginfo.si_code) {
+	case TRAP_DBREG:
+		return handle_debugregister(pid, lid);
+
+	case TRAP_TRACE:
+		return handle_singlestep(pid, lid);
+ 
+	case TRAP_BRKPT:
+		return handle_breakpoint(pid, lid);
+
+	case TRAP_SCE:
+		return handle_syscallentry(pid, lid, &psi.psi_siginfo);
+
+	case TRAP_SCX:
+		return handle_syscallexit(pid, lid, &psi.psi_siginfo);
+
+	case TRAP_EXEC:
+		return handle_exec(pid, lid);
+
+	case TRAP_LWP:
+		/* FALLTHROUGH */
+	case TRAP_CHLD:
+		ptrace(PT_GET_PROCESS_STATE, pid, &pst, sizeof(pst));
+		switch (pst.pe_report_event) {
+		case PTRACE_FORK:
+			return handle_forked(pid, lid, pst.pe_other_pid);
+
+		case PTRACE_VFORK:
+			return handle_vforked(pid, lid, pst.pe_other_pid);
+
+		case PTRACE_VFORK_DONE:
+			return handle_vforkdone(pid, lid, pst.pe_other_pid);
+
+		case PTRACE_LWP_CREATE:
+			return handle_lwpcreated(pid, lid, pst.pe_lwp);
+
+		case PTRACE_LWP_EXIT:
+			return handle_lwpexited(pid, lid, pst.pe_lwp);
+
+#if 0
+		case PTRACE_POSIX_SPAWN:
+			return handle_spawned(pid, lid, pst.pe_other_pid);
+#endif
+		}
+
+	default:
+		/* Fallback to regular crash/signal. */
+		if (psi.psi_siginfo.si_code <= SI_USER || 
+		    psi.psi_siginfo.si_code == SI_NOINFO) {
+			return handle_stopped(pid, lid, &psi.psi_siginfo);
+		} else {
+			return handle_crashed(pid, lid, &psi.psi_siginfo);
+		}
+	}
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::monitor_crash(edb::pid_t pid) {
+	ptrace_siginfo_t psi;
+	lwpid_t lid;
+
+	ptrace(PT_GET_SIGINFO, pid, &psi, sizeof(psi));
+ 
+	lid = psi.psi_lwpid;
+
+	if (psi.psi_siginfo.si_code <= SI_USER ||
+	    psi.psi_siginfo.si_code == SI_NOINFO) {
+		return handle_stopped(pid, lid, &psi.psi_siginfo);
+	} else {
+		return handle_crashed(pid, lid, &psi.psi_siginfo);
+	}
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::monitor_signal(edb::pid_t pid) {
+	ptrace_siginfo_t psi;
+	lwpid_t lid;
+
+	ptrace(PT_GET_SIGINFO, pid, &psi, sizeof(psi));
+ 
+	lid = psi.psi_lwpid;
+
+	return handle_stopped(pid, lid, &psi.psi_siginfo);
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_continued(edb::pid_t pid) {
+
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::monitor_signaled(edb::pid_t pid, int sig, int core) {
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_exited(edb::pid_t pid, int status) {
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_debugregister(edb::pid_t pid, edb::tid_t lid) {
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_singlestep(edb::pid_t pid, edb::tid_t lid) {
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_breakpoint(edb::pid_t pid, edb::tid_t lid) {
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_syscallentry(edb::pid_t pid, edb::tid_t lid, siginfo_t *si) {
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_syscallexit(edb::pid_t pid, edb::tid_t lid, siginfo_t *si) {
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_exec(edb::pid_t pid, edb::tid_t lid) {
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_forked(edb::pid_t pid, edb::tid_t lid, edb::pid_t child) {
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_vforked(edb::pid_t pid, edb::tid_t lid, edb::pid_t child) {
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_vforkdone(edb::pid_t pid, edb::tid_t lid, edb::pid_t child) {
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_lwpcreated(edb::pid_t pid, edb::tid_t lid, edb::tid_t lwp) {
+	auto newThread = std::make_shared<PlatformThread>(this, process_, lwp);
+
+	threads_.insert(lwp, newThread);
+
+#if 0
+	for (::size_t i = 0; i < 8; i++)
+		newThread->set_debug_register(i, old_thread->get_debug_register(i));
+#endif
+
+	ptrace(PT_CONTINUE, pid, (void *)1, 0);
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_lwpexited(edb::pid_t pid, edb::tid_t lid, edb::tid_t lwp) {
+	threads_.remove(lwp);
+
+	ptrace(PT_CONTINUE, pid, (void *)1, 0);
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_crashed(edb::pid_t pid, edb::tid_t lid, siginfo_t *si) {
+}
+
+//------------------------------------------------------------------------------
+// Name: monitor_sigtrap
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_stopped(edb::pid_t pid, edb::tid_t lid, siginfo_t *si) {
+}
+
+//------------------------------------------------------------------------------
+// Name: handle_event
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::handle_event(edb::pid_t pid, int status) {
+	if (WIFSTOPPED(status)) {
+		switch (WSTOPSIG(status)) {
+		case SIGTRAP:
+			return monitor_sigtrap(pid);
+		case SIGSEGV:
+			/* FALLTHROUGH */
+		case SIGILL:
+			/* FALLTHROUGH */
+		case SIGFPE:
+			/* FALLTHROUGH */
+		case SIGBUS:
+			return monitor_crash(pid);
+		default:
+			return monitor_signal(pid);
+		}
+	}
+
+	if (WIFCONTINUED(status)) {
+		return handle_continued(pid);
+	}
+		
+	/* Tracee terminating event */
+	if (WIFSIGNALED(status)) {
+		return handle_signaled(pid, WTERMSIG(status), WCOREDUMP(status));
+	}
+
+	if (WIFEXITED(status)) {
+		return handle_exited(pid, status);
+	}
+}
+
+//------------------------------------------------------------------------------
+// Name: wait_debug_event
+// Desc: waits for a debug event, msecs is a timeout
+//       it will return nullptr if an error or timeout occurs
+//------------------------------------------------------------------------------
+std::shared_ptr<IDebugEvent> DebuggerCore::wait_debug_event(int msecs) {
+	if (process_) {
+		if (!Posix::wait_for_sigchld(msecs)) {
+			int status;
+			const edb::pid_t pid = Posix::waitpid(process_->pid(), &status, WNOHANG);
+			if (pid > 0) {
+				return handle_event(pid, status);
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
+		auto newThread = std::make_shared<PlatformThread>(this, process_, pl.pl_lwpid);
+		threads_.insert(pl.pl_lwpid, newThread);
+	}
+	if (rv == -1) {
+		process_ = nullptr;
+		return Status(std::strerror(lastErr));
+	}
+
+	active_thread_ = threads_.begin();
+	detectCPUMode();
+	return Status::Ok;
+}
+
+//------------------------------------------------------------------------------
+// Name: detach
+// Desc:
+//------------------------------------------------------------------------------
+Status DebuggerCore::detach() {
+	QString errorMessage;
+
+	if (process_) {
+		clear_breakpoints();
+
+		if (ptrace(PT_DETACH, process_->pid(), (void *)1, 0) == -1) {
+			const char *const error = strerror(errno);
+			errorMessage+=tr("Unable to detach from process %1: PTRACE_DETACH failed: %2\n").arg(process_->pid()).arg(error);
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
+	if (attached()) {
+		clear_breakpoints();
+
+		::kill(process_->pid(), SIGKILL);
+
+		pid_t ret;
+		while ((ret = Posix::waitpid(process_->pid(), nullptr, 0)) != process_->pid() && ret != -1);
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
+	end_debug_session();
+
+	lastMeansOfCapture = MeansOfCapture::Launch;
+
+	static constexpr std::size_t sharedMemSize = 4096;
+
+	void *const ptr = ::mmap(nullptr, sharedMemSize, PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);
+	const auto sharedMem = static_cast<QChar*>(ptr);
+
+	std::memset(ptr, 0, sharedMemSize);
+
+	pid_t pid = fork();
+	if (pid == -1) {
+		// error! for some reason we couldn't fork
+		reset();
+		return Status(tr("Failed to fork"));
+	}
+
+	if (pid == 0) {
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
+
+	reset();
+
+	int status;
+	const auto wpidRet = Posix::waitpid(pid, &status, __WALL);
+	const QString childError(sharedMem);
+
+	::munmap(sharedMem, sharedMemSize);
+
+	if (wpidRet == -1) {
+		return Status(tr("waitpid() failed: %1").arg(std::strerror(errno))+(childError.isEmpty()?"" : tr(".\nError returned by child:\n%1.").arg(childError)));
+	}
+
+	if(WIFEXITED(status)) {
+		return Status(tr("The child unexpectedly exited with code %1. Error returned by child:\n%2").arg(WEXITSTATUS(status)).arg(childError));
+	}
+
+	if(WIFSIGNALED(status)) {
+		return Status(tr("The child was unexpectedly killed by signal %1. Error returned by child:\n%2").arg(WTERMSIG(status)).arg(childError));
+	}
+
+	// This happens when exec failed, but just in case it's something another return some description.
+	if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGABRT) {
+		return Status(childError.isEmpty() ? tr("The child unexpectedly aborted") : childError);
+	}
+
+	// the very first event should be a STOP of type SIGTRAP
+	if (!WIFSTOPPED(status) || WSTOPSIG(status) != SIGTRAP) {
+		end_debug_session();
+		return Status(tr("First event after waitpid() should be a STOP of type SIGTRAP, but wasn't, instead status=0x%1")
+			.arg(status,0,16)+(childError.isEmpty() ? "" : tr(".\nError returned by child:\n%1.").arg(childError)));
+	}
+
+	const auto setoptStatus=ptrace_set_options(pid);
+	if(!setoptStatus) {
+		end_debug_session();
+		return Status(tr("[DebuggerCore] failed to set ptrace options: %1").arg(setoptStatus.error()));
+	}
+
+	// create the process
+	process_ = std::make_shared<PlatformProcess>(this, pid);
+
+	struct ptrace_lwpinfo pl;
+	pl.pl_lwpid = 0;
+	int rv;
+	while ((rv = ptrace (PT_LWPINFO, pid, (void *)&pl, sizeof(pl))) != -1 && pl.pl_lwpid != 0) {
+		auto newThread   = std::make_shared<PlatformThread>(this, process_, pl.pl_lwpid);
+		threads_.insert(pl.pl_lwpid, newThread);
+	}
+	if (rv == -1) {
+		process_ = nullptr;
+		return Status(std::strerror(lastErr));
+	}
+
+	active_thread_ = threads_.begin();
+	detectCPUMode();
+
+	return Status::Ok;
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
+	struct ::kinfo_proc2 *kp = NULL;
+	::size_t len = 0;
+
+	const int mib[] = { CTL_KERN, KERN_PROC2, KERN_PROC_ALL, 0, sizeof(*kp), 0 };
+
+	if (::sysctl(mib, __arraycount(mib), NULL, &len, NULL, 0) == -1)
+		return ret;
+
+	if (::reallocarr(&kp, len, sizeof(*kp)) != 0)
+		return ret;
+
+	if (::sysctl(mib, __arraycount(mib), NULL, &len, NULL, 0) == -1) {
+		::reallocarr(&kp, 0, 0);
+		return ret;
+	}
+
+	for (::size_t i = 0; i < len/sizeof(*kp); i++) {
+		ret.insert(pid, std::make_shared<PlatformProcess>(const_cast<DebuggerCore*>(this), kp[i].p_pid));
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
+	struct ::kinfo_proc2 kp;
+	::size_t len = sizeof(p);
+
+	const int mib[] = { CTL_KERN, KERN_PROC2, KERN_PROC_PID, pid, sizeof(kp), 1 };
+	if (::sysctl(mib, __arraycount(mib), &kp, &len, NULL, 0) == -1)
+		return 0;
+
+	return kp.p_ppid;
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc: Returns EDB's native CPU type
+//------------------------------------------------------------------------------
+quint64 DebuggerCore::cpu_type() const {
+	return edb::string_hash("x86-64");
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QString DebuggerCore::stack_pointer() const {
+	return "rsp";
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QString DebuggerCore::frame_pointer() const {
+	return "rbp";
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QString DebuggerCore::instruction_pointer() const {
+	return "rip";
+}
+
+//------------------------------------------------------------------------------
+// Name: flag_register
+// Desc: Returns the name of the flag register as a QString.
+//------------------------------------------------------------------------------
+QString DebuggerCore::flag_register() const {
+	return "rflags";
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
+	return 0x90;
+}
+
+}
