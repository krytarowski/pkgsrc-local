$NetBSD$

--- plugins/DebuggerCore/unix/netbsd/arch/x86-generic/PlatformState.cpp.orig	2019-06-16 23:21:29.961093575 +0000
+++ plugins/DebuggerCore/unix/netbsd/arch/x86-generic/PlatformState.cpp
@@ -0,0 +1,478 @@
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
+#include "PlatformState.h"
+#include "FloatX.h"
+#include "string_hash.h"
+#include "Util.h"
+#include <QDebug>
+#include <QRegExp>
+#include <unordered_map>
+
+namespace DebuggerCorePlugin {
+
+//------------------------------------------------------------------------------
+// Name: PlatformState
+// Desc:
+//------------------------------------------------------------------------------
+PlatformState::PlatformState() {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+    this->clear();
+}
+
+//------------------------------------------------------------------------------
+// Name: PlatformState::clone
+// Desc: makes a copy of the state object
+//------------------------------------------------------------------------------
+std::unique_ptr<IState> PlatformState::clone() const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	return std::make_unique<PlatformState>(*this);
+}
+
+//------------------------------------------------------------------------------
+// Name: flags_to_string
+// Desc: returns the flags in a string form appropriate for this platform
+//------------------------------------------------------------------------------
+QString PlatformState::flags_to_string(edb::reg_t flags) const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+//------------------------------------------------------------------------------
+// Name: flags_to_string
+// Desc: returns the flags in a string form appropriate for this platform
+//------------------------------------------------------------------------------
+QString PlatformState::flags_to_string() const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+template <size_t BitSize = 0, class Names, class Regs>
+Register findRegisterValue(const Names &names, const Regs &regs, const QString &regName, Register::Type type, size_t maxNames, int shift = 0) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+//------------------------------------------------------------------------------
+// Name: value
+// Desc: returns a Register object which represents the register with the name
+//       supplied
+//------------------------------------------------------------------------------
+Register PlatformState::value(const QString &reg) const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	const QString regName = reg.toLower();
+
+	if (regName == "rdi")
+		return make_Register("rdi", regs_.regs[_REG_RDI], Register::TYPE_GPR);
+	if (regName == "rsi")
+		return make_Register("rsi", regs_.regs[_REG_RSI], Register::TYPE_GPR);
+	if (regName == "rdx")
+		return make_Register("rdx", regs_.regs[_REG_RDX], Register::TYPE_GPR);
+	if (regName == "rcx")
+		return make_Register("rcx", regs_.regs[_REG_RCX], Register::TYPE_GPR);
+	if (regName == "r8")
+		return make_Register("r8", regs_.regs[_REG_R8], Register::TYPE_GPR);
+	if (regName == "r9")
+		return make_Register("r9", regs_.regs[_REG_R9], Register::TYPE_GPR);
+	if (regName == "r10")
+		return make_Register("r10", regs_.regs[_REG_R10], Register::TYPE_GPR);
+	if (regName == "r11")
+		return make_Register("r11", regs_.regs[_REG_R11], Register::TYPE_GPR);
+	if (regName == "r12")
+		return make_Register("r12", regs_.regs[_REG_R12], Register::TYPE_GPR);
+	if (regName == "r13")
+		return make_Register("r13", regs_.regs[_REG_R13], Register::TYPE_GPR);
+	if (regName == "r14")
+		return make_Register("r14", regs_.regs[_REG_R14], Register::TYPE_GPR);
+	if (regName == "r15")
+		return make_Register("r15", regs_.regs[_REG_R15], Register::TYPE_GPR);
+	if (regName == "rbp")
+		return make_Register("rbp", regs_.regs[_REG_RBP], Register::TYPE_GPR);
+	if (regName == "rbx")
+		return make_Register("rbx", regs_.regs[_REG_RBX], Register::TYPE_GPR);
+	if (regName == "rax")
+		return make_Register("rax", regs_.regs[_REG_RAX], Register::TYPE_GPR);
+	if (regName == "gs")
+		return make_Register("gs", regs_.regs[_REG_GS], Register::TYPE_GPR);
+	if (regName == "fs")
+		return make_Register("fs", regs_.regs[_REG_FS], Register::TYPE_GPR);
+	if (regName == "es")
+		return make_Register("es", regs_.regs[_REG_ES], Register::TYPE_GPR);
+	if (regName == "ds")
+		return make_Register("ds", regs_.regs[_REG_DS], Register::TYPE_GPR);
+	if (regName == "trapno")
+		return make_Register("trapno", regs_.regs[_REG_TRAPNO], Register::TYPE_GPR);
+	if (regName == "err")
+		return make_Register("err", regs_.regs[_REG_ERR], Register::TYPE_GPR);
+	if (regName == "rip")
+		return make_Register("rip", regs_.regs[_REG_RIP], Register::TYPE_GPR);
+	if (regName == "cs")
+		return make_Register("cs", regs_.regs[_REG_CS], Register::TYPE_GPR);
+	if (regName == "rflags")
+		return make_Register("rflags", regs_.regs[_REG_RFLAGS], Register::TYPE_GPR);
+	if (regName == "rsp")
+		return make_Register("rsp", regs_.regs[_REG_RSP], Register::TYPE_GPR);
+	if (regName == "ss")
+		return make_Register("ss", regs_.regs[_REG_SS], Register::TYPE_GPR);
+	
+	return Register();
+}
+
+//------------------------------------------------------------------------------
+// Name: instruction_pointer_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::instruction_pointer_register() const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	return make_Register("rip", PTRACE_REG_PC(&regs_), Register::TYPE_IP);
+}
+
+//------------------------------------------------------------------------------
+// Name: frame_pointer
+// Desc: returns what is conceptually the frame pointer for this platform
+//------------------------------------------------------------------------------
+edb::address_t PlatformState::frame_pointer() const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+#ifndef PTRACE_REG_FP
+#define PTRACE_REG_FP(r) (r)->regs[_REG_RBP]
+#endif
+	return PTRACE_REG_FP(&regs_);
+}
+
+//------------------------------------------------------------------------------
+// Name: instruction_pointer
+// Desc: returns the instruction pointer for this platform
+//------------------------------------------------------------------------------
+edb::address_t PlatformState::instruction_pointer() const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	return PTRACE_REG_PC(&regs_);
+}
+
+//------------------------------------------------------------------------------
+// Name: stack_pointer
+// Desc: returns the stack pointer for this platform
+//------------------------------------------------------------------------------
+edb::address_t PlatformState::stack_pointer() const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	return PTRACE_REG_SP(&regs_);
+}
+
+//------------------------------------------------------------------------------
+// Name: debug_register
+// Desc:
+//------------------------------------------------------------------------------
+edb::reg_t PlatformState::debug_register(size_t n) const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	return dr_.dr[n];
+}
+
+//------------------------------------------------------------------------------
+// Name: flags_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::flags_register() const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	return make_Register("rflags", regs_.regs[_REG_RFLAGS], Register::TYPE_GPR);
+}
+
+//------------------------------------------------------------------------------
+// Name: flags
+// Desc:
+//------------------------------------------------------------------------------
+edb::reg_t PlatformState::flags() const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+//------------------------------------------------------------------------------
+// Name: fpu_stack_pointer
+// Desc:
+//------------------------------------------------------------------------------
+int PlatformState::fpu_stack_pointer() const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	return 0;
+}
+
+//------------------------------------------------------------------------------
+// Name: fpu_register
+// Desc:
+//------------------------------------------------------------------------------
+edb::value80 PlatformState::fpu_register(size_t n) const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	edb::value80 val;
+	memset(&val, 0, sizeof(val));
+	return val;
+}
+
+//------------------------------------------------------------------------------
+// Name: fpu_register_is_empty
+// Desc: Returns true if Rn register is empty when treated in terms of FPU stack
+//------------------------------------------------------------------------------
+bool PlatformState::fpu_register_is_empty(size_t n) const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	return true;
+}
+
+//------------------------------------------------------------------------------
+// Name: fpu_register_tag_string
+// Desc:
+//------------------------------------------------------------------------------
+QString PlatformState::fpu_register_tag_string(size_t n) const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+edb::value16 PlatformState::fpu_control_word() const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	edb::value16 val;
+	memset(&val, 0, sizeof(val));
+	return val;
+}
+
+edb::value16 PlatformState::fpu_status_word() const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	edb::value16 val;
+	memset(&val, 0, sizeof(val));
+	return val;
+}
+
+edb::value16 PlatformState::fpu_tag_word() const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	edb::value16 val;
+	memset(&val, 0, sizeof(val));
+	return val;
+}
+
+//------------------------------------------------------------------------------
+// Name: adjust_stack
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::adjust_stack(int bytes) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	regs_.regs[_REG_RSP] += bytes;
+}
+
+//------------------------------------------------------------------------------
+// Name: clear
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::clear() {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	memset(&regs_, 0, sizeof(regs_));
+	memset(&fpreg_, 0, sizeof(fpreg_));
+	memset(&dr_, 0, sizeof(dr_));
+}
+
+//------------------------------------------------------------------------------
+// Name: empty
+// Desc:
+//------------------------------------------------------------------------------
+bool PlatformState::empty() const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+}
+
+//------------------------------------------------------------------------------
+// Name: set_debug_register
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::set_debug_register(size_t n, edb::reg_t value) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	dr_.dr[n] = value;
+}
+
+//------------------------------------------------------------------------------
+// Name: set_flags
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::set_flags(edb::reg_t flags) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	regs_.regs[_REG_RFLAGS] = flags;
+}
+
+//------------------------------------------------------------------------------
+// Name: set_instruction_pointer
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::set_instruction_pointer(edb::address_t value) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	regs_.regs[_REG_RIP] = value;
+}
+
+//------------------------------------------------------------------------------
+// Name: gp_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::gp_register(size_t n) const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	switch (n) {
+	case 0:
+		return make_Register("rdi", regs_.regs[_REG_RDI], Register::TYPE_GPR);
+	case 1:
+		return make_Register("rsi", regs_.regs[_REG_RSI], Register::TYPE_GPR);
+	case 2:
+		return make_Register("rdx", regs_.regs[_REG_RDX], Register::TYPE_GPR);
+	case 3:
+		return make_Register("rcx", regs_.regs[_REG_RCX], Register::TYPE_GPR);
+	case 4:
+		return make_Register("r8", regs_.regs[_REG_R8], Register::TYPE_GPR);
+	case 5:
+		return make_Register("r9", regs_.regs[_REG_R9], Register::TYPE_GPR);
+	case 6:
+		return make_Register("r10", regs_.regs[_REG_R10], Register::TYPE_GPR);
+	case 7:
+		return make_Register("r11", regs_.regs[_REG_R11], Register::TYPE_GPR);
+	case 8:
+		return make_Register("r12", regs_.regs[_REG_R12], Register::TYPE_GPR);
+	case 9:
+		return make_Register("r13", regs_.regs[_REG_R13], Register::TYPE_GPR);
+	case 10:
+		return make_Register("r14", regs_.regs[_REG_R14], Register::TYPE_GPR);
+	case 11:
+		return make_Register("r15", regs_.regs[_REG_R15], Register::TYPE_GPR);
+	case 12:
+		return make_Register("rbp", regs_.regs[_REG_RBP], Register::TYPE_GPR);
+	case 13:
+		return make_Register("rbx", regs_.regs[_REG_RBX], Register::TYPE_GPR);
+	case 14:
+		return make_Register("rax", regs_.regs[_REG_RAX], Register::TYPE_GPR);
+	case 15:
+		return make_Register("gs", regs_.regs[_REG_GS], Register::TYPE_GPR);
+	case 16:
+		return make_Register("fs", regs_.regs[_REG_FS], Register::TYPE_GPR);
+	case 17:
+		return make_Register("es", regs_.regs[_REG_ES], Register::TYPE_GPR);
+	case 18:
+		return make_Register("ds", regs_.regs[_REG_DS], Register::TYPE_GPR);
+	case 19:
+		return make_Register("trapno", regs_.regs[_REG_TRAPNO], Register::TYPE_GPR);
+	case 20:
+		return make_Register("err", regs_.regs[_REG_ERR], Register::TYPE_GPR);
+	case 21:
+		return make_Register("rip", regs_.regs[_REG_RIP], Register::TYPE_GPR);
+	case 22:
+		return make_Register("cs", regs_.regs[_REG_CS], Register::TYPE_GPR);
+	case 23:
+		return make_Register("rflags", regs_.regs[_REG_RFLAGS], Register::TYPE_GPR);
+	case 24:
+		return make_Register("rsp", regs_.regs[_REG_RSP], Register::TYPE_GPR);
+	case 25:
+		return make_Register("ss", regs_.regs[_REG_SS], Register::TYPE_GPR);
+	default:
+		return Register();
+	}
+}
+
+//------------------------------------------------------------------------------
+// Name: set_register
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::set_register(const Register &reg) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+}
+
+//------------------------------------------------------------------------------
+// Name: set_register
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::set_register(const QString &name, edb::reg_t value) {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	const QString lreg = name.toLower();
+	if(lreg == "rax") { regs_.regs[_REG_RAX] = value; }
+        else if(lreg == "rbx") { regs_.regs[_REG_RBX] = value; }
+        else if(lreg == "rcx") { regs_.regs[_REG_RCX] = value; }
+        else if(lreg == "rdx") { regs_.regs[_REG_RDX] = value; }
+        else if(lreg == "rbp") { regs_.regs[_REG_RBP] = value; }                                                                                                      
+        else if(lreg == "rsp") { regs_.regs[_REG_RSP] = value; }
+        else if(lreg == "rsi") { regs_.regs[_REG_RSI] = value; }
+        else if(lreg == "rdi") { regs_.regs[_REG_RDI] = value; }
+        else if(lreg == "r8") { regs_.regs[_REG_R8] = value; }
+        else if(lreg == "r9") { regs_.regs[_REG_R9] = value; }
+        else if(lreg == "r10") { regs_.regs[_REG_R10] = value; }
+        else if(lreg == "r11") { regs_.regs[_REG_R11] = value; }
+        else if(lreg == "r12") { regs_.regs[_REG_R12] = value; }
+        else if(lreg == "r13") { regs_.regs[_REG_R13] = value; }                                                                                                      
+        else if(lreg == "r14") { regs_.regs[_REG_R14] = value; }
+        else if(lreg == "r15") { regs_.regs[_REG_R15] = value; }
+        else if(lreg == "rip") { regs_.regs[_REG_RIP] = value; }
+        else if(lreg == "cs") { regs_.regs[_REG_CS] = value; }
+        else if(lreg == "ds") { regs_.regs[_REG_DS] = value; }
+        else if(lreg == "es") { regs_.regs[_REG_ES] = value; }
+        else if(lreg == "fs") { regs_.regs[_REG_FS] = value; }
+        else if(lreg == "gs") { regs_.regs[_REG_GS] = value; }
+        else if(lreg == "ss") { regs_.regs[_REG_SS] = value; }                                                                                                        
+        else if(lreg == "rflags") { regs_.regs[_REG_RFLAGS] = value; }
+}
+
+//------------------------------------------------------------------------------
+// Name: arch_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::arch_register(uint64_t type, size_t n) const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	return Register();
+}
+
+//------------------------------------------------------------------------------
+// Name: mmx_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::mmx_register(size_t n) const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	return Register();
+}
+
+//------------------------------------------------------------------------------
+// Name: xmm_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::xmm_register(size_t n) const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	return Register();
+}
+
+//------------------------------------------------------------------------------
+// Name: ymm_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::ymm_register(size_t n) const {
+	printf("%s(): %s:%d\n", __func__, __FILE__, __LINE__);
+
+	return Register();
+}
+}
