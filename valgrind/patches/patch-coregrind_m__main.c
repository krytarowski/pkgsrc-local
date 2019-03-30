$NetBSD$

--- coregrind/m_main.c.orig	2018-05-05 07:42:22.000000000 +0000
+++ coregrind/m_main.c
@@ -1470,7 +1470,7 @@ Int valgrind_main ( Int argc, HChar **ar
    if (!need_help) {
       VG_(debugLog)(1, "main", "Create initial image\n");
 
-#     if defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_solaris)
+#     if defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_solaris) || defined(VGO_netbsd)
       the_iicii.argv              = argv;
       the_iicii.envp              = envp;
       the_iicii.toolname          = VG_(clo_toolname);
@@ -1735,7 +1735,7 @@ Int valgrind_main ( Int argc, HChar **ar
    addr2dihandle = VG_(newXA)( VG_(malloc), "main.vm.2",
                                VG_(free), sizeof(Addr_n_ULong) );
 
-#  if defined(VGO_linux) || defined(VGO_solaris)
+#  if defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
    { Addr* seg_starts;
      Int   n_seg_starts;
      Addr_n_ULong anu;
@@ -2401,7 +2401,7 @@ static void final_tidyup(ThreadId tid)
 /*=== Getting to main() alive: LINUX                               ===*/
 /*====================================================================*/
 
-#if defined(VGO_linux)
+#if defined(VGO_linux) || defined(VGO_netbsd)
 
 /* If linking of the final executables is done with glibc present,
    then Valgrind starts at main() above as usual, and all of the
@@ -2872,6 +2872,29 @@ asm(
     "\tnop\n"
 ".previous\n"
 );
+#elif defined(VGP_amd64_netbsd)
+
+asm("\n"
+    ".text\n"
+    "\t.globl _start\n"
+    "\t.globl __start\n"
+    "\t.globl ___start\n"
+    "\t.type _start,@function\n"
+    "_start:\n"
+    "__start:\n"
+    "___start:\n"
+    /* set up the new stack in %rdi */
+    "\tmovq  $vgPlain_interim_stack, %rdi\n"
+    "\taddq  $"VG_STRINGIFY(VG_STACK_GUARD_SZB)", %rdi\n"
+    "\taddq  $"VG_STRINGIFY(VG_DEFAULT_STACK_ACTIVE_SZB)", %rdi\n"
+    "\tandq  $~15, %rdi\n"
+    /* install it, and collect the original one */
+    "\txchgq %rdi, %rsp\n"
+    /* call _start_in_C_amd64_netbsd, passing it the startup %rsp */
+    "\tcall  _start_in_C_amd64_netbsd\n"
+    "\thlt\n"
+    ".previous\n"
+);
 #else
 #  error "Unknown linux platform"
 #endif
@@ -2883,6 +2906,24 @@ asm(
 #include <elf.h>
 /* --- !!! --- EXTERNAL HEADERS end --- !!! --- */
 
+void _start_in_C_amd64_netbsd ( UWord* pArgc, UWord *initial_sp );
+void _start_in_C_amd64_netbsd ( UWord* pArgc, UWord *initial_sp )
+{
+   Int     r;
+   Word    argc = pArgc[0];
+   HChar** argv = (HChar**)&pArgc[1];
+   HChar** envp = (HChar**)&pArgc[1+argc+1];
+
+   VG_(memset)( &the_iicii, 0, sizeof(the_iicii) );
+   VG_(memset)( &the_iifii, 0, sizeof(the_iifii) );
+
+   the_iicii.sp_at_startup = (Addr)initial_sp;
+
+   r = valgrind_main( (Int)argc, argv, envp );
+   /* NOTREACHED */
+   VG_(exit)(r);
+}
+
 /* Avoid compiler warnings: this fn _is_ used, but labelling it
    'static' causes gcc to complain it isn't.
    attribute 'used' also ensures the code is not eliminated at link
