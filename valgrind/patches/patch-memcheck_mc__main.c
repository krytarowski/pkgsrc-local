$NetBSD$

--- memcheck/mc_main.c.orig	2018-09-30 04:41:00.000000000 +0000
+++ memcheck/mc_main.c
@@ -55,7 +55,24 @@
 #include "memcheck.h"   /* for client requests */
 
 /* Set to 1 to do a little more sanity checking */
-#define VG_DEBUG_MEMORY 0
+#define VG_DEBUG_MEMORY 1
+
+void __sanitizer_cov_trace_pc(void);
+
+void
+__sanitizer_cov_trace_pc(void)
+{
+   static int recursive = 0;
+
+   if (recursive > 0)
+      return;
+
+   recursive++;
+
+   VG_(debugLog)(2, "KR", "%s() %s:%d addr=%lx\n", __func__, __FILE__, __LINE__, __builtin_return_address(0));
+
+   recursive--;
+}
 
 #define DEBUG(fmt, args...) //VG_(printf)(fmt, ## args)
 
@@ -1391,6 +1408,7 @@ VG_REGPARM(3) /* make sure we're using a
                  this function may get called from hand written assembly. */
 ULong mc_LOADVn_slow ( Addr a, SizeT nBits, Bool bigendian )
 {
+VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    PROF_EVENT(MCPE_LOADVN_SLOW);
 
    /* ------------ BEGIN semi-fast cases ------------ */
@@ -1474,7 +1492,9 @@ ULong mc_LOADVn_slow ( Addr a, SizeT nBi
    /* If there's no possibility of getting a partial-loads-ok
       exemption, report the error and quit. */
    if (!MC_(clo_partial_loads_ok)) {
+VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       MC_(record_address_error)( VG_(get_running_tid)(), a, szB, False );
+VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       return vbits64;
    }
 
@@ -1550,7 +1570,9 @@ ULong mc_LOADVn_slow ( Addr a, SizeT nBi
 
    /* Exemption doesn't apply.  Flag an addressing error in the normal
       way. */
+VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    MC_(record_address_error)( VG_(get_running_tid)(), a, szB, False );
+VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
 
    return vbits64;
 }
@@ -5058,7 +5080,10 @@ VG_REGPARM(1) UWord MC_(helperc_LOADV32b
 // Generic for all platforms except {arm32,x86}-linux and x86-solaris
 VG_REGPARM(1) UWord MC_(helperc_LOADV32le) ( Addr a )
 {
-   return mc_LOADV32(a, False);
+VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
+   UWord return1 =  mc_LOADV32(a, False);
+VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
+   return return1;
 }
 #endif
 
