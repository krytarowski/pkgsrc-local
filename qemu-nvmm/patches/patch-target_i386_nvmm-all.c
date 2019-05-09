$NetBSD$

--- target/i386/nvmm-all.c.orig	2019-05-09 02:48:13.973231637 +0000
+++ target/i386/nvmm-all.c
@@ -0,0 +1,1167 @@
+/*
+ * Copyright (c) 2018-2019 Maxime Villard, All rights reserved.
+ *
+ * NetBSD Virtual Machine Monitor (NVMM) accelerator for QEMU.
+ *
+ * This work is licensed under the terms of the GNU GPL, version 2 or later.
+ * See the COPYING file in the top-level directory.
+ */
+
+#include "qemu/osdep.h"
+#include "cpu.h"
+#include "exec/address-spaces.h"
+#include "exec/ioport.h"
+#include "qemu-common.h"
+#include "strings.h"
+#include "sysemu/accel.h"
+#include "sysemu/nvmm.h"
+#include "sysemu/sysemu.h"
+#include "sysemu/cpus.h"
+#include "qemu/main-loop.h"
+#include "hw/boards.h"
+#include "qemu/error-report.h"
+#include "qemu/queue.h"
+#include "qapi/error.h"
+#include "migration/blocker.h"
+
+#include <nvmm.h>
+
+static bool nvmm_allowed = false;
+
+struct nvmm_vcpu {
+    nvmm_cpuid_t cpuid;
+    uint8_t tpr;
+    bool stop;
+
+    /* Window-exiting for INTs/NMIs. */
+    bool int_window_exit;
+    bool nmi_window_exit;
+
+    /* The guest is in an interrupt shadow (POP SS, etc). */
+    bool int_shadow;
+};
+
+static struct {
+    struct nvmm_machine mach;
+} nvmm_global;
+
+static struct nvmm_vcpu *
+get_nvmm_vcpu(CPUState *cpu)
+{
+    return (struct nvmm_vcpu *)cpu->hax_vcpu;
+}
+
+static struct nvmm_machine *
+get_nvmm_mach(void)
+{
+    return &nvmm_global.mach;
+}
+
+/* -------------------------------------------------------------------------- */
+
+static void
+nvmm_set_segment(struct nvmm_x64_state_seg *nseg, const SegmentCache *qseg)
+{
+    uint32_t attrib = qseg->flags;
+
+    nseg->selector = qseg->selector;
+    nseg->limit = qseg->limit;
+    nseg->base = qseg->base;
+    nseg->attrib.type = __SHIFTOUT(attrib, DESC_TYPE_MASK);
+    nseg->attrib.s = __SHIFTOUT(attrib, DESC_S_MASK);
+    nseg->attrib.dpl = __SHIFTOUT(attrib, DESC_DPL_MASK);
+    nseg->attrib.p = __SHIFTOUT(attrib, DESC_P_MASK);
+    nseg->attrib.avl = __SHIFTOUT(attrib, DESC_AVL_MASK);
+    nseg->attrib.l = __SHIFTOUT(attrib, DESC_L_MASK);
+    nseg->attrib.def = __SHIFTOUT(attrib, DESC_B_MASK);
+    nseg->attrib.g = __SHIFTOUT(attrib, DESC_G_MASK);
+}
+
+static void
+nvmm_set_registers(CPUState *cpu)
+{
+    struct CPUX86State *env = (CPUArchState *)(cpu->env_ptr);
+    struct nvmm_machine *mach = get_nvmm_mach();
+    struct nvmm_vcpu *vcpu = get_nvmm_vcpu(cpu);
+    struct nvmm_x64_state state;
+    uint64_t bitmap;
+    size_t i;
+    int ret;
+
+    assert(cpu_is_stopped(cpu) || qemu_cpu_is_self(cpu));
+
+    /* GPRs. */
+    state.gprs[NVMM_X64_GPR_RAX] = env->regs[R_EAX];
+    state.gprs[NVMM_X64_GPR_RCX] = env->regs[R_ECX];
+    state.gprs[NVMM_X64_GPR_RDX] = env->regs[R_EDX];
+    state.gprs[NVMM_X64_GPR_RBX] = env->regs[R_EBX];
+    state.gprs[NVMM_X64_GPR_RSP] = env->regs[R_ESP];
+    state.gprs[NVMM_X64_GPR_RBP] = env->regs[R_EBP];
+    state.gprs[NVMM_X64_GPR_RSI] = env->regs[R_ESI];
+    state.gprs[NVMM_X64_GPR_RDI] = env->regs[R_EDI];
+    state.gprs[NVMM_X64_GPR_R8]  = env->regs[R_R8];
+    state.gprs[NVMM_X64_GPR_R9]  = env->regs[R_R9];
+    state.gprs[NVMM_X64_GPR_R10] = env->regs[R_R10];
+    state.gprs[NVMM_X64_GPR_R11] = env->regs[R_R11];
+    state.gprs[NVMM_X64_GPR_R12] = env->regs[R_R12];
+    state.gprs[NVMM_X64_GPR_R13] = env->regs[R_R13];
+    state.gprs[NVMM_X64_GPR_R14] = env->regs[R_R14];
+    state.gprs[NVMM_X64_GPR_R15] = env->regs[R_R15];
+
+    /* RIP and RFLAGS. */
+    state.gprs[NVMM_X64_GPR_RIP] = env->eip;
+    state.gprs[NVMM_X64_GPR_RFLAGS] = env->eflags;
+
+    /* Segments. */
+    nvmm_set_segment(&state.segs[NVMM_X64_SEG_CS], &env->segs[R_CS]);
+    nvmm_set_segment(&state.segs[NVMM_X64_SEG_DS], &env->segs[R_DS]);
+    nvmm_set_segment(&state.segs[NVMM_X64_SEG_ES], &env->segs[R_ES]);
+    nvmm_set_segment(&state.segs[NVMM_X64_SEG_FS], &env->segs[R_FS]);
+    nvmm_set_segment(&state.segs[NVMM_X64_SEG_GS], &env->segs[R_GS]);
+    nvmm_set_segment(&state.segs[NVMM_X64_SEG_SS], &env->segs[R_SS]);
+
+    /* Special segments. */
+    nvmm_set_segment(&state.segs[NVMM_X64_SEG_GDT], &env->gdt);
+    nvmm_set_segment(&state.segs[NVMM_X64_SEG_LDT], &env->ldt);
+    nvmm_set_segment(&state.segs[NVMM_X64_SEG_TR], &env->tr);
+    nvmm_set_segment(&state.segs[NVMM_X64_SEG_IDT], &env->idt);
+
+    /* Control registers. */
+    state.crs[NVMM_X64_CR_CR0] = env->cr[0];
+    state.crs[NVMM_X64_CR_CR2] = env->cr[2];
+    state.crs[NVMM_X64_CR_CR3] = env->cr[3];
+    state.crs[NVMM_X64_CR_CR4] = env->cr[4];
+    state.crs[NVMM_X64_CR_CR8] = vcpu->tpr;
+    state.crs[NVMM_X64_CR_XCR0] = env->xcr0;
+
+    /* Debug registers. */
+    state.drs[NVMM_X64_DR_DR0] = env->dr[0];
+    state.drs[NVMM_X64_DR_DR1] = env->dr[1];
+    state.drs[NVMM_X64_DR_DR2] = env->dr[2];
+    state.drs[NVMM_X64_DR_DR3] = env->dr[3];
+    state.drs[NVMM_X64_DR_DR6] = env->dr[6];
+    state.drs[NVMM_X64_DR_DR7] = env->dr[7];
+
+    /* FPU. */
+    state.fpu.fx_cw = env->fpuc;
+    state.fpu.fx_sw = (env->fpus & ~0x3800) | ((env->fpstt & 0x7) << 11);
+    state.fpu.fx_tw = 0;
+    for (i = 0; i < 8; i++) {
+        state.fpu.fx_tw |= (!env->fptags[i]) << i;
+    }
+    state.fpu.fx_opcode = env->fpop;
+    state.fpu.fx_ip.fa_64 = env->fpip;
+    state.fpu.fx_dp.fa_64 = env->fpdp;
+    state.fpu.fx_mxcsr = env->mxcsr;
+    state.fpu.fx_mxcsr_mask = 0x0000FFFF;
+    assert(sizeof(state.fpu.fx_87_ac) == sizeof(env->fpregs));
+    memcpy(state.fpu.fx_87_ac, env->fpregs, sizeof(env->fpregs));
+    for (i = 0; i < 16; i++) {
+        memcpy(&state.fpu.fx_xmm[i].xmm_bytes[0],
+            &env->xmm_regs[i].ZMM_Q(0), 8);
+        memcpy(&state.fpu.fx_xmm[i].xmm_bytes[8],
+            &env->xmm_regs[i].ZMM_Q(1), 8);
+    }
+
+    /* MSRs. */
+    state.msrs[NVMM_X64_MSR_EFER] = env->efer;
+    state.msrs[NVMM_X64_MSR_STAR] = env->star;
+#ifdef TARGET_X86_64
+    state.msrs[NVMM_X64_MSR_LSTAR] = env->lstar;
+    state.msrs[NVMM_X64_MSR_CSTAR] = env->cstar;
+    state.msrs[NVMM_X64_MSR_SFMASK] = env->fmask;
+    state.msrs[NVMM_X64_MSR_KERNELGSBASE] = env->kernelgsbase;
+#endif
+    state.msrs[NVMM_X64_MSR_SYSENTER_CS]  = env->sysenter_cs;
+    state.msrs[NVMM_X64_MSR_SYSENTER_ESP] = env->sysenter_esp;
+    state.msrs[NVMM_X64_MSR_SYSENTER_EIP] = env->sysenter_eip;
+    state.msrs[NVMM_X64_MSR_PAT] = env->pat;
+    state.msrs[NVMM_X64_MSR_TSC] = env->tsc;
+
+    bitmap =
+        NVMM_X64_STATE_SEGS |
+        NVMM_X64_STATE_GPRS |
+        NVMM_X64_STATE_CRS  |
+        NVMM_X64_STATE_DRS  |
+        NVMM_X64_STATE_MSRS |
+        NVMM_X64_STATE_FPU;
+
+    ret = nvmm_vcpu_setstate(mach, vcpu->cpuid, &state, bitmap);
+    if (ret == -1) {
+        error_report("NVMM: Failed to set virtual processor context,"
+            " error=%d", errno);
+    }
+}
+
+static void
+nvmm_get_segment(SegmentCache *qseg, const struct nvmm_x64_state_seg *nseg)
+{
+    qseg->selector = nseg->selector;
+    qseg->limit = nseg->limit;
+    qseg->base = nseg->base;
+
+    qseg->flags =
+        __SHIFTIN((uint32_t)nseg->attrib.type, DESC_TYPE_MASK) |
+        __SHIFTIN((uint32_t)nseg->attrib.s, DESC_S_MASK) |
+        __SHIFTIN((uint32_t)nseg->attrib.dpl, DESC_DPL_MASK) |
+        __SHIFTIN((uint32_t)nseg->attrib.p, DESC_P_MASK) |
+        __SHIFTIN((uint32_t)nseg->attrib.avl, DESC_AVL_MASK) |
+        __SHIFTIN((uint32_t)nseg->attrib.l, DESC_L_MASK) |
+        __SHIFTIN((uint32_t)nseg->attrib.def, DESC_B_MASK) |
+        __SHIFTIN((uint32_t)nseg->attrib.g, DESC_G_MASK);
+}
+
+static void
+nvmm_get_registers(CPUState *cpu)
+{
+    struct CPUX86State *env = (CPUArchState *)(cpu->env_ptr);
+    struct nvmm_machine *mach = get_nvmm_mach();
+    struct nvmm_vcpu *vcpu = get_nvmm_vcpu(cpu);
+    X86CPU *x86_cpu = X86_CPU(cpu);
+    struct nvmm_x64_state state;
+    uint64_t bitmap, tpr;
+    size_t i;
+    int ret;
+
+    assert(cpu_is_stopped(cpu) || qemu_cpu_is_self(cpu));
+
+    bitmap =
+        NVMM_X64_STATE_SEGS |
+        NVMM_X64_STATE_GPRS |
+        NVMM_X64_STATE_CRS  |
+        NVMM_X64_STATE_DRS  |
+        NVMM_X64_STATE_MSRS |
+        NVMM_X64_STATE_FPU;
+
+    ret = nvmm_vcpu_getstate(mach, vcpu->cpuid, &state, bitmap);
+    if (ret == -1) {
+        error_report("NVMM: Failed to get virtual processor context,"
+            " error=%d", errno);
+    }
+
+    /* GPRs. */
+    env->regs[R_EAX] = state.gprs[NVMM_X64_GPR_RAX];
+    env->regs[R_ECX] = state.gprs[NVMM_X64_GPR_RCX];
+    env->regs[R_EDX] = state.gprs[NVMM_X64_GPR_RDX];
+    env->regs[R_EBX] = state.gprs[NVMM_X64_GPR_RBX];
+    env->regs[R_ESP] = state.gprs[NVMM_X64_GPR_RSP];
+    env->regs[R_EBP] = state.gprs[NVMM_X64_GPR_RBP];
+    env->regs[R_ESI] = state.gprs[NVMM_X64_GPR_RSI];
+    env->regs[R_EDI] = state.gprs[NVMM_X64_GPR_RDI];
+    env->regs[R_R8]  = state.gprs[NVMM_X64_GPR_R8];
+    env->regs[R_R9]  = state.gprs[NVMM_X64_GPR_R9];
+    env->regs[R_R10] = state.gprs[NVMM_X64_GPR_R10];
+    env->regs[R_R11] = state.gprs[NVMM_X64_GPR_R11];
+    env->regs[R_R12] = state.gprs[NVMM_X64_GPR_R12];
+    env->regs[R_R13] = state.gprs[NVMM_X64_GPR_R13];
+    env->regs[R_R14] = state.gprs[NVMM_X64_GPR_R14];
+    env->regs[R_R15] = state.gprs[NVMM_X64_GPR_R15];
+
+    /* RIP and RFLAGS. */
+    env->eip = state.gprs[NVMM_X64_GPR_RIP];
+    env->eflags = state.gprs[NVMM_X64_GPR_RFLAGS];
+
+    /* Segments. */
+    nvmm_get_segment(&env->segs[R_ES], &state.segs[NVMM_X64_SEG_ES]);
+    nvmm_get_segment(&env->segs[R_CS], &state.segs[NVMM_X64_SEG_CS]);
+    nvmm_get_segment(&env->segs[R_SS], &state.segs[NVMM_X64_SEG_SS]);
+    nvmm_get_segment(&env->segs[R_DS], &state.segs[NVMM_X64_SEG_DS]);
+    nvmm_get_segment(&env->segs[R_FS], &state.segs[NVMM_X64_SEG_FS]);
+    nvmm_get_segment(&env->segs[R_GS], &state.segs[NVMM_X64_SEG_GS]);
+
+    /* Special segments. */
+    nvmm_get_segment(&env->gdt, &state.segs[NVMM_X64_SEG_GDT]);
+    nvmm_get_segment(&env->ldt, &state.segs[NVMM_X64_SEG_LDT]);
+    nvmm_get_segment(&env->tr, &state.segs[NVMM_X64_SEG_TR]);
+    nvmm_get_segment(&env->idt, &state.segs[NVMM_X64_SEG_IDT]);
+
+    /* Control registers. */
+    env->cr[0] = state.crs[NVMM_X64_CR_CR0];
+    env->cr[2] = state.crs[NVMM_X64_CR_CR2];
+    env->cr[3] = state.crs[NVMM_X64_CR_CR3];
+    env->cr[4] = state.crs[NVMM_X64_CR_CR4];
+    tpr = state.crs[NVMM_X64_CR_CR8];
+    if (tpr != vcpu->tpr) {
+        vcpu->tpr = tpr;
+        cpu_set_apic_tpr(x86_cpu->apic_state, tpr);
+    }
+    env->xcr0 = state.crs[NVMM_X64_CR_XCR0];
+
+    /* Debug registers. */
+    env->dr[0] = state.drs[NVMM_X64_DR_DR0];
+    env->dr[1] = state.drs[NVMM_X64_DR_DR1];
+    env->dr[2] = state.drs[NVMM_X64_DR_DR2];
+    env->dr[3] = state.drs[NVMM_X64_DR_DR3];
+    env->dr[6] = state.drs[NVMM_X64_DR_DR6];
+    env->dr[7] = state.drs[NVMM_X64_DR_DR7];
+
+    /* FPU. */
+    env->fpuc = state.fpu.fx_cw;
+    env->fpstt = (state.fpu.fx_sw >> 11) & 0x7;
+    env->fpus = state.fpu.fx_sw & ~0x3800;
+    for (i = 0; i < 8; i++) {
+        env->fptags[i] = !((state.fpu.fx_tw >> i) & 1);
+    }
+    env->fpop = state.fpu.fx_opcode;
+    env->fpip = state.fpu.fx_ip.fa_64;
+    env->fpdp = state.fpu.fx_dp.fa_64;
+    env->mxcsr = state.fpu.fx_mxcsr;
+    assert(sizeof(state.fpu.fx_87_ac) == sizeof(env->fpregs));
+    memcpy(env->fpregs, state.fpu.fx_87_ac, sizeof(env->fpregs));
+    for (i = 0; i < 16; i++) {
+        memcpy(&env->xmm_regs[i].ZMM_Q(0),
+            &state.fpu.fx_xmm[i].xmm_bytes[0], 8);
+        memcpy(&env->xmm_regs[i].ZMM_Q(1),
+            &state.fpu.fx_xmm[i].xmm_bytes[8], 8);
+    }
+
+    /* MSRs. */
+    env->efer = state.msrs[NVMM_X64_MSR_EFER];
+    env->star = state.msrs[NVMM_X64_MSR_STAR];
+#ifdef TARGET_X86_64
+    env->lstar = state.msrs[NVMM_X64_MSR_LSTAR];
+    env->cstar = state.msrs[NVMM_X64_MSR_CSTAR];
+    env->fmask = state.msrs[NVMM_X64_MSR_SFMASK];
+    env->kernelgsbase = state.msrs[NVMM_X64_MSR_KERNELGSBASE];
+#endif
+    env->sysenter_cs  = state.msrs[NVMM_X64_MSR_SYSENTER_CS];
+    env->sysenter_esp = state.msrs[NVMM_X64_MSR_SYSENTER_ESP];
+    env->sysenter_eip = state.msrs[NVMM_X64_MSR_SYSENTER_EIP];
+    env->pat = state.msrs[NVMM_X64_MSR_PAT];
+    env->tsc = state.msrs[NVMM_X64_MSR_TSC];
+
+    x86_update_hflags(env);
+}
+
+static bool
+nvmm_can_take_int(CPUState *cpu)
+{
+    struct CPUX86State *env = (CPUArchState *)(cpu->env_ptr);
+    struct nvmm_vcpu *vcpu = get_nvmm_vcpu(cpu);
+    struct nvmm_machine *mach = get_nvmm_mach();
+
+    if (vcpu->int_window_exit) {
+        return false;
+    }
+
+    if (vcpu->int_shadow || (!(env->eflags & IF_MASK))) {
+        struct nvmm_x64_state state;
+
+        /* Exit on interrupt window. */
+        nvmm_vcpu_getstate(mach, vcpu->cpuid, &state,
+            NVMM_X64_STATE_INTR);
+        state.intr.int_window_exiting = 1;
+        nvmm_vcpu_setstate(mach, vcpu->cpuid, &state,
+            NVMM_X64_STATE_INTR);
+
+        return false;
+    }
+
+    return true;
+}
+
+static bool
+nvmm_can_take_nmi(CPUState *cpu)
+{
+    struct nvmm_vcpu *vcpu = get_nvmm_vcpu(cpu);
+
+    /*
+     * Contrary to INTs, NMIs always schedule an exit when they are
+     * completed. Therefore, if window-exiting is enabled, it means
+     * NMIs are blocked.
+     */
+    if (vcpu->nmi_window_exit) {
+        return false;
+    }
+
+    return true;
+}
+
+/*
+ * Called before the VCPU is run. We inject events generated by the I/O
+ * thread, and synchronize the guest TPR.
+ */
+static void
+nvmm_vcpu_pre_run(CPUState *cpu)
+{
+    struct CPUX86State *env = (CPUArchState *)(cpu->env_ptr);
+    struct nvmm_machine *mach = get_nvmm_mach();
+    struct nvmm_vcpu *vcpu = get_nvmm_vcpu(cpu);
+    X86CPU *x86_cpu = X86_CPU(cpu);
+    struct nvmm_x64_state state;
+    struct nvmm_event event;
+    bool has_event = false;
+    bool sync_tpr = false;
+    uint8_t tpr;
+    int ret;
+
+    memset(&event, 0, sizeof(event));
+
+    qemu_mutex_lock_iothread();
+
+    tpr = cpu_get_apic_tpr(x86_cpu->apic_state);
+    if (tpr != vcpu->tpr) {
+        vcpu->tpr = tpr;
+        sync_tpr = true;
+    }
+
+    /*
+     * Force the VCPU out of its inner loop to process any INIT requests
+     * or commit pending TPR access.
+     */
+    if (cpu->interrupt_request & (CPU_INTERRUPT_INIT|CPU_INTERRUPT_TPR)) {
+        cpu->exit_request = 1;
+    }
+
+    if (!has_event && (cpu->interrupt_request & CPU_INTERRUPT_NMI)) {
+        if (nvmm_can_take_nmi(cpu)) {
+            cpu->interrupt_request &= ~CPU_INTERRUPT_NMI;
+            event.type = NVMM_EVENT_INTERRUPT_HW;
+            event.vector = 2;
+            has_event = true;
+        }
+    }
+
+    if (!has_event && (cpu->interrupt_request & CPU_INTERRUPT_HARD)) {
+        if (nvmm_can_take_int(cpu)) {
+            cpu->interrupt_request &= ~CPU_INTERRUPT_HARD;
+            event.type = NVMM_EVENT_INTERRUPT_HW;
+            event.vector = cpu_get_pic_interrupt(env);
+            has_event = true;
+        }
+    }
+
+    /* Don't want SMIs. */
+    if (cpu->interrupt_request & CPU_INTERRUPT_SMI) {
+        cpu->interrupt_request &= ~CPU_INTERRUPT_SMI;
+    }
+
+    if (sync_tpr) {
+        ret = nvmm_vcpu_getstate(mach, vcpu->cpuid, &state,
+            NVMM_X64_STATE_CRS);
+        if (ret == -1) {
+            error_report("NVMM: Failed to get CPU state,"
+                " error=%d", errno);
+        }
+
+        state.crs[NVMM_X64_CR_CR8] = vcpu->tpr;
+
+        ret = nvmm_vcpu_setstate(mach, vcpu->cpuid, &state,
+            NVMM_X64_STATE_CRS);
+        if (ret == -1) {
+            error_report("NVMM: Failed to set CPU state,"
+                " error=%d", errno);
+        }
+    }
+
+    if (has_event) {
+        ret = nvmm_vcpu_inject(mach, vcpu->cpuid, &event);
+        if (ret == -1) {
+            error_report("NVMM: Failed to inject event,"
+                " error=%d", errno);
+        }
+    }
+
+    qemu_mutex_unlock_iothread();
+}
+
+/*
+ * Called after the VCPU ran. We synchronize the host view of the TPR and
+ * RFLAGS.
+ */
+static void
+nvmm_vcpu_post_run(CPUState *cpu, struct nvmm_exit *exit)
+{
+    struct nvmm_vcpu *vcpu = get_nvmm_vcpu(cpu);
+    struct CPUX86State *env = (CPUArchState *)(cpu->env_ptr);
+    X86CPU *x86_cpu = X86_CPU(cpu);
+    uint64_t tpr;
+
+    env->eflags = exit->exitstate[NVMM_X64_EXITSTATE_RFLAGS];
+
+    vcpu->int_shadow =
+        exit->exitstate[NVMM_X64_EXITSTATE_INT_SHADOW];
+    vcpu->int_window_exit =
+        exit->exitstate[NVMM_X64_EXITSTATE_INT_WINDOW_EXIT];
+    vcpu->nmi_window_exit =
+        exit->exitstate[NVMM_X64_EXITSTATE_NMI_WINDOW_EXIT];
+
+    tpr = exit->exitstate[NVMM_X64_EXITSTATE_CR8];
+    if (vcpu->tpr != tpr) {
+        vcpu->tpr = tpr;
+        qemu_mutex_lock_iothread();
+        cpu_set_apic_tpr(x86_cpu->apic_state, vcpu->tpr);
+        qemu_mutex_unlock_iothread();
+    }
+}
+
+/* -------------------------------------------------------------------------- */
+
+static void
+nvmm_io_callback(struct nvmm_io *io)
+{
+    MemTxAttrs attrs = { 0 };
+    int ret;
+
+    ret = address_space_rw(&address_space_io, io->port, attrs, io->data,
+        io->size, !io->in);
+    if (ret != MEMTX_OK) {
+        error_report("NVMM: I/O Transaction Failed "
+            "[%s, port=%lu, size=%zu]", (io->in ? "in" : "out"),
+            io->port, io->size);
+    }
+
+    /* XXX Needed, otherwise infinite loop. */
+    current_cpu->vcpu_dirty = false;
+}
+
+static void
+nvmm_mem_callback(struct nvmm_mem *mem)
+{
+    cpu_physical_memory_rw(mem->gpa, mem->data, mem->size, mem->write);
+
+    /* XXX Needed, otherwise infinite loop. */
+    current_cpu->vcpu_dirty = false;
+}
+
+static const struct nvmm_callbacks nvmm_callbacks = {
+    .io = nvmm_io_callback,
+    .mem = nvmm_mem_callback
+};
+
+/* -------------------------------------------------------------------------- */
+
+static int
+nvmm_handle_mem(struct nvmm_machine *mach, struct nvmm_vcpu *vcpu,
+    struct nvmm_exit *exit)
+{
+    int ret;
+
+    ret = nvmm_assist_mem(mach, vcpu->cpuid, exit);
+    if (ret == -1) {
+        error_report("NVMM: Mem Assist Failed [gpa=%p]",
+            (void *)exit->u.mem.gpa);
+    }
+
+    return ret;
+}
+
+static int
+nvmm_handle_io(struct nvmm_machine *mach, struct nvmm_vcpu *vcpu,
+    struct nvmm_exit *exit)
+{
+    int ret;
+
+    ret = nvmm_assist_io(mach, vcpu->cpuid, exit);
+    if (ret == -1) {
+        error_report("NVMM: I/O Assist Failed [port=%d]",
+            (int)exit->u.io.port);
+    }
+
+    return ret;
+}
+
+static int
+nvmm_handle_msr(struct nvmm_machine *mach, CPUState *cpu,
+    struct nvmm_exit *exit)
+{
+    struct nvmm_vcpu *vcpu = get_nvmm_vcpu(cpu);
+    X86CPU *x86_cpu = X86_CPU(cpu);
+    struct nvmm_x64_state state;
+    uint64_t val;
+    int ret;
+
+    val = exit->u.msr.val;
+
+    switch (exit->u.msr.msr) {
+    case MSR_IA32_APICBASE:
+        if (exit->u.msr.type == NVMM_EXIT_MSR_RDMSR) {
+            val = cpu_get_apic_base(x86_cpu->apic_state);
+        } else {
+            cpu_set_apic_base(x86_cpu->apic_state, val);
+        }
+        break;
+    default:
+        // TODO: more MSRs to add?
+        error_report("NVMM: Unexpected MSR 0x%lx, ignored",
+            exit->u.msr.msr);
+        if (exit->u.msr.type == NVMM_EXIT_MSR_RDMSR) {
+            val = 0;
+        }
+        break;
+    }
+
+    ret = nvmm_vcpu_getstate(mach, vcpu->cpuid, &state,
+        NVMM_X64_STATE_GPRS);
+    if (ret == -1) {
+        return -1;
+    }
+
+    if (exit->u.msr.type == NVMM_EXIT_MSR_RDMSR) {
+        state.gprs[NVMM_X64_GPR_RAX] = (val & 0xFFFFFFFF);
+        state.gprs[NVMM_X64_GPR_RDX] = (val >> 32);
+    }
+
+    state.gprs[NVMM_X64_GPR_RIP] = exit->u.msr.npc;
+
+    ret = nvmm_vcpu_setstate(mach, vcpu->cpuid, &state,
+        NVMM_X64_STATE_GPRS);
+    if (ret == -1) {
+        return -1;
+    }
+
+    return 0;
+}
+
+static int
+nvmm_handle_halted(struct nvmm_machine *mach, CPUState *cpu,
+    struct nvmm_exit *exit)
+{
+    struct CPUX86State *env = (CPUArchState *)(cpu->env_ptr);
+    int ret = 0;
+
+    qemu_mutex_lock_iothread();
+
+    if (!((cpu->interrupt_request & CPU_INTERRUPT_HARD) &&
+          (env->eflags & IF_MASK)) &&
+        !(cpu->interrupt_request & CPU_INTERRUPT_NMI)) {
+        cpu->exception_index = EXCP_HLT;
+        cpu->halted = true;
+        ret = 1;
+    }
+
+    qemu_mutex_unlock_iothread();
+
+    return ret;
+}
+
+static int
+nvmm_inject_ud(struct nvmm_machine *mach, struct nvmm_vcpu *vcpu)
+{
+    struct nvmm_event event;
+
+    event.type = NVMM_EVENT_EXCEPTION;
+    event.vector = 6;
+    event.u.error = 0;
+
+    return nvmm_vcpu_inject(mach, vcpu->cpuid, &event);
+}
+
+static int
+nvmm_vcpu_loop(CPUState *cpu)
+{
+    struct CPUX86State *env = (CPUArchState *)(cpu->env_ptr);
+    struct nvmm_machine *mach = get_nvmm_mach();
+    struct nvmm_vcpu *vcpu = get_nvmm_vcpu(cpu);
+    X86CPU *x86_cpu = X86_CPU(cpu);
+    struct nvmm_exit exit;
+    int ret;
+
+    /*
+     * Some asynchronous events must be handled outside of the inner
+     * VCPU loop. They are handled here.
+     */
+    if (cpu->interrupt_request & CPU_INTERRUPT_INIT) {
+        nvmm_cpu_synchronize_state(cpu);
+        do_cpu_init(x86_cpu);
+        /* XXX: reset the INT/NMI windows */
+    }
+    if (cpu->interrupt_request & CPU_INTERRUPT_POLL) {
+        cpu->interrupt_request &= ~CPU_INTERRUPT_POLL;
+        apic_poll_irq(x86_cpu->apic_state);
+    }
+    if (((cpu->interrupt_request & CPU_INTERRUPT_HARD) &&
+         (env->eflags & IF_MASK)) ||
+        (cpu->interrupt_request & CPU_INTERRUPT_NMI)) {
+        cpu->halted = false;
+    }
+    if (cpu->interrupt_request & CPU_INTERRUPT_SIPI) {
+        nvmm_cpu_synchronize_state(cpu);
+        do_cpu_sipi(x86_cpu);
+    }
+    if (cpu->interrupt_request & CPU_INTERRUPT_TPR) {
+        cpu->interrupt_request &= ~CPU_INTERRUPT_TPR;
+        nvmm_cpu_synchronize_state(cpu);
+        apic_handle_tpr_access_report(x86_cpu->apic_state, env->eip,
+            env->tpr_access_type);
+    }
+
+    if (cpu->halted) {
+        cpu->exception_index = EXCP_HLT;
+        atomic_set(&cpu->exit_request, false);
+        return 0;
+    }
+
+    qemu_mutex_unlock_iothread();
+    cpu_exec_start(cpu);
+
+    /*
+     * Inner VCPU loop.
+     */
+    do {
+        if (cpu->vcpu_dirty) {
+            nvmm_set_registers(cpu);
+            cpu->vcpu_dirty = false;
+        }
+
+        if (vcpu->stop) {
+            cpu->exception_index = EXCP_INTERRUPT;
+            vcpu->stop = false;
+            ret = 1;
+            break;
+        }
+
+        nvmm_vcpu_pre_run(cpu);
+
+        if (atomic_read(&cpu->exit_request)) {
+            qemu_cpu_kick_self();
+        }
+
+        ret = nvmm_vcpu_run(mach, vcpu->cpuid, &exit);
+        if (ret == -1) {
+            error_report("NVMM: Failed to exec a virtual processor,"
+                " error=%d", errno);
+            break;
+        }
+
+        nvmm_vcpu_post_run(cpu, &exit);
+
+        switch (exit.reason) {
+        case NVMM_EXIT_NONE:
+            break;
+        case NVMM_EXIT_MEMORY:
+            ret = nvmm_handle_mem(mach, vcpu, &exit);
+            break;
+        case NVMM_EXIT_IO:
+            ret = nvmm_handle_io(mach, vcpu, &exit);
+            break;
+        case NVMM_EXIT_MSR:
+            ret = nvmm_handle_msr(mach, cpu, &exit);
+            break;
+        case NVMM_EXIT_INT_READY:
+        case NVMM_EXIT_NMI_READY:
+            break;
+        case NVMM_EXIT_MONITOR:
+        case NVMM_EXIT_MWAIT:
+        case NVMM_EXIT_MWAIT_COND:
+            ret = nvmm_inject_ud(mach, vcpu);
+            break;
+        case NVMM_EXIT_HALTED:
+            ret = nvmm_handle_halted(mach, cpu, &exit);
+            break;
+        case NVMM_EXIT_SHUTDOWN:
+            qemu_system_reset_request(SHUTDOWN_CAUSE_GUEST_RESET);
+            cpu->exception_index = EXCP_INTERRUPT;
+            ret = 1;
+            break;
+        default:
+            error_report("NVMM: Unexpected VM exit code %lx",
+                exit.reason);
+            nvmm_get_registers(cpu);
+            qemu_mutex_lock_iothread();
+            qemu_system_guest_panicked(cpu_get_crash_info(cpu));
+            qemu_mutex_unlock_iothread();
+            ret = -1;
+            break;
+        }
+    } while (ret == 0);
+
+    cpu_exec_end(cpu);
+    qemu_mutex_lock_iothread();
+    current_cpu = cpu;
+
+    atomic_set(&cpu->exit_request, false);
+
+    return ret < 0;
+}
+
+/* -------------------------------------------------------------------------- */
+
+static void
+do_nvmm_cpu_synchronize_state(CPUState *cpu, run_on_cpu_data arg)
+{
+    nvmm_get_registers(cpu);
+    cpu->vcpu_dirty = true;
+}
+
+static void
+do_nvmm_cpu_synchronize_post_reset(CPUState *cpu, run_on_cpu_data arg)
+{
+    nvmm_set_registers(cpu);
+    cpu->vcpu_dirty = false;
+}
+
+static void
+do_nvmm_cpu_synchronize_post_init(CPUState *cpu, run_on_cpu_data arg)
+{
+    nvmm_set_registers(cpu);
+    cpu->vcpu_dirty = false;
+}
+
+static void
+do_nvmm_cpu_synchronize_pre_loadvm(CPUState *cpu, run_on_cpu_data arg)
+{
+    cpu->vcpu_dirty = true;
+}
+
+void nvmm_cpu_synchronize_state(CPUState *cpu)
+{
+    if (!cpu->vcpu_dirty) {
+        run_on_cpu(cpu, do_nvmm_cpu_synchronize_state, RUN_ON_CPU_NULL);
+    }
+}
+
+void nvmm_cpu_synchronize_post_reset(CPUState *cpu)
+{
+    run_on_cpu(cpu, do_nvmm_cpu_synchronize_post_reset, RUN_ON_CPU_NULL);
+}
+
+void nvmm_cpu_synchronize_post_init(CPUState *cpu)
+{
+    run_on_cpu(cpu, do_nvmm_cpu_synchronize_post_init, RUN_ON_CPU_NULL);
+}
+
+void nvmm_cpu_synchronize_pre_loadvm(CPUState *cpu)
+{
+    run_on_cpu(cpu, do_nvmm_cpu_synchronize_pre_loadvm, RUN_ON_CPU_NULL);
+}
+
+/* -------------------------------------------------------------------------- */
+
+static Error *nvmm_migration_blocker;
+
+static void
+nvmm_ipi_signal(int sigcpu)
+{
+    struct nvmm_vcpu *vcpu;
+
+    if (current_cpu) {
+        vcpu = get_nvmm_vcpu(current_cpu);
+        vcpu->stop = true;
+    }
+}
+
+static void
+nvmm_init_cpu_signals(void)
+{
+    struct sigaction sigact;
+    sigset_t set;
+
+    /* Install the IPI handler. */
+    memset(&sigact, 0, sizeof(sigact));
+    sigact.sa_handler = nvmm_ipi_signal;
+    sigaction(SIG_IPI, &sigact, NULL);
+
+    /* Allow IPIs on the current thread. */
+    sigprocmask(SIG_BLOCK, NULL, &set);
+    sigdelset(&set, SIG_IPI);
+    pthread_sigmask(SIG_SETMASK, &set, NULL);
+}
+
+int
+nvmm_init_vcpu(CPUState *cpu)
+{
+    struct nvmm_machine *mach = get_nvmm_mach();
+    Error *local_error = NULL;
+    struct nvmm_vcpu *vcpu;
+    int ret;
+
+    nvmm_init_cpu_signals();
+
+    if (nvmm_migration_blocker == NULL) {
+        error_setg(&nvmm_migration_blocker,
+            "NVMM: Migration not supported");
+
+        (void)migrate_add_blocker(nvmm_migration_blocker, &local_error);
+        if (local_error) {
+            error_report_err(local_error);
+            migrate_del_blocker(nvmm_migration_blocker);
+            error_free(nvmm_migration_blocker);
+            return -EINVAL;
+        }
+    }
+
+    vcpu = g_malloc0(sizeof(struct nvmm_vcpu));
+    if (vcpu == NULL) {
+        error_report("NVMM: Failed to allocate VCPU context.");
+        return -ENOMEM;
+    }
+    vcpu->cpuid = cpu->cpu_index;
+
+    ret = nvmm_vcpu_create(mach, vcpu->cpuid);
+    if (ret == -1) {
+        error_report("NVMM: Failed to create a virtual processor,"
+            " error=%d", errno);
+        g_free(vcpu);
+        return -EINVAL;
+    }
+
+    cpu->vcpu_dirty = true;
+    cpu->hax_vcpu = (struct hax_vcpu_state *)vcpu;
+
+    return 0;
+}
+
+int
+nvmm_vcpu_exec(CPUState *cpu)
+{
+    int ret, fatal;
+
+    while (1) {
+        if (cpu->exception_index >= EXCP_INTERRUPT) {
+            ret = cpu->exception_index;
+            cpu->exception_index = -1;
+            break;
+        }
+
+        fatal = nvmm_vcpu_loop(cpu);
+
+        if (fatal) {
+            error_report("NVMM: Failed to execute a VCPU.");
+            abort();
+        }
+    }
+
+    return ret;
+}
+
+void
+nvmm_destroy_vcpu(CPUState *cpu)
+{
+    struct nvmm_machine *mach = get_nvmm_mach();
+    struct nvmm_vcpu *vcpu = get_nvmm_vcpu(cpu);
+
+    nvmm_vcpu_destroy(mach, vcpu->cpuid);
+    g_free(cpu->hax_vcpu);
+}
+
+/* -------------------------------------------------------------------------- */
+
+static void
+nvmm_update_mapping(hwaddr start_pa, ram_addr_t size, uintptr_t hva,
+    bool add, bool rom, const char *name)
+{
+    struct nvmm_machine *mach = get_nvmm_mach();
+    int ret, prot;
+
+    if (add) {
+        prot = PROT_READ | PROT_EXEC;
+        if (!rom) {
+            prot |= PROT_WRITE;
+        }
+        ret = nvmm_gpa_map(mach, hva, start_pa, size, prot);
+    } else {
+        ret = nvmm_gpa_unmap(mach, hva, start_pa, size);
+    }
+
+    if (ret == -1) {
+        error_report("NVMM: Failed to %s GPA range '%s' PA:%p, "
+            "Size:%p bytes, HostVA:%p, error=%d",
+            (add ? "map" : "unmap"), name, (void *)(uintptr_t)start_pa,
+            (void *)size, (void *)hva, errno);
+    }
+}
+
+static void
+nvmm_process_section(MemoryRegionSection *section, int add)
+{
+    MemoryRegion *mr = section->mr;
+    hwaddr start_pa = section->offset_within_address_space;
+    ram_addr_t size = int128_get64(section->size);
+    unsigned int delta;
+    uintptr_t hva;
+
+    if (!memory_region_is_ram(mr)) {
+        return;
+    }
+
+    /* Adjust start_pa and size so that they are page-aligned. */
+    delta = qemu_real_host_page_size - (start_pa & ~qemu_real_host_page_mask);
+    delta &= ~qemu_real_host_page_mask;
+    if (delta > size) {
+        return;
+    }
+    start_pa += delta;
+    size -= delta;
+    size &= qemu_real_host_page_mask;
+    if (!size || (start_pa & ~qemu_real_host_page_mask)) {
+        return;
+    }
+
+    hva = (uintptr_t)memory_region_get_ram_ptr(mr) +
+        section->offset_within_region + delta;
+
+    nvmm_update_mapping(start_pa, size, hva, add,
+        memory_region_is_rom(mr), mr->name);
+}
+
+static void
+nvmm_region_add(MemoryListener *listener, MemoryRegionSection *section)
+{
+    memory_region_ref(section->mr);
+    nvmm_process_section(section, 1);
+}
+
+static void
+nvmm_region_del(MemoryListener *listener, MemoryRegionSection *section)
+{
+    nvmm_process_section(section, 0);
+    memory_region_unref(section->mr);
+}
+
+static void
+nvmm_transaction_begin(MemoryListener *listener)
+{
+    /* nothing */
+}
+
+static void
+nvmm_transaction_commit(MemoryListener *listener)
+{
+    /* nothing */
+}
+
+static void
+nvmm_log_sync(MemoryListener *listener, MemoryRegionSection *section)
+{
+    MemoryRegion *mr = section->mr;
+
+    if (!memory_region_is_ram(mr)) {
+        return;
+    }
+
+    memory_region_set_dirty(mr, 0, int128_get64(section->size));
+}
+
+static MemoryListener nvmm_memory_listener = {
+    .begin = nvmm_transaction_begin,
+    .commit = nvmm_transaction_commit,
+    .region_add = nvmm_region_add,
+    .region_del = nvmm_region_del,
+    .log_sync = nvmm_log_sync,
+    .priority = 10,
+};
+
+static void
+nvmm_ram_block_added(RAMBlockNotifier *n, void *host, size_t size)
+{
+    struct nvmm_machine *mach = get_nvmm_mach();
+    uintptr_t hva = (uintptr_t)host;
+    int ret;
+
+    ret = nvmm_hva_map(mach, hva, size);
+
+    if (ret == -1) {
+        error_report("NVMM: Failed to map HVA, HostVA:%p "
+            "Size:%p bytes, error=%d",
+            (void *)hva, (void *)size, errno);
+    }
+}
+
+static struct RAMBlockNotifier nvmm_ram_notifier = {
+    .ram_block_added = nvmm_ram_block_added
+};
+
+/* -------------------------------------------------------------------------- */
+
+static void
+nvmm_handle_interrupt(CPUState *cpu, int mask)
+{
+    cpu->interrupt_request |= mask;
+
+    if (!qemu_cpu_is_self(cpu)) {
+        qemu_cpu_kick(cpu);
+    }
+}
+
+/* -------------------------------------------------------------------------- */
+
+static int
+nvmm_accel_configure(struct nvmm_machine *mach)
+{
+    struct nvmm_x86_conf_cpuid cpuid;
+    int ret;
+
+    memset(&cpuid, 0, sizeof(cpuid));
+    cpuid.leaf = 0x00000001;
+    cpuid.del.edx = CPUID_MCE | CPUID_MCA | CPUID_MTRR;
+
+    ret = nvmm_machine_configure(mach, NVMM_X86_CONF_CPUID, &cpuid);
+    if (ret == -1)
+        return -1;
+
+    return 0;
+}
+
+static int
+nvmm_accel_init(MachineState *ms)
+{
+    struct nvmm_capability cap;
+    int ret;
+
+    ret = nvmm_capability(&cap);
+    if (ret == -1) {
+        error_report("NVMM: No accelerator found, error=%d", errno);
+        return -ENOSPC;
+    }
+    if (cap.version != 1) {
+        error_report("NVMM: Unsupported version %lu", cap.version);
+        return -ENOSPC;
+    }
+    if (cap.state_size != sizeof(struct nvmm_x64_state)) {
+        error_report("NVMM: Wrong state size %zu", cap.state_size);
+        return -ENOSPC;
+    }
+
+    ret = nvmm_machine_create(&nvmm_global.mach);
+    if (ret == -1) {
+        error_report("NVMM: Machine creation failed, error=%d", errno);
+        return -ENOSPC;
+    }
+
+    ret = nvmm_accel_configure(&nvmm_global.mach);
+    if (ret == -1) {
+        error_report("NVMM: Machine configuration failed, error=%d",
+            errno);
+        return -ENOSPC;
+    }
+
+    nvmm_callbacks_register(&nvmm_callbacks);
+
+    memory_listener_register(&nvmm_memory_listener, &address_space_memory);
+    ram_block_notifier_add(&nvmm_ram_notifier);
+
+    cpu_interrupt_handler = nvmm_handle_interrupt;
+
+    printf("NetBSD Virtual Machine Monitor accelerator is operational\n");
+    return 0;
+}
+
+int
+nvmm_enabled(void)
+{
+    return nvmm_allowed;
+}
+
+static void
+nvmm_accel_class_init(ObjectClass *oc, void *data)
+{
+    AccelClass *ac = ACCEL_CLASS(oc);
+    ac->name = "NVMM";
+    ac->init_machine = nvmm_accel_init;
+    ac->allowed = &nvmm_allowed;
+}
+
+static const TypeInfo nvmm_accel_type = {
+    .name = ACCEL_CLASS_NAME("nvmm"),
+    .parent = TYPE_ACCEL,
+    .class_init = nvmm_accel_class_init,
+};
+
+static void
+nvmm_type_init(void)
+{
+    type_register_static(&nvmm_accel_type);
+}
+
+type_init(nvmm_type_init);
