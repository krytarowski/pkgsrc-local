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
@@ -412,6 +412,8 @@ ESZ(Addr) mapelf(struct elfinfo *e, ESZ(
       memsz   = ph->p_memsz;
       brkaddr = addr+memsz;
 
+      VG_(debugLog)(2, "initimg", "%s() %s:%d addr=%lx vaddr=%lx base=%lx memsz=%lu brkaddr=%lx\n", __func__, __FILE__, __LINE__, addr, ph->p_vaddr, base, memsz, brkaddr);
+
       if (brkaddr > elfbrk)
          elfbrk = brkaddr;
    }
@@ -644,6 +646,8 @@ Int VG_(load_ELF)(Int fd, const HChar* n
          VG_(pread)(fd, buf, ph->p_filesz, ph->p_offset);
          buf[ph->p_filesz] = '\0';
 
+         VG_(debugLog)(2, "initimg", "%s() %s:%d interp='%s'\n", __func__, __FILE__, __LINE__, buf);
+
          sres = VG_(open)(buf, VKI_O_RDONLY, 0);
          if (sr_isError(sres)) {
             VG_(printf)("valgrind: m_ume.c: can't open interpreter\n");
@@ -870,7 +874,7 @@ Int VG_(load_ELF)(Int fd, const HChar* n
    return 0;
 }
 
-#endif // defined(VGO_linux) || defined(VGO_solaris)
+#endif // defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
 
 /*--------------------------------------------------------------------*/
 /*--- end                                                          ---*/
