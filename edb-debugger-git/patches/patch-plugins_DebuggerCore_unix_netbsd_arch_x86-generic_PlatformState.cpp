$NetBSD$

--- plugins/DebuggerCore/unix/netbsd/arch/x86-generic/PlatformState.cpp.orig	2019-06-16 01:25:12.631996478 +0000
+++ plugins/DebuggerCore/unix/netbsd/arch/x86-generic/PlatformState.cpp
@@ -0,0 +1,360 @@
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
+constexpr const char *PlatformState::X86::IP64Name;
+constexpr const char *PlatformState::X86::IP32Name;
+constexpr const char *PlatformState::X86::IP16Name;
+constexpr const char *PlatformState::X86::origEAXName;
+constexpr const char *PlatformState::X86::origRAXName;
+constexpr const char *PlatformState::X86::flags64Name;
+constexpr const char *PlatformState::X86::flags32Name;
+constexpr const char *PlatformState::X86::flags16Name;
+
+const std::array<const char *, MAX_GPR_COUNT> PlatformState::X86::GPReg64Names = {
+	"rax",
+	"rcx",
+	"rdx",
+	"rbx",
+	"rsp",
+	"rbp",
+	"rsi",
+	"rdi",
+	"r8",
+	"r9",
+	"r10",
+	"r11",
+	"r12",
+	"r13",
+	"r14",
+	"r15"
+};
+
+const std::array<const char *, MAX_GPR_COUNT> PlatformState::X86::GPReg32Names = {
+	"eax",
+	"ecx",
+	"edx",
+	"ebx",
+	"esp",
+	"ebp",
+	"esi",
+	"edi",
+	"r8d",
+	"r9d",
+	"r10d",
+	"r11d",
+	"r12d",
+	"r13d",
+	"r14d",
+	"r15d"
+};
+
+const std::array<const char *, MAX_GPR_COUNT> PlatformState::X86::GPReg16Names = {
+	"ax",
+	"cx",
+	"dx",
+	"bx",
+	"sp",
+	"bp",
+	"si",
+	"di",
+	"r8w",
+	"r9w",
+	"r10w",
+	"r11w",
+	"r12w",
+	"r13w",
+	"r14w",
+	"r15w"
+};
+
+const std::array<const char *, MAX_GPR_LOW_ADDRESSABLE_COUNT> PlatformState::X86::GPReg8LNames = {
+	"al",
+	"cl",
+	"dl",
+	"bl",
+	"spl",
+	"bpl",
+	"sil",
+	"dil",
+	"r8b",
+	"r9b",
+	"r10b",
+	"r11b",
+	"r12b",
+	"r13b",
+	"r14b",
+	"r15b"
+};
+
+const std::array<const char *, MAX_GPR_HIGH_ADDRESSABLE_COUNT> PlatformState::X86::GPReg8HNames = {
+	"ah",
+	"ch",
+	"dh",
+	"bh"
+};
+
+const std::array<const char *, MAX_SEG_REG_COUNT> PlatformState::X86::segRegNames  = {
+	"es",
+	"cs",
+	"ss",
+	"ds",
+	"fs",
+	"gs"
+};
+
+void PlatformState::fillFrom(const UserRegsStructX86_64 &regs) {
+}
+
+void PlatformState::fillStruct(UserRegsStructX86_64 &regs) const {
+}
+
+void PlatformState::X86::clear() {
+}
+
+bool PlatformState::X86::empty() const {
+}
+
+//------------------------------------------------------------------------------
+// Name: PlatformState
+// Desc:
+//------------------------------------------------------------------------------
+PlatformState::PlatformState() {
+    this->clear();
+}
+
+//------------------------------------------------------------------------------
+// Name: PlatformState::clone
+// Desc: makes a copy of the state object
+//------------------------------------------------------------------------------
+std::unique_ptr<IState> PlatformState::clone() const {
+	return std::make_unique<PlatformState>(*this);
+}
+
+//------------------------------------------------------------------------------
+// Name: flags_to_string
+// Desc: returns the flags in a string form appropriate for this platform
+//------------------------------------------------------------------------------
+QString PlatformState::flags_to_string(edb::reg_t flags) const {
+}
+
+//------------------------------------------------------------------------------
+// Name: flags_to_string
+// Desc: returns the flags in a string form appropriate for this platform
+//------------------------------------------------------------------------------
+QString PlatformState::flags_to_string() const {
+}
+
+template <size_t BitSize = 0, class Names, class Regs>
+Register findRegisterValue(const Names &names, const Regs &regs, const QString &regName, Register::Type type, size_t maxNames, int shift = 0) {
+}
+
+//------------------------------------------------------------------------------
+// Name: value
+// Desc: returns a Register object which represents the register with the name
+//       supplied
+//------------------------------------------------------------------------------
+Register PlatformState::value(const QString &reg) const {
+}
+
+//------------------------------------------------------------------------------
+// Name: instruction_pointer_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::instruction_pointer_register() const {
+}
+
+//------------------------------------------------------------------------------
+// Name: frame_pointer
+// Desc: returns what is conceptually the frame pointer for this platform
+//------------------------------------------------------------------------------
+edb::address_t PlatformState::frame_pointer() const {
+}
+
+//------------------------------------------------------------------------------
+// Name: instruction_pointer
+// Desc: returns the instruction pointer for this platform
+//------------------------------------------------------------------------------
+edb::address_t PlatformState::instruction_pointer() const {
+}
+
+//------------------------------------------------------------------------------
+// Name: stack_pointer
+// Desc: returns the stack pointer for this platform
+//------------------------------------------------------------------------------
+edb::address_t PlatformState::stack_pointer() const {
+}
+
+//------------------------------------------------------------------------------
+// Name: debug_register
+// Desc:
+//------------------------------------------------------------------------------
+edb::reg_t PlatformState::debug_register(size_t n) const {
+}
+
+//------------------------------------------------------------------------------
+// Name: flags_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::flags_register() const {
+}
+
+//------------------------------------------------------------------------------
+// Name: flags
+// Desc:
+//------------------------------------------------------------------------------
+edb::reg_t PlatformState::flags() const {
+}
+
+//------------------------------------------------------------------------------
+// Name: fpu_stack_pointer
+// Desc:
+//------------------------------------------------------------------------------
+int PlatformState::fpu_stack_pointer() const {
+}
+
+//------------------------------------------------------------------------------
+// Name: fpu_register
+// Desc:
+//------------------------------------------------------------------------------
+edb::value80 PlatformState::fpu_register(size_t n) const {
+}
+
+//------------------------------------------------------------------------------
+// Name: fpu_register_is_empty
+// Desc: Returns true if Rn register is empty when treated in terms of FPU stack
+//------------------------------------------------------------------------------
+bool PlatformState::fpu_register_is_empty(size_t n) const {
+}
+
+//------------------------------------------------------------------------------
+// Name: fpu_register_tag_string
+// Desc:
+//------------------------------------------------------------------------------
+QString PlatformState::fpu_register_tag_string(size_t n) const {
+}
+
+edb::value16 PlatformState::fpu_control_word() const {
+}
+
+edb::value16 PlatformState::fpu_status_word() const {
+}
+
+edb::value16 PlatformState::fpu_tag_word() const {
+}
+
+//------------------------------------------------------------------------------
+// Name: adjust_stack
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::adjust_stack(int bytes) {
+}
+
+//------------------------------------------------------------------------------
+// Name: clear
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::clear() {
+}
+
+//------------------------------------------------------------------------------
+// Name: empty
+// Desc:
+//------------------------------------------------------------------------------
+bool PlatformState::empty() const {
+}
+
+//------------------------------------------------------------------------------
+// Name: set_debug_register
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::set_debug_register(size_t n, edb::reg_t value) {
+}
+
+//------------------------------------------------------------------------------
+// Name: set_flags
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::set_flags(edb::reg_t flags) {
+}
+
+//------------------------------------------------------------------------------
+// Name: set_instruction_pointer
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::set_instruction_pointer(edb::address_t value) {
+}
+
+//------------------------------------------------------------------------------
+// Name: gp_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::gp_register(size_t n) const {
+}
+
+//------------------------------------------------------------------------------
+// Name: set_register
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::set_register(const Register &reg) {
+}
+
+//------------------------------------------------------------------------------
+// Name: set_register
+// Desc:
+//------------------------------------------------------------------------------
+void PlatformState::set_register(const QString &name, edb::reg_t value) {
+}
+
+//------------------------------------------------------------------------------
+// Name: arch_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::arch_register(uint64_t type, size_t n) const {
+}
+
+//------------------------------------------------------------------------------
+// Name: mmx_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::mmx_register(size_t n) const {
+}
+
+//------------------------------------------------------------------------------
+// Name: xmm_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::xmm_register(size_t n) const {
+}
+
+//------------------------------------------------------------------------------
+// Name: ymm_register
+// Desc:
+//------------------------------------------------------------------------------
+Register PlatformState::ymm_register(size_t n) const {
+}
+}
