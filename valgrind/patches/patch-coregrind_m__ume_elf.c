$NetBSD$

--- coregrind/m_ume/elf.c.orig	2018-05-05 07:42:22.000000000 +0000
+++ coregrind/m_ume/elf.c
@@ -28,7 +28,7 @@
    The GNU General Public License is contained in the file COPYING.
 */
 
-#if defined(VGO_linux) || defined(VGO_solaris)
+#if defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
 
 #include "pub_core_basics.h"
 #include "pub_core_vki.h"
@@ -870,7 +870,7 @@ Int VG_(load_ELF)(Int fd, const HChar* n
    return 0;
 }
 
-#endif // defined(VGO_linux) || defined(VGO_solaris)
+#endif // defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
 
 /*--------------------------------------------------------------------*/
 /*--- end                                                          ---*/
