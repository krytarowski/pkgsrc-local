$NetBSD$

--- plugins/DebuggerCore/unix/netbsd/arch/x86-generic/PlatformThread.cpp.orig	2019-06-16 23:21:29.984368447 +0000
+++ plugins/DebuggerCore/unix/netbsd/arch/x86-generic/PlatformThread.cpp
@@ -0,0 +1,113 @@
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
+#include "PlatformThread.h"
+#include "DebuggerCore.h"
+#include "IProcess.h"
+#include "PlatformCommon.h"
+#include "PlatformState.h"
+#include "State.h"
+#include <QtDebug>
+
+#include <elf.h>
+#include <sys/types.h>
+#include <sys/ptrace.h>
+#include <fcntl.h>
+
+
+namespace DebuggerCorePlugin {
+
+//------------------------------------------------------------------------------
+// Name: fillSegmentBases
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformThread::fillSegmentBases(PlatformState* state) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+//------------------------------------------------------------------------------
+// Name: fillStateFromPrStatus
+// Desc:
+//------------------------------------------------------------------------------
+bool PlatformThread::fillStateFromPrStatus(PlatformState* state) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+//------------------------------------------------------------------------------
+// Name: fillStateFromSimpleRegs
+// Desc:
+//------------------------------------------------------------------------------
+bool PlatformThread::fillStateFromSimpleRegs(PlatformState* state) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+//------------------------------------------------------------------------------
+// Name: get_state
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformThread::get_state(State *state) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	auto state_impl = static_cast<PlatformState *>(state->impl_.get());
+
+	ptrace(PT_GETREGS, process_->pid(), &state_impl->regs_, tid_);
+}
+
+//------------------------------------------------------------------------------
+// Name: set_state
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformThread::set_state(const State &state) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+//------------------------------------------------------------------------------
+// Name: get_debug_register
+// Desc:
+//------------------------------------------------------------------------------
+unsigned long PlatformThread::get_debug_register(std::size_t n) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+//------------------------------------------------------------------------------
+// Name: set_debug_register
+// Desc:
+//------------------------------------------------------------------------------
+long PlatformThread::set_debug_register(std::size_t n, long value) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+//------------------------------------------------------------------------------
+// Name: step
+// Desc: steps this thread one instruction, passing the signal that stopped it
+//       (unless the signal was SIGSTOP)
+//------------------------------------------------------------------------------
+Status PlatformThread::step() {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+//------------------------------------------------------------------------------
+// Name: step
+// Desc: steps this thread one instruction, passing the signal that stopped it
+//       (unless the signal was SIGSTOP, or the passed status != DEBUG_EXCEPTION_NOT_HANDLED)
+//------------------------------------------------------------------------------
+Status PlatformThread::step(edb::EVENT_STATUS status) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+}
