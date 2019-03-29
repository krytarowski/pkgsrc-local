$NetBSD$

--- coregrind/m_syswrap/syswrap-amd64-netbsd.c.orig	2019-03-29 08:30:25.935209270 +0000
+++ coregrind/m_syswrap/syswrap-amd64-netbsd.c
@@ -1,6 +1,6 @@
 
 /*--------------------------------------------------------------------*/
-/*--- Platform-specific syscalls stuff.    syswrap-amd64-freebsd.c ---*/
+/*--- Platform-specific syscalls stuff.    syswrap-amd64-netbsd.c ---*/
 /*--------------------------------------------------------------------*/
 
 /*
@@ -28,7 +28,7 @@
    The GNU General Public License is contained in the file COPYING.
 */
 
-#if defined(VGP_amd64_freebsd)
+#if defined(VGP_amd64_netbsd)
 
 #include "pub_core_basics.h"
 #include "pub_core_vki.h"
@@ -54,7 +54,7 @@
 
 #include "priv_types_n_macros.h"
 #include "priv_syswrap-generic.h"    /* for decls of generic wrappers */
-#include "priv_syswrap-freebsd.h"    /* for decls of freebsd-ish wrappers */
+#include "priv_syswrap-netbsd.h"    /* for decls of freebsd-ish wrappers */
 #include "priv_syswrap-main.h"
 
 /* ---------------------------------------------------------------------
@@ -711,7 +711,7 @@ PRE(sys_sysarch)
 #undef PRE
 #undef POST
 
-#endif /* defined(VGP_amd64_freebsd) */
+#endif /* defined(VGP_amd64_netbsd) */
 
 /*--------------------------------------------------------------------*/
 /*--- end                                                          ---*/
