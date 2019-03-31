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
@@ -568,8 +570,10 @@ Int VG_(load_ELF)(Int fd, const HChar* n
    /* The kernel maps position-independent executables at TASK_SIZE*2/3;
       duplicate this behavior as close as we can. */
    if (e->e.e_type == ET_DYN && ebase == 0) {
+      VG_(debugLog)(2, "initimg", "%s() %s:%d ebase=%lx\n", __func__, __FILE__, __LINE__, ebase);
       ebase = VG_PGROUNDDN(info->exe_base 
                            + (info->exe_end - info->exe_base) * 2 / 3);
+      VG_(debugLog)(2, "initimg", "%s() %s:%d ebase=%lx\n", __func__, __FILE__, __LINE__, ebase);
       /* We really don't want to load PIEs at zero or too close.  It
          works, but it's unrobust (NULL pointer reads and writes
          become legit, which is really bad) and causes problems for
@@ -595,12 +599,18 @@ Int VG_(load_ELF)(Int fd, const HChar* n
       /* Record for later use in AT_BASE. */
       info->interp_offset = ebase;
 #     endif
+
+      VG_(debugLog)(2, "initimg", "%s() %s:%d ebase=%lx\n", __func__, __FILE__, __LINE__, ebase);
    }
 
    info->phnum = e->e.e_phnum;
    info->entry = e->e.e_entry + ebase;
    info->phdr = 0;
+#if defined(VGO_netbsd)
+   info->stack_prot = VKI_PROT_READ|VKI_PROT_WRITE;
+#else
    info->stack_prot = VKI_PROT_READ|VKI_PROT_WRITE|VKI_PROT_EXEC;
+#endif
 
    for (i = 0; i < e->e.e_phnum; i++) {
       ESZ(Phdr) *ph = &e->p[i];
@@ -644,6 +654,8 @@ Int VG_(load_ELF)(Int fd, const HChar* n
          VG_(pread)(fd, buf, ph->p_filesz, ph->p_offset);
          buf[ph->p_filesz] = '\0';
 
+         VG_(debugLog)(2, "initimg", "%s() %s:%d interp='%s'\n", __func__, __FILE__, __LINE__, buf);
+
          sres = VG_(open)(buf, VKI_O_RDONLY, 0);
          if (sr_isError(sres)) {
             VG_(printf)("valgrind: m_ume.c: can't open interpreter\n");
@@ -870,7 +882,7 @@ Int VG_(load_ELF)(Int fd, const HChar* n
    return 0;
 }
 
-#endif // defined(VGO_linux) || defined(VGO_solaris)
+#endif // defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
 
 /*--------------------------------------------------------------------*/
 /*--- end                                                          ---*/
