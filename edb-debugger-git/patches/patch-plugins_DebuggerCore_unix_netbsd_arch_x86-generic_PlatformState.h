$NetBSD$

--- plugins/DebuggerCore/unix/netbsd/arch/x86-generic/PlatformState.h.orig	2019-06-16 23:21:29.972787537 +0000
+++ plugins/DebuggerCore/unix/netbsd/arch/x86-generic/PlatformState.h
@@ -0,0 +1,243 @@
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
+#ifndef PLATFORMSTATE_20110330_H_
+#define PLATFORMSTATE_20110330_H_
+
+#include "IState.h"
+#include "Types.h"
+#include "PrStatus.h"
+#include "edb.h"
+#include <cstddef>
+
+#include <sys/types.h>
+#include <sys/ptrace.h>
+#include <machine/reg.h>
+
+namespace DebuggerCorePlugin {
+
+using std::size_t;
+
+static constexpr size_t IA32_GPR_COUNT                  = 8;
+static constexpr size_t IA32_GPR_LOW_ADDRESSABLE_COUNT  = 4; // al,cl,dl,bl
+static constexpr size_t AMD64_GPR_COUNT                 = 16;
+static constexpr size_t AMD64_GPR_LOW_ADDRESSABLE_COUNT = 16; // all GPRs' low bytes are addressable in 64 bit mode
+static constexpr size_t IA32_XMM_REG_COUNT              = IA32_GPR_COUNT;
+static constexpr size_t AMD64_XMM_REG_COUNT             = AMD64_GPR_COUNT;
+static constexpr size_t IA32_YMM_REG_COUNT              = IA32_GPR_COUNT;
+static constexpr size_t AMD64_YMM_REG_COUNT             = AMD64_GPR_COUNT;
+static constexpr size_t IA32_ZMM_REG_COUNT              = IA32_GPR_COUNT;
+static constexpr size_t AMD64_ZMM_REG_COUNT             = 32;
+static constexpr size_t MAX_GPR_COUNT                   = AMD64_GPR_COUNT;
+static constexpr size_t MAX_GPR_LOW_ADDRESSABLE_COUNT   = AMD64_GPR_LOW_ADDRESSABLE_COUNT;
+static constexpr size_t MAX_GPR_HIGH_ADDRESSABLE_COUNT  = 4; // ah,ch,dh,bh
+static constexpr size_t MAX_DBG_REG_COUNT               = 8;
+static constexpr size_t MAX_SEG_REG_COUNT               = 6;
+static constexpr size_t MAX_FPU_REG_COUNT               = 8;
+static constexpr size_t MAX_MMX_REG_COUNT               = MAX_FPU_REG_COUNT;
+static constexpr size_t MAX_XMM_REG_COUNT               = AMD64_XMM_REG_COUNT;
+static constexpr size_t MAX_YMM_REG_COUNT               = AMD64_YMM_REG_COUNT;
+static constexpr size_t MAX_ZMM_REG_COUNT               = AMD64_ZMM_REG_COUNT;
+
+// Dummies to avoid missing compile-time checks for conversion code
+// Actual layout is irrelevant since the code is not going to be executed
+struct UserRegsStructX86 {
+	uint32_t ebx;
+	uint32_t ecx;
+	uint32_t edx;
+	uint32_t esi;
+	uint32_t edi;
+	uint32_t ebp;
+	uint32_t eax;
+	uint32_t xds;
+	uint32_t xes;
+	uint32_t xfs;
+	uint32_t xgs;
+	uint32_t orig_eax;
+	uint32_t eip;
+	uint32_t xcs;
+	uint32_t eflags;
+	uint32_t esp;
+	uint32_t xss;
+};
+
+struct UserFPXRegsStructX86 {
+	uint16_t cwd;
+	uint16_t swd;
+	uint16_t twd;
+	uint16_t fop; // last instruction opcode
+	uint32_t fip; // last instruction EIP
+	uint32_t fcs; // last instruction CS
+	uint32_t foo; // last operand offset
+	uint32_t fos; // last operand selector
+	uint32_t mxcsr;
+	uint32_t reserved;
+	uint32_t st_space[32];  /* 8*16 bytes for each FP-reg = 128 bytes */
+	uint32_t xmm_space[32]; /* 8*16 bytes for each XMM-reg = 128 bytes */
+	uint32_t padding[56];
+};
+
+struct UserFPRegsStructX86 {
+	uint32_t cwd;
+	uint32_t swd;
+	uint32_t twd;
+	uint32_t fip; // last instruction EIP
+	uint32_t fcs; // last instruction CS
+	uint32_t foo; // last operand offset
+	uint32_t fos; // last operand selector
+	uint32_t st_space[20];
+};
+
+
+// Masks for XCR0 feature enabled bits
+#define X86_XSTATE_X87_MASK X87_XSTATE_X87
+#define X86_XSTATE_SSE_MASK (X87_XSTATE_X87 | X87_XSTATE_SSE)
+
+struct X86XState {
+	uint16_t cwd;
+	uint16_t swd;
+	uint16_t twd;
+	uint16_t fop;   // last instruction opcode
+	uint32_t fioff; // last instruction EIP
+	uint32_t fiseg; // last instruction CS in 32 bit mode, high 32 bits of RIP in 64 bit mode
+	uint32_t fooff; // last operand offset
+	uint32_t foseg; // last operand selector in 32 bit mode, high 32 bits of FDP in 64 bit mode
+	uint32_t mxcsr;
+	uint32_t mxcsr_mask;         // FIXME
+	uint8_t  st_space[16 * 8];   // 8 16-byte fields
+	uint8_t  xmm_space[16 * 16]; // 16 16-byte fields, regardless of XMM_REG_COUNT
+	uint8_t  padding[48];
+
+	union {
+		uint64_t xcr0;
+		uint8_t  sw_usable_bytes[48];
+	};
+
+	union {
+		uint64_t xstate_bv;
+		uint8_t  xstate_hdr_bytes[64];
+	};
+
+	uint8_t ymmh_space[16 * 16];
+
+	// The extended state feature bits
+	enum FeatureBit : uint64_t {
+		FEATURE_X87 = 1 << 0,
+		FEATURE_SSE = 1 << 1,
+		FEATURE_AVX = 1 << 2,
+		// MPX adds two feature bits
+		FEATURE_BNDREGS = 1 << 3,
+		FEATURE_BNDCFG  = 1 << 4,
+		FEATURE_MPX     = FEATURE_BNDREGS | FEATURE_BNDCFG,
+		// AVX-512 adds three feature bits
+		FEATURE_K      = 1 << 5,
+		FEATURE_ZMM_H  = 1 << 6,
+		FEATURE_ZMM    = 1 << 7,
+		FEATURE_AVX512 = FEATURE_K | FEATURE_ZMM_H | FEATURE_ZMM,
+	};
+
+	// Possible sizes of X86_XSTATE
+	static constexpr size_t XSAVE_NONEXTENDED_SIZE = 576;
+	static constexpr size_t SSE_SIZE               = XSAVE_NONEXTENDED_SIZE;
+	static constexpr size_t AVX_SIZE               = 832;
+	static constexpr size_t BNDREGS_SIZE           = 1024;
+	static constexpr size_t BNDCFG_SIZE            = 1088;
+	static constexpr size_t AVX512_SIZE            = 2688;
+	static constexpr size_t MAX_SIZE               = 2688;
+};
+
+static_assert(std::is_standard_layout<X86XState>::value, "X86XState struct is supposed to have standard layout");
+static_assert(offsetof(X86XState, st_space) == 32, "ST space should appear at offset 32");
+static_assert(offsetof(X86XState, xmm_space) == 160, "XMM space should appear at offset 160");
+static_assert(offsetof(X86XState, xcr0) == 464, "XCR0 should appear at offset 464");
+static_assert(offsetof(X86XState, ymmh_space) == 576, "YMM_H space should appear at offset 576");
+
+class PlatformState final : public IState {
+	friend class DebuggerCore;
+	friend class PlatformThread;
+
+public:
+	PlatformState();
+
+public:
+	std::unique_ptr<IState> clone() const override;
+
+public:
+	QString flags_to_string() const override;
+	QString flags_to_string(edb::reg_t flags) const override;
+	Register value(const QString &reg) const override;
+	Register instruction_pointer_register() const override;
+	Register flags_register() const override;
+	edb::address_t frame_pointer() const override;
+	edb::address_t instruction_pointer() const override;
+	edb::address_t stack_pointer() const override;
+	edb::reg_t debug_register(size_t n) const override;
+	edb::reg_t flags() const override;
+	int fpu_stack_pointer() const override;
+	edb::value80 fpu_register(size_t n) const override;
+	bool fpu_register_is_empty(size_t n) const override;
+	QString fpu_register_tag_string(size_t n) const override;
+	edb::value16 fpu_control_word() const override;
+	edb::value16 fpu_status_word() const override;
+	edb::value16 fpu_tag_word() const override;
+	void adjust_stack(int bytes) override;
+	void clear() override;
+	bool empty() const override;
+	void set_debug_register(size_t n, edb::reg_t value) override;
+	void set_flags(edb::reg_t flags) override;
+	void set_instruction_pointer(edb::address_t value) override;
+	void set_register(const Register &reg) override;
+	void set_register(const QString &name, edb::reg_t value) override;
+
+	Register arch_register(uint64_t type, size_t n) const override;
+	Register gp_register(size_t n) const override;
+
+	bool is64Bit() const {
+		return edb::v1::debuggeeIs64Bit();
+	}
+
+	size_t dbg_reg_count() const {
+		return MAX_DBG_REG_COUNT;
+	}
+
+	size_t seg_reg_count() const {
+		return MAX_SEG_REG_COUNT;
+	}
+
+	size_t gpr_low_addressable_count() const {
+		return is64Bit() ? AMD64_GPR_LOW_ADDRESSABLE_COUNT : IA32_GPR_LOW_ADDRESSABLE_COUNT;
+	}
+
+	size_t gpr_high_addressable_count() const {
+		return MAX_GPR_HIGH_ADDRESSABLE_COUNT;
+	}
+
+private:
+	Register mmx_register(size_t n) const ;
+	Register xmm_register(size_t n) const ;
+	Register ymm_register(size_t n) const ;
+
+private:
+	struct reg regs_;
+	struct fpreg fpreg_;
+	struct dbreg dr_;
+};
+
+}
+
+#endif
