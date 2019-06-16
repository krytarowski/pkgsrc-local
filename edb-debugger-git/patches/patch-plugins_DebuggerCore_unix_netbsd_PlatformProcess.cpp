$NetBSD$

--- plugins/DebuggerCore/unix/netbsd/PlatformProcess.cpp.orig	2019-06-16 01:25:12.514579410 +0000
+++ plugins/DebuggerCore/unix/netbsd/PlatformProcess.cpp
@@ -0,0 +1,952 @@
+/*
+Copyright (C) 2015 - 2015 Evan Teran
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
+#ifndef _LARGEFILE64_SOURCE
+#define _LARGEFILE64_SOURCE
+#endif
+
+#include "PlatformProcess.h"
+#include "DebuggerCore.h"
+#include "IBreakpoint.h"
+#include "PlatformThread.h"
+#include "PlatformCommon.h"
+#include "PlatformRegion.h"
+#include "ByteShiftArray.h"
+#include "MemoryRegions.h"
+#include "Module.h"
+#include "edb.h"
+#include "Util.h"
+#include "linker.h"
+#include "libELF/elf_binary.h"
+#include "libELF/elf_model.h"
+
+#include <QDebug>
+#include <QByteArray>
+#include <QFile>
+#include <QFileInfo>
+#include <QTextStream>
+#include <QDateTime>
+
+#include <boost/functional/hash.hpp>
+#include <fstream>
+
+#include <sys/param.h>
+#include <sys/types.h>
+#include <sys/mman.h>
+#include <sys/ptrace.h>
+#include <sys/sysctl.h>
+#include <unistd.h>
+#include <pwd.h>
+#include <elf.h>
+
+namespace DebuggerCorePlugin {
+namespace {
+
+// Used as size of ptrace word
+constexpr size_t EDB_WORDSIZE = sizeof(long);
+
+void set_ok(bool &ok, long value) {
+	ok = (value != -1) || (errno == 0);
+}
+
+QStringList split_max(const QString &str, int maxparts) {
+	int prev_idx = 0;
+	int idx = 0;
+	QStringList items;
+	for (const QChar &c : str) {
+		if (c == ' ') {
+			if (prev_idx < idx) {
+				if (items.size() < maxparts - 1)
+					items << str.mid(prev_idx, idx - prev_idx);
+				else {
+					items << str.right(str.size() - prev_idx);
+					break;
+				}
+			}
+			prev_idx = idx + 1;
+		}
+		++idx;
+	}
+	if (prev_idx < str.size() && items.size() < maxparts) {
+		items << str.right(str.size() - prev_idx);
+	}
+	return items;
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+template<class Addr>
+QList<Module> get_loaded_modules(const IProcess* process) {
+
+	QList<Module> ret;
+
+	edb::netbsd_struct::r_debug<Addr> dynamic_info;
+	if(process) {
+		if(const edb::address_t debug_pointer = process->debug_pointer()) {
+			if(process->read_bytes(debug_pointer, &dynamic_info, sizeof(dynamic_info))) {
+				if(dynamic_info.r_map) {
+
+					auto link_address = edb::address_t::fromZeroExtended(dynamic_info.r_map);
+
+					while(link_address) {
+
+						edb::netbsd_struct::link_map<Addr> map;
+						if(process->read_bytes(link_address, &map, sizeof(map))) {
+							char path[PATH_MAX];
+							if(!process->read_bytes(edb::address_t::fromZeroExtended(map.l_name), &path, sizeof(path))) {
+								path[0] = '\0';
+							}
+
+							if(map.l_addr) {
+								Module module;
+								module.name         = path;
+								module.base_address = map.l_addr;
+								ret.push_back(module);
+							}
+
+							link_address = edb::address_t::fromZeroExtended(map.l_next);
+						} else {
+							break;
+						}
+					}
+				}
+			}
+		}
+	}
+
+	// fallback
+	if(ret.isEmpty()) {
+		const QList<std::shared_ptr<IRegion>> r = edb::v1::memory_regions().regions();
+		QSet<QString> found_modules;
+
+		for(const std::shared_ptr<IRegion> &region: r) {
+
+			// we assume that modules will be listed by absolute path
+			if(region->name().startsWith("/")) {
+				if(!util::contains(found_modules, region->name())) {
+					Module module;
+					module.name         = region->name();
+					module.base_address = region->start();
+					found_modules.insert(region->name());
+					ret.push_back(module);
+				}
+			}
+		}
+	}
+
+	return ret;
+}
+
+}
+
+//------------------------------------------------------------------------------
+// Name: PlatformProcess
+// Desc:
+//------------------------------------------------------------------------------
+PlatformProcess::PlatformProcess(DebuggerCore *core, edb::pid_t pid) : core_(core), pid_(pid) {
+}
+
+//------------------------------------------------------------------------------
+// Name: seek_addr
+// Desc: seeks memory file to given address, taking possible negativity of the
+// address into account
+//------------------------------------------------------------------------------
+void seek_addr(QFile& file, edb::address_t address) {
+	file.seek(address);
+}
+
+
+//------------------------------------------------------------------------------
+// Name: read_bytes
+// Desc: reads <len> bytes into <buf> starting at <address>
+// Note: returns the number of bytes read <N>
+// Note: if the read is short, only the first <N> bytes are defined
+//------------------------------------------------------------------------------
+std::size_t PlatformProcess::read_bytes(edb::address_t address, void* buf, std::size_t len) const {
+	quint64 read = 0;
+
+	Q_ASSERT(buf);
+	Q_ASSERT(core_->process_.get() == this);
+
+	auto ptr = reinterpret_cast<char *>(buf);
+
+	if(len != 0) {
+
+		// small reads take the fast path
+		if(len == 1) {
+
+			auto it = core_->breakpoints_.find(address);
+			if(it != core_->breakpoints_.end()) {
+				*ptr = (*it)->original_bytes()[0];
+				return 1;
+			}
+
+			if(ro_mem_file_) {
+				seek_addr(*ro_mem_file_, address);
+				read = ro_mem_file_->read(ptr, 1);
+				if (read == 1) {
+					return 1;
+				}
+				return 0;
+			} else {
+				bool ok;
+				quint8 x = read_byte_via_ptrace(address, &ok);
+				if(ok) {
+					*ptr = x;
+					return 1;
+				}
+				return 0;
+			}
+		}
+
+		if(ro_mem_file_) {
+			seek_addr(*ro_mem_file_, address);
+			read = ro_mem_file_->read(ptr, len);
+			if(read == 0 || read == quint64(-1)) {
+				return 0;
+			}
+		} else {
+			for(std::size_t index = 0; index < len; ++index) {
+
+				// read a byte, if we failed, we are done
+				bool ok;
+				const quint8 x = read_byte_via_ptrace(address + index, &ok);
+				if(!ok) {
+					break;
+				}
+
+				// store it
+				reinterpret_cast<char*>(buf)[index] = x;
+
+				++read;
+			}
+		}
+
+		// replace any breakpoints
+		Q_FOREACH(const std::shared_ptr<IBreakpoint> &bp, core_->breakpoints_) {
+			auto bpBytes = bp->original_bytes();
+			const edb::address_t bpAddr = bp->address();
+			// show the original bytes in the buffer..
+			for(size_t i=0; i < bp->size(); ++i) {
+				if(bpAddr + i >= address && bpAddr + i < address + read) {
+					ptr[bpAddr + i - address] = bpBytes[i];
+				}
+			}
+		}
+	}
+
+	return read;
+}
+
+//------------------------------------------------------------------------------
+// Name: patch_bytes
+// Desc: same as write_bytes, except that it also records the original data
+//       that was found at the address being written to.
+// Note: unlike the read_bytes, write_bytes functions, this will not apply the
+//       write if we could not properly backup <len> bytes as requested.
+// Note: on the off chance that we can READ <len> bytes, but can't WRITE <len>
+//       bytes, we will return the number of bytes written, but record <len>
+//       bytes of patch data.
+//------------------------------------------------------------------------------
+std::size_t PlatformProcess::patch_bytes(edb::address_t address, const void *buf, size_t len) {
+	Q_ASSERT(buf);
+	Q_ASSERT(core_->process_.get() == this);
+
+	Patch patch;
+	patch.address = address;
+	patch.orig_bytes.resize(len);
+	patch.new_bytes = QByteArray(static_cast<const char *>(buf), len);
+
+	size_t read_ret = read_bytes(address, patch.orig_bytes.data(), len);
+	if(read_ret != len) {
+		return 0;
+	}
+
+	patches_.insert(address, patch);
+
+	return write_bytes(address, buf, len);
+}
+
+//------------------------------------------------------------------------------
+// Name: write_bytes
+// Desc: writes <len> bytes from <buf> starting at <address>
+//------------------------------------------------------------------------------
+std::size_t PlatformProcess::write_bytes(edb::address_t address, const void *buf, std::size_t len) {
+	quint64 written = 0;
+
+	Q_ASSERT(buf);
+	Q_ASSERT(core_->process_.get() == this);
+
+	if(len != 0) {
+		if(rw_mem_file_) {
+			seek_addr(*rw_mem_file_,address);
+			written = rw_mem_file_->write(reinterpret_cast<const char *>(buf), len);
+			if(written == 0 || written == quint64(-1)) {
+				return 0;
+			}
+		}
+		else {
+			// TODO write whole words at a time using ptrace_poke.
+			for(std::size_t byteIndex=0;byteIndex<len;++byteIndex) {
+				bool ok=false;
+				write_byte_via_ptrace(address+byteIndex, *(reinterpret_cast<const char*>(buf)+byteIndex), &ok);
+				if(!ok) return written;
+				++written;
+			}
+		}
+	}
+
+	return written;
+}
+
+//------------------------------------------------------------------------------
+// Name: read_pages
+// Desc: reads <count> pages from the process starting at <address>
+// Note: buf's size must be >= count * core_->page_size()
+// Note: address should be page aligned.
+//------------------------------------------------------------------------------
+std::size_t PlatformProcess::read_pages(edb::address_t address, void *buf, std::size_t count) const {
+	Q_ASSERT(buf);
+	Q_ASSERT(core_->process_.get() == this);
+	return read_bytes(address, buf, count * core_->page_size()) / core_->page_size();
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QDateTime PlatformProcess::start_time() const {
+	QDateTime time;
+
+	struct ::kinfo_proc2 kp;
+	::size_t len = sizeof(kp);
+
+	const int mib[] = { CTL_KERN, KERN_PROC2, KERN_PROC_PID, pid, sizeof(kp), 1 };
+	if (::sysctl(mib, __arraycount(mib), &kp, &len, NULL, 0) == -1)
+		return time;
+
+	time.setTime_t(kp.p_ustart_sec);
+	time.setTime(time.time().addMSecs((int)(kp.p_ustart_usec / 1000.0)));
+
+	return time;
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QList<QByteArray> PlatformProcess::arguments() const {
+	QList<QByteArray> ret;
+
+    int mib[4];
+    int st;
+    size_t len;
+    char *procargs;
+
+    mib[0] = CTL_KERN;
+    mib[1] = KERN_PROC_ARGS;
+    mib[2] = pid_;
+    mib[3] = KERN_PROC_ARGV;
+    len = 0;
+
+    st = ::sysctl(mib, __arraycount(mib), NULL, &len, NULL, 0);
+    if (st == -1) {
+        return ret;
+    }
+
+    procargs = (char *)::malloc(len);
+    if (procargs == NULL) {
+        return ret;
+    }
+    st = ::sysctl(mib, __arraycount(mib), procargs, &len, NULL, 0);
+    if (st == -1) {
+        ::free(procargs);
+        return ret;
+    }
+
+    QByteArray s;
+    QChar ch;
+
+    for (size_t i = 0; i < len; i++) {
+	procargs[i] >> ch;
+        if(ch.isNull()) {
+            if(!s.isEmpty()) {
+                ret << s;
+            }
+            s.clear();
+	} else {
+            s += ch;
+        }
+    }
+    if(!s.isEmpty()) {
+        ret << s;
+    }
+
+    free(procargs);
+
+    return ret;
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QString PlatformProcess::current_working_directory() const {
+	int mib[] = { CTL_KERN, KERN_PROC_ARGS, pid_, KERN_PROC_CWD };
+	size_t len;
+
+	::sysctl(mib, __arraycount(mib), 0, &len, NULL, 0);
+	char *buf = (char *)::malloc(len);
+	::sysctl(mib, __arraycount(mib), buf, &len, NULL, 0);
+	QString str = buf;
+	free(buf);
+
+	return str;
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QString PlatformProcess::executable() const {
+	int mib[] = { CTL_KERN, KERN_PROC_ARGS, pid_, KERN_PROC_PATHNAME };
+	size_t len;
+
+	::sysctl(mib, __arraycount(mib), 0, &len, NULL, 0);
+	char *buf = (char *)::malloc(len);
+	::sysctl(mib, __arraycount(mib), buf, &len, NULL, 0);
+	QString str = buf;
+	free(buf);
+
+	return str;
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+edb::pid_t PlatformProcess::pid() const {
+	return pid_;
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IProcess> PlatformProcess::parent() const {
+	struct ::kinfo_proc2 kp;
+	::size_t len = sizeof(kp);
+
+	const int mib[] = { CTL_KERN, KERN_PROC2, KERN_PROC_PID, pid, sizeof(kp), 1 };
+	if (::sysctl(mib, __arraycount(mib), &kp, &len, NULL, 0) == -1)
+		return nulptr;
+
+	return std::make_shared<PlatformProcess>(core_, kp.p_ppid);
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+edb::address_t PlatformProcess::code_address() const {
+	struct user_stat user_stat;
+	int n = get_user_stat(pid_, &user_stat);
+	if(n >= 26) {
+		return user_stat.startcode;
+	}
+	return 0;
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+edb::address_t PlatformProcess::data_address() const {
+	struct user_stat user_stat;
+	int n = get_user_stat(pid_, &user_stat);
+	if(n >= 27) {
+		return user_stat.endcode + 1; // endcode == startdata ?
+	}
+	return 0;
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QList<std::shared_ptr<IRegion>> PlatformProcess::regions() const {
+	static QList<std::shared_ptr<IRegion>> regions;
+	const int mib[] = { CTL_VM, VM_PROC, VM_PROC_MAP, pid_, sizeof(struct kinfo_vmentry) };
+	::size_t len;
+	::sysctl(mib, __arraycount(mib), NULL, &len, NULL, 0);
+	len <<= 1;
+	struct ::kinfo_vmentry *ptr = (struct ::kinfo_vmentry *)::malloc(len);
+	::sysctl(mib, __arraycount(mib), ptr, &len, NULL, 0);
+
+	for (::size_t i = 0; i < len/sizeof(struct ::kinfo_vmentry); i++) {
+		edb::address_t start = ptr[i].kve_start;
+		edb::address_t end = ptr[i].kve_end;
+		edb::address_t base = ptr[i].kve_offset;
+		IRegion::permissions_t permissions = 0;
+		if (ptr[i].kve_protection & KVME_PROT_READ)
+			permissions |= PROT_READ;
+		if (ptr[i].kve_protection & KVME_PROT_WRITE)
+			permissions |= PROT_WRITE;
+		if (ptr[i].kve_protection & KVME_PROT_EXEC)
+			permissions |= PROT_EXEC;
+		QString name = ptr[i].kve_path;
+
+		auto region = std::make_shared<PlatformRegion>(start, end, base, name, permissions);
+		regions.push_back(region);
+	}
+
+	free(ptr);
+
+	return regions;
+}
+
+//------------------------------------------------------------------------------
+// Name: read_byte
+// Desc: the base implementation of reading a byte
+//------------------------------------------------------------------------------
+quint8 PlatformProcess::read_byte_via_ptrace(edb::address_t address, bool *ok) const {
+	// TODO(eteran): assert that we are paused
+
+	Q_ASSERT(ok);
+	Q_ASSERT(core_->process_.get() == this);
+
+	*ok = false;
+
+	// if this spot is unreadable, then just return 0xff, otherwise
+	// continue as normal.
+
+	// core_->page_size() - 1 will always be 0xf* because pagesizes
+	// are always 0x10*, so the masking works
+	// range of nBytesToNextPage is [1..n] where n=pagesize, and we have to adjust
+	// if nByteToNextPage < wordsize
+	const size_t nBytesToNextPage = core_->page_size() - (address & (core_->page_size() - 1));
+
+	// Avoid crossing page boundary, since next page may be unreadable
+	const size_t addressShift = nBytesToNextPage < EDB_WORDSIZE ? EDB_WORDSIZE - nBytesToNextPage : 0;
+	address -= addressShift;
+
+	const long value = ptrace_peek(address, ok);
+
+	if(*ok) {
+		quint8 result;
+		// We aren't interested in `value` as in number, it's just a buffer, so no endianness magic.
+		// Just have to compensate for `addressShift` when reading it.
+		std::memcpy(&result, reinterpret_cast<const char*>(&value) + addressShift, sizeof(result));
+		return result;
+	}
+
+	return 0xff;
+}
+
+
+//------------------------------------------------------------------------------
+// Name: write_byte
+// Desc: writes a single byte at a given address via ptrace API.
+// Note: assumes the this will not trample any breakpoints, must be handled
+//       in calling code!
+//------------------------------------------------------------------------------
+void PlatformProcess::write_byte_via_ptrace(edb::address_t address, quint8 value, bool *ok) {
+	// TODO(eteran): assert that we are paused
+
+	Q_ASSERT(ok);
+	Q_ASSERT(core_->process_.get() == this);
+
+	*ok = false;
+
+	// core_->page_size() - 1 will always be 0xf* because pagesizes
+	// are always 0x10*, so the masking works
+	// range of nBytesToNextPage is [1..n] where n=pagesize, and we have to adjust
+	// if nBytesToNextPage < wordsize
+	const size_t nBytesToNextPage = core_->page_size() - (address & (core_->page_size() - 1));
+
+	// Avoid crossing page boundary, since next page may be inaccessible
+	const size_t addressShift = nBytesToNextPage < EDB_WORDSIZE ? EDB_WORDSIZE - nBytesToNextPage : 0;
+	address -= addressShift;
+
+	long word = ptrace_peek(address, ok);
+	if(!*ok) {
+		return;
+	}
+
+	// We aren't interested in `value` as in number, it's just a buffer, so no endianness magic.
+	// Just have to compensate for `addressShift` when writing it.
+	std::memcpy(reinterpret_cast<char*>(&word) + addressShift, &value, sizeof(value));
+
+	*ok = ptrace_poke(address, word);
+}
+
+//------------------------------------------------------------------------------
+// Name: ptrace_peek
+// Desc:
+// Note: this will fail on newer versions of netbsd if called from a
+//       different thread than the one which attached to process
+//------------------------------------------------------------------------------
+long PlatformProcess::ptrace_peek(edb::address_t address, bool *ok) const {
+}
+
+//------------------------------------------------------------------------------
+// Name: ptrace_poke
+// Desc:
+//------------------------------------------------------------------------------
+bool PlatformProcess::ptrace_poke(edb::address_t address, long value) {
+}
+
+//------------------------------------------------------------------------------
+// Name: threads
+// Desc:
+//------------------------------------------------------------------------------
+QList<std::shared_ptr<IThread>> PlatformProcess::threads() const {
+
+	Q_ASSERT(core_->process_.get() == this);
+
+	QList<std::shared_ptr<IThread>> threadList;
+	threadList.reserve(core_->threads_.size());
+	std::copy(core_->threads_.begin(), core_->threads_.end(), std::back_inserter(threadList));
+	return threadList;
+}
+
+//------------------------------------------------------------------------------
+// Name: current_thread
+// Desc:
+//------------------------------------------------------------------------------
+std::shared_ptr<IThread> PlatformProcess::current_thread() const {
+
+	Q_ASSERT(core_->process_.get() == this);
+
+	auto it = core_->threads_.find(core_->active_thread_);
+	if(it != core_->threads_.end()) {
+		return it.value();
+	}
+	return nullptr;
+}
+
+//------------------------------------------------------------------------------
+// Name: set_current_thread
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformProcess::set_current_thread(IThread& thread) {
+	core_->active_thread_ = static_cast<PlatformThread*>(&thread)->tid();
+	edb::v1::update_ui();
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+edb::uid_t PlatformProcess::uid() const {
+	struct ::kinfo_proc2 kp;
+	::size_t len = sizeof(kp);
+
+	const int mib[] = { CTL_KERN, KERN_PROC2, KERN_PROC_PID, pid_, sizeof(kp), 1 };
+	if (::sysctl(mib, __arraycount(mib), &kp, &len, NULL, 0) == -1)
+		return 0;
+
+	return kp.p_uid;
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QString PlatformProcess::user() const {
+	if(const struct passwd *const pwd = ::getpwuid(uid())) {
+		return pwd->pw_name;
+	}
+
+	return QString();
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QString PlatformProcess::name() const {
+	struct ::kinfo_proc2 kp;
+	::size_t len = sizeof(kp);
+
+	const int mib[] = { CTL_KERN, KERN_PROC2, KERN_PROC_PID, pid_, sizeof(kp), 1 };
+	if (::sysctl(mib, __arraycount(mib), &kp, &len, NULL, 0) == -1)
+		return 0;
+
+	return QString(kp.p_comm);
+}
+
+//------------------------------------------------------------------------------
+// Name:
+// Desc:
+//------------------------------------------------------------------------------
+QList<Module> PlatformProcess::loaded_modules() const {
+	return get_loaded_modules<Elf64_Addr>(this);
+}
+
+//------------------------------------------------------------------------------
+// Name: pause
+// Desc: stops *all* threads of a process
+//------------------------------------------------------------------------------
+Status PlatformProcess::pause() {
+	return Status::Ok;
+}
+
+//------------------------------------------------------------------------------
+// Name: step
+// Desc: steps the currently active thread
+//------------------------------------------------------------------------------
+Status PlatformProcess::step(edb::EVENT_STATUS status) {
+}
+
+//------------------------------------------------------------------------------
+// Name: isPaused
+// Desc: returns true if ALL threads are currently in the debugger's wait list
+//------------------------------------------------------------------------------
+bool PlatformProcess::isPaused() const {
+}
+
+//------------------------------------------------------------------------------
+// Name: resume
+// Desc: resumes ALL threads
+//------------------------------------------------------------------------------
+Status PlatformProcess::resume(edb::EVENT_STATUS status) {
+	return Status::Ok;
+}
+
+//------------------------------------------------------------------------------
+// Name: patches
+// Desc: returns any patches applied to this process
+//------------------------------------------------------------------------------
+QMap<edb::address_t, Patch> PlatformProcess::patches() const {
+	return patches_;
+}
+
+/**
+ * @brief PlatformProcess::entry_point
+ * @return
+ */
+edb::address_t PlatformProcess::entry_point() const  {
+	::size_t len = 4096 * 10;
+	AuxInfo *ptr = (AuxInfo *)::malloc(len);
+	edb::address_t val;
+
+	struct ptrace_io_desc io = { PIOD_READ_AUXV, NULL, ptr, len };
+
+	pid_t pid_ = 0;
+	ptrace(PT_IO, pid_, &io, 0);
+
+	for (AuxInfo *aip = ptr; aip->a_type != AT_NULL; aip++) {
+		if (aip->a_type == AT_ENTRY) {
+			val = aip->a_v;
+			break;
+		}
+	}
+
+	free(ptr);
+
+	return val;
+}
+
+/**
+ * @brief get_program_headers
+ * @param process
+ * @param phdr_memaddr
+ * @param num_phdr
+ * @return
+ */
+bool get_program_headers(const IProcess *process, edb::address_t *phdr_memaddr, int *num_phdr) {
+
+	*phdr_memaddr = edb::address_t{};
+	*num_phdr = 0;
+
+	::size_t len = 4096 * 10;
+	AuxInfo *ptr = (AuxInfo *)::malloc(len);
+	edb::address_t val;
+
+	struct ptrace_io_desc io = { PIOD_READ_AUXV, NULL, ptr, len };
+
+	pid_t pid_ = 0;
+	ptrace(PT_IO, pid_, &io, 0);
+
+	for (AuxInfo *aip = ptr; aip->a_type != AT_NULL; aip++) {
+		if (aip->a_type == AT_PHDR) {
+			*phdr_memaddr = aip->a_v;
+			break;
+		} else if (aip->a_type == AT_PHNUM) {
+			*num_phdr = aip->a_v;
+			break;
+		}
+	}
+
+	free(ptr);
+
+	return (*phdr_memaddr != 0 && *num_phdr != 0);
+}
+
+/**
+ * @brief get_debug_pointer
+ * @param process
+ * @param phdr_memaddr
+ * @param count
+ * @param relocation
+ * @return
+ */
+template <class Model>
+edb::address_t get_debug_pointer(const IProcess *process, edb::address_t phdr_memaddr, int count, edb::address_t relocation) {
+
+	using elf_phdr = typename Model::elf_phdr;
+
+	elf_phdr phdr;
+	for(int i = 0; i < count; ++i) {
+		if(process->read_bytes(phdr_memaddr + i * sizeof(elf_phdr), &phdr, sizeof(elf_phdr))) {
+			if(phdr.p_type == PT_DYNAMIC) {
+				try {
+
+					auto buf = std::make_unique<uint8_t[]>(phdr.p_memsz);
+
+					if(process->read_bytes(phdr.p_vaddr + relocation, &buf[0], phdr.p_memsz)) {
+						auto dynamic = reinterpret_cast<typename Model::elf_dyn *>(&buf[0]);
+						while(dynamic->d_tag != DT_NULL) {
+							if(dynamic->d_tag == DT_DEBUG) {
+								return dynamic->d_un.d_val;
+							}
+							++dynamic;
+						}
+					}
+				} catch(const std::bad_alloc &) {
+					qDebug() << "[get_debug_pointer] no more memory";
+					return 0;
+				}
+			}
+		}
+	}
+
+	return 0;
+}
+
+/**
+ * @brief get_relocation
+ * @param process
+ * @param phdr_memaddr
+ * @param i
+ * @return
+ */
+template <class Model>
+edb::address_t get_relocation(const IProcess *process, edb::address_t phdr_memaddr, int i) {
+
+	using elf_phdr = typename Model::elf_phdr;
+
+	elf_phdr phdr;
+	if(process->read_bytes(phdr_memaddr + i * sizeof(elf_phdr), &phdr, sizeof(elf_phdr))) {
+		if (phdr.p_type == PT_PHDR) {
+			return phdr_memaddr - phdr.p_vaddr;
+		}
+	}
+
+	return -1;
+}
+
+/**
+ * attempts to locate the ELF debug pointer in the target process and returns
+ * it, 0 of not found
+ *
+ * @brief PlatformProcess::debug_pointer
+ * @return
+ */
+edb::address_t PlatformProcess::debug_pointer() const {
+
+	// NOTE(eteran): some of this code is from or inspired by code in
+	// gdb/gdbserver/linux-low.c
+
+	edb::address_t phdr_memaddr;
+	int num_phdr;
+
+	if(get_program_headers(this, &phdr_memaddr, &num_phdr)) {
+
+		/* Compute relocation: it is expected to be 0 for "regular" executables,
+		 * non-zero for PIE ones.  */
+		edb::address_t relocation = -1;
+		for (int i = 0; relocation == -1 && i < num_phdr; i++) {
+			relocation = get_relocation<elf_model<64>>(this, phdr_memaddr, i);
+		}
+
+		if (relocation == -1) {
+			/* PT_PHDR is optional, but necessary for PIE in general.
+			 * Fortunately any real world executables, including PIE
+			 * executables, have always PT_PHDR present.  PT_PHDR is not
+			 * present in some shared libraries or in fpc (Free Pascal 2.4)
+			 * binaries but neither of those have a need for or present
+			 * DT_DEBUG anyway (fpc binaries are statically linked).
+			 *
+			 * Therefore if there exists DT_DEBUG there is always also PT_PHDR.
+			 *
+			 * GDB could find RELOCATION also from AT_ENTRY - e_entry.  */
+			return 0;
+		}
+
+			return get_debug_pointer<elf_model<64>>(this, phdr_memaddr, num_phdr, relocation);
+	}
+
+	return edb::address_t{};
+}
+
+edb::address_t PlatformProcess::calculate_main() const {
+		ByteShiftArray ba(14);
+
+		edb::address_t entry_point = this->entry_point();
+
+		for(int i = 0; i < 50; ++i) {
+			quint8 byte;
+			if(read_bytes(entry_point + i, &byte, sizeof(byte))) {
+				ba << byte;
+
+				edb::address_t address = 0;
+
+				if(ba.size() >= 13) {
+					// beginning of a call preceeded by a 64-bit mov and followed by a hlt
+					if(ba[0] == 0x48 && ba[1] == 0xc7 && ba[7] == 0xe8 && ba[12] == 0xf4) {
+						// Seems that this 64-bit mov still has a 32-bit immediate
+						address = *reinterpret_cast<const edb::address_t *>(ba.data() + 3) & 0xffffffff;
+					}
+
+					// same heuristic except for PIC binaries
+					else if (ba.size() >= 14 && ba[0] == 0x48 && ba[1] == 0x8d && ba[2] == 0x3d && ba[7] == 0xFF && ba[8] == 0x15 && ba[13] == 0xf4) {
+						// It's signed relative!
+						auto rel = *reinterpret_cast<const qint32 *>(ba.data() + 3);
+						// ba[0] is entry_point + i - 13. instruction is 7 bytes long.
+						address = rel + entry_point + i - 13 + 7;
+					}
+
+					if (address) {
+						// TODO: make sure that this address resides in an executable region
+						qDebug() << "No main symbol found, calculated it to be " << edb::v1::format_pointer(address) << " using heuristic";
+						return address;
+					}
+				}
+			} else {
+				break;
+			}
+		}
+
+	return 0;
+}
+
+}
