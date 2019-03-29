$NetBSD$

--- coregrind/m_libcproc.c.orig	2018-05-05 07:42:22.000000000 +0000
+++ coregrind/m_libcproc.c
@@ -67,7 +67,7 @@ HChar** VG_(client_envp) = NULL;
 const HChar *VG_(libdir) = VG_LIBDIR;
 
 const HChar *VG_(LD_PRELOAD_var_name) =
-#if defined(VGO_linux) || defined(VGO_solaris)
+#if defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
    "LD_PRELOAD";
 #elif defined(VGO_darwin)
    "DYLD_INSERT_LIBRARIES";
@@ -348,8 +348,12 @@ void VG_(client_cmd_and_args)(HChar *buf
 
 Int VG_(waitpid)(Int pid, Int *status, Int options)
 {
-#  if defined(VGO_linux)
+#  if defined(VGO_linux) || defined(VGO_netbsd)
+#    if defined(VGO_netbsd)
+   SysRes res = VG_(do_syscall4)(__NR__wait450,
+#    else
    SysRes res = VG_(do_syscall4)(__NR_wait4,
+#    endif
                                  pid, (UWord)status, options, 0);
    return sr_isError(res) ? -1 : sr_Res(res);
 #  elif defined(VGO_darwin)
@@ -586,7 +590,7 @@ Int VG_(system) ( const HChar* cmd )
 Int VG_(sysctl)(Int *name, UInt namelen, void *oldp, SizeT *oldlenp, void *newp, SizeT newlen)
 {
    SysRes res;
-#  if defined(VGO_darwin)
+#  if defined(VGO_darwin) || defined(VGO_netbsd)
    res = VG_(do_syscall6)(__NR___sysctl,
                            (UWord)name, namelen, (UWord)oldp, (UWord)oldlenp, (UWord)newp, newlen);
 #  else
@@ -689,6 +693,10 @@ Int VG_(gettid)(void)
    // Use Mach thread ports for lwpid instead.
    return mach_thread_self();
 
+#  elif defined(VGO_netbsd)
+   SysRes res = VG_(do_syscall0)(__NR__lwp_self);
+   return sr_Res(res);
+
 #  elif defined(VGO_solaris)
    SysRes res = VG_(do_syscall0)(__NR_lwp_self);
    return sr_Res(res);
@@ -804,7 +812,7 @@ Int VG_(getgroups)( Int size, UInt* list
         || defined(VGP_ppc64be_linux) || defined(VGP_ppc64le_linux)  \
         || defined(VGO_darwin) || defined(VGP_s390x_linux)    \
         || defined(VGP_mips32_linux) || defined(VGP_arm64_linux) \
-        || defined(VGO_solaris)
+        || defined(VGO_solaris) || defined(VGO_netbsd)
    SysRes sres;
    sres = VG_(do_syscall2)(__NR_getgroups, size, (Addr)list);
    if (sr_isError(sres))
@@ -860,7 +868,7 @@ Int VG_(fork) ( void )
       return -1;
    return sr_Res(res);
 
-#  elif defined(VGO_darwin)
+#  elif defined(VGO_darwin) || defined(VGO_netbsd)
    SysRes res;
    res = VG_(do_syscall0)(__NR_fork); /* __NR_fork is UX64 */
    if (sr_isError(res))
@@ -921,6 +929,14 @@ UInt VG_(read_millisecond_timer) ( void 
      }
    }
 
+#  elif defined(VGO_netbsd)
+   { SysRes res;
+     struct vki_timeval tv_now;
+     res = VG_(do_syscall2)(__NR__gettimeofday50, (UWord)&tv_now, (UWord)NULL);
+     vg_assert(! sr_isError(res));
+     now = tv_now.tv_sec * 1000000ULL + tv_now.tv_usec;
+   }
+
 #  elif defined(VGO_darwin)
    // Weird: it seems that gettimeofday() doesn't fill in the timeval, but
    // rather returns the tv_sec as the low 32 bits of the result and the
