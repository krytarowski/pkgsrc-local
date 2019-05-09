$NetBSD$

--- target/i386/helper.c.orig	2019-04-23 18:14:46.000000000 +0000
+++ target/i386/helper.c
@@ -986,7 +986,7 @@ void cpu_report_tpr_access(CPUX86State *
     X86CPU *cpu = x86_env_get_cpu(env);
     CPUState *cs = CPU(cpu);
 
-    if (kvm_enabled() || whpx_enabled()) {
+    if (kvm_enabled() || whpx_enabled() || nvmm_enabled()) {
         env->tpr_access_type = access;
 
         cpu_interrupt(cs, CPU_INTERRUPT_TPR);
