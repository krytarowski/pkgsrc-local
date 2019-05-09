$NetBSD$

--- qemu-options.hx.orig	2019-04-23 18:14:46.000000000 +0000
+++ qemu-options.hx
@@ -66,7 +66,7 @@ Supported machine properties are:
 @table @option
 @item accel=@var{accels1}[:@var{accels2}[:...]]
 This is used to enable an accelerator. Depending on the target architecture,
-kvm, xen, hax, hvf, whpx or tcg can be available. By default, tcg is used. If there is
+kvm, xen, hax, hvf, whpx, nvmm or tcg can be available. By default, tcg is used. If there is
 more than one accelerator specified, the next one is used if the previous one
 fails to initialize.
 @item kernel_irqchip=on|off
@@ -119,13 +119,13 @@ ETEXI
 
 DEF("accel", HAS_ARG, QEMU_OPTION_accel,
     "-accel [accel=]accelerator[,thread=single|multi]\n"
-    "                select accelerator (kvm, xen, hax, hvf, whpx or tcg; use 'help' for a list)\n"
+    "                select accelerator (kvm, xen, hax, hvf, whpx, nvmm or tcg; use 'help' for a list)\n"
     "                thread=single|multi (enable multi-threaded TCG)\n", QEMU_ARCH_ALL)
 STEXI
 @item -accel @var{name}[,prop=@var{value}[,...]]
 @findex -accel
 This is used to enable an accelerator. Depending on the target architecture,
-kvm, xen, hax, hvf, whpx or tcg can be available. By default, tcg is used. If there is
+kvm, xen, hax, hvf, whpx, nvmm or tcg can be available. By default, tcg is used. If there is
 more than one accelerator specified, the next one is used if the previous one
 fails to initialize.
 @table @option
