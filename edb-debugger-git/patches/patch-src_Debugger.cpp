$NetBSD$

--- src/Debugger.cpp.orig	2019-06-13 22:49:27.000000000 +0000
+++ src/Debugger.cpp
@@ -51,7 +51,7 @@ along with this program.  If not, see <h
 #include "SessionError.h"
 #include "edb.h"
 
-#if defined(Q_OS_LINUX)
+#if defined(Q_OS_LINUX) || defined(Q_OS_NETBSD)
 #include "linker.h"
 #endif
 
@@ -91,7 +91,7 @@ along with this program.  If not, see <h
 
 #include <sys/types.h>
 #include <sys/stat.h>
-#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD) || defined(Q_OS_FREEBSD)
+#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD) || defined(Q_OS_FREEBSD) || defined(Q_OS_NETBSD)
 #include <unistd.h>
 #include <fcntl.h>
 #endif
@@ -107,7 +107,7 @@ constexpr quint64 ld_loader_tag     = Q_
 
 template <class Addr>
 void handle_library_event(IProcess *process, edb::address_t debug_pointer) {
-#ifdef Q_OS_LINUX
+#if defined(Q_OS_LINUX)
 	edb::linux_struct::r_debug<Addr> dynamic_info;
 	const bool ok = (process->read_bytes(debug_pointer, &dynamic_info, sizeof(dynamic_info)) == sizeof(dynamic_info));
 	if(ok) {
@@ -133,6 +133,32 @@ void handle_library_event(IProcess *proc
 			break;
 		}
 	}
+#elif defined(Q_OS_NETBSD)
+	edb::netbsd_struct::r_debug<Addr> dynamic_info;
+	const bool ok = (process->read_bytes(debug_pointer, &dynamic_info, sizeof(dynamic_info)) == sizeof(dynamic_info));
+	if(ok) {
+
+		// NOTE(eteran): at least on my system, the name of
+		//               what is being loaded is either in
+		//               r8 or r13 depending on which event
+		//               we are looking at.
+		// TODO(eteran): find a way to get the name reliably
+
+		switch(dynamic_info.r_state) {
+		case edb::netbsd_struct::r_debug<Addr>::RT_CONSISTENT:
+			// TODO(eteran): enable this once we are confident
+	#if 0
+			edb::v1::memory_regions().sync();
+	#endif
+			break;
+		case edb::netbsd_struct::r_debug<Addr>::RT_ADD:
+			//qDebug("LIBRARY LOAD EVENT");
+			break;
+		case edb::netbsd_struct::r_debug<Addr>::RT_DELETE:
+			//qDebug("LIBRARY UNLOAD EVENT");
+			break;
+		}
+	}
 #else
 	Q_UNUSED(process)
 	Q_UNUSED(debug_pointer)
@@ -141,12 +167,18 @@ void handle_library_event(IProcess *proc
 
 template <class Addr>
 edb::address_t find_linker_hook_address(IProcess *process, edb::address_t debug_pointer) {
-#ifdef Q_OS_LINUX
+#if defined(Q_OS_LINUX)
 	edb::linux_struct::r_debug<Addr> dynamic_info;
 	const bool ok = process->read_bytes(debug_pointer, &dynamic_info, sizeof(dynamic_info));
 	if(ok) {
 		return edb::address_t::fromZeroExtended(dynamic_info.r_brk);
 	}
+#elif defined(Q_OS_NETBSD)
+	edb::netbsd_struct::r_debug<Addr> dynamic_info;
+	const bool ok = process->read_bytes(debug_pointer, &dynamic_info, sizeof(dynamic_info));
+	if(ok) {
+		return edb::address_t::fromZeroExtended(dynamic_info.r_brk);
+	}
 #else
 	Q_UNUSED(process)
 	Q_UNUSED(debug_pointer)
@@ -595,7 +627,7 @@ QString Debugger::create_tty() {
 
 	QString result_tty = tty_file_;
 
-#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD) || defined(Q_OS_FREEBSD)
+#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD) || defined(Q_OS_FREEBSD) || defined(Q_OS_NETBSD)
 	// we attempt to reuse an open output window
 	if(edb::v1::config().tty_enabled && tty_proc_->state() != QProcess::Running) {
 		const QString command = edb::v1::config().tty_command;
@@ -2218,7 +2250,7 @@ edb::EVENT_STATUS Debugger::handle_trap(
 		state.set_instruction_pointer(previous_ip);
 		process->current_thread()->set_state(state);
 
-#if defined(Q_OS_LINUX)
+#if defined(Q_OS_LINUX) || defined(Q_OS_NETBSD)
 		// test if we have hit our internal LD hook BP. If so, read in the r_debug
 		// struct so we can get the state, then we can just resume
 		// TODO(eteran): add an option to let the user stop of debug events
@@ -2869,7 +2901,7 @@ void Debugger::set_initial_debugger_stat
 	reenable_breakpoint_run_  = nullptr;
 	reenable_breakpoint_step_ = nullptr;
 
-#ifdef Q_OS_LINUX
+#if defined(Q_OS_LINUX) || defined(Q_OS_NETBSD)
 	debug_pointer_ = 0;
 	dynamic_info_bp_set_ = false;
 #endif
@@ -3420,7 +3452,7 @@ void Debugger::next_debug_event() {
 		//               do this when the hook isn't set.
 		edb::v1::memory_regions().sync();
 
-#if defined(Q_OS_LINUX)
+#if defined(Q_OS_LINUX) || defined(Q_OS_NETBSD)
 		if(!dynamic_info_bp_set_) {
 			if(IProcess *process = edb::v1::debugger_core->process()) {
 				if(debug_pointer_ == 0) {
