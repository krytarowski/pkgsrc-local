$NetBSD$

--- coregrind/m_libcfile.c.orig	2018-05-05 07:42:22.000000000 +0000
+++ coregrind/m_libcfile.c
@@ -131,6 +131,9 @@ Bool VG_(resolve_filename) ( Int fd, con
    *result = NULL;
    return False;
 
+#  elif defined(VGO_netbsd)
+   return False;
+
 #  else
 #     error Unknown OS
 #  endif
@@ -142,7 +145,7 @@ SysRes VG_(mknod) ( const HChar* pathnam
    /* ARM64 wants to use __NR_mknodat rather than __NR_mknod. */
    SysRes res = VG_(do_syscall4)(__NR_mknodat,
                                  VKI_AT_FDCWD, (UWord)pathname, mode, dev);
-#  elif defined(VGO_linux) || defined(VGO_darwin)
+#  elif defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_netbsd)
    SysRes res = VG_(do_syscall3)(__NR_mknod,
                                  (UWord)pathname, mode, dev);
 #  elif defined(VGO_solaris)
@@ -160,7 +163,7 @@ SysRes VG_(open) ( const HChar* pathname
    /* ARM64 wants to use __NR_openat rather than __NR_open. */
    SysRes res = VG_(do_syscall4)(__NR_openat,
                                  VKI_AT_FDCWD, (UWord)pathname, flags, mode);
-#  elif defined(VGO_linux)
+#  elif defined(VGO_linux) | defined(VGO_netbsd)
    SysRes res = VG_(do_syscall3)(__NR_open,
                                  (UWord)pathname, flags, mode);
 #  elif defined(VGO_darwin)
@@ -188,7 +191,7 @@ Int VG_(fd_open) (const HChar* pathname,
 void VG_(close) ( Int fd )
 {
    /* Hmm.  Return value is not checked.  That's uncool. */
-#  if defined(VGO_linux) || defined(VGO_solaris)
+#  if defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
    (void)VG_(do_syscall1)(__NR_close, fd);
 #  elif defined(VGO_darwin)
    (void)VG_(do_syscall1)(__NR_close_nocancel, fd);
@@ -200,7 +203,7 @@ void VG_(close) ( Int fd )
 Int VG_(read) ( Int fd, void* buf, Int count)
 {
    Int    ret;
-#  if defined(VGO_linux) || defined(VGO_solaris)
+#  if defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
    SysRes res = VG_(do_syscall3)(__NR_read, fd, (UWord)buf, count);
 #  elif defined(VGO_darwin)
    SysRes res = VG_(do_syscall3)(__NR_read_nocancel, fd, (UWord)buf, count);
@@ -220,7 +223,7 @@ Int VG_(read) ( Int fd, void* buf, Int c
 Int VG_(write) ( Int fd, const void* buf, Int count)
 {
    Int    ret;
-#  if defined(VGO_linux) || defined(VGO_solaris)
+#  if defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
    SysRes res = VG_(do_syscall3)(__NR_write, fd, (UWord)buf, count);
 #  elif defined(VGO_darwin)
    SysRes res = VG_(do_syscall3)(__NR_write_nocancel, fd, (UWord)buf, count);
@@ -256,7 +259,7 @@ Int VG_(pipe) ( Int fd[2] )
 #  elif defined(VGO_linux)
    SysRes res = VG_(do_syscall1)(__NR_pipe, (UWord)fd);
    return sr_isError(res) ? -1 : 0;
-#  elif defined(VGO_darwin)
+#  elif defined(VGO_darwin) || defined(VGO_netbsd)
    /* __NR_pipe is UX64, so produces a double-word result */
    SysRes res = VG_(do_syscall0)(__NR_pipe);
    if (!sr_isError(res)) {
@@ -283,7 +286,7 @@ Int VG_(pipe) ( Int fd[2] )
 
 Off64T VG_(lseek) ( Int fd, Off64T offset, Int whence )
 {
-#  if defined(VGO_linux) || defined(VGP_amd64_darwin)
+#  if defined(VGO_linux) || defined(VGP_amd64_darwin) || || defined(VGP_amd64_netbsd)
 #  if defined(__NR__llseek)
    Off64T result;
    SysRes res = VG_(do_syscall5)(__NR__llseek, fd,
@@ -344,7 +347,7 @@ SysRes VG_(stat) ( const HChar* file_nam
    SysRes res;
    VG_(memset)(vgbuf, 0, sizeof(*vgbuf));
 
-#  if defined(VGO_linux) || defined(VGO_darwin)
+#  if defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_netbsd)
    /* First try with stat64.  If that doesn't work out, fall back to
       the vanilla version. */
 #  if defined(__NR_stat64)
@@ -397,7 +400,7 @@ Int VG_(fstat) ( Int fd, struct vg_stat*
    SysRes res;
    VG_(memset)(vgbuf, 0, sizeof(*vgbuf));
 
-#  if defined(VGO_linux) || defined(VGO_darwin)
+#  if defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_netbsd)
    /* First try with fstat64.  If that doesn't work out, fall back to
       the vanilla version. */
 #  if defined(__NR_fstat64)
@@ -469,7 +472,7 @@ Bool VG_(is_dir) ( const HChar* f )
 
 SysRes VG_(dup) ( Int oldfd )
 {
-#  if defined(VGO_linux) || defined(VGO_darwin)
+#  if defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_netbsd)
    return VG_(do_syscall1)(__NR_dup, oldfd);
 #  elif defined(VGO_solaris)
    return VG_(do_syscall3)(__NR_fcntl, oldfd, F_DUPFD, 0);
@@ -491,7 +494,7 @@ SysRes VG_(dup2) ( Int oldfd, Int newfd 
       return VG_(mk_SysRes_Success)(newfd);
    }
    return VG_(do_syscall3)(__NR_dup3, oldfd, newfd, 0);
-#  elif defined(VGO_linux) || defined(VGO_darwin)
+#  elif defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_netbsd)
    return VG_(do_syscall2)(__NR_dup2, oldfd, newfd);
 #  elif defined(VGO_solaris)
    return VG_(do_syscall3)(__NR_fcntl, oldfd, F_DUP2FD, newfd);
@@ -503,7 +506,7 @@ SysRes VG_(dup2) ( Int oldfd, Int newfd 
 /* Returns -1 on error. */
 Int VG_(fcntl) ( Int fd, Int cmd, Addr arg )
 {
-#  if defined(VGO_linux) || defined(VGO_solaris)
+#  if defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
    SysRes res = VG_(do_syscall3)(__NR_fcntl, fd, cmd, arg);
 #  elif defined(VGO_darwin)
    SysRes res = VG_(do_syscall3)(__NR_fcntl_nocancel, fd, cmd, arg);
@@ -518,7 +521,7 @@ Int VG_(rename) ( const HChar* old_name,
 #  if defined(VGO_solaris) || defined(VGP_arm64_linux)
    SysRes res = VG_(do_syscall4)(__NR_renameat, VKI_AT_FDCWD, (UWord)old_name,
                                  VKI_AT_FDCWD, (UWord)new_name);
-#  elif defined(VGO_linux) || defined(VGO_darwin)
+#  elif defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_netbsd)
    SysRes res = VG_(do_syscall2)(__NR_rename, (UWord)old_name, (UWord)new_name);
 #  else
 #    error "Unknown OS"
@@ -531,7 +534,7 @@ Int VG_(unlink) ( const HChar* file_name
 #  if defined(VGP_arm64_linux)
    SysRes res = VG_(do_syscall2)(__NR_unlinkat, VKI_AT_FDCWD,
                                                 (UWord)file_name);
-#  elif defined(VGO_linux) || defined(VGO_darwin)
+#  elif defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_netbsd)
    SysRes res = VG_(do_syscall1)(__NR_unlink, (UWord)file_name);
 #  elif defined(VGO_solaris)
    SysRes res = VG_(do_syscall3)(__NR_unlinkat, VKI_AT_FDCWD,
@@ -553,7 +556,7 @@ static HChar *startup_wd;
    changes. */
 void VG_(record_startup_wd) ( void )
 {
-#  if defined(VGO_linux) || defined(VGO_solaris)
+#  if defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
    /* Simple: just ask the kernel */
    SysRes res;
    SizeT szB = 0;
@@ -614,7 +617,7 @@ SysRes VG_(poll) (struct vki_pollfd *fds
                           (UWord)fds, nfds, 
                           (UWord)(timeout >= 0 ? &timeout_ts : NULL),
                           (UWord)NULL);
-#  elif defined(VGO_linux)
+#  elif defined(VGO_linux) || defined(VGO_netbsd)
    res = VG_(do_syscall3)(__NR_poll, (UWord)fds, nfds, timeout);
 #  elif defined(VGO_darwin)
    res = VG_(do_syscall3)(__NR_poll_nocancel, (UWord)fds, nfds, timeout);
@@ -649,7 +652,7 @@ SSizeT VG_(readlink) (const HChar* path,
 #  if defined(VGP_arm64_linux)
    res = VG_(do_syscall4)(__NR_readlinkat, VKI_AT_FDCWD,
                                            (UWord)path, (UWord)buf, bufsiz);
-#  elif defined(VGO_linux) || defined(VGO_darwin)
+#  elif defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_netbsd)
    res = VG_(do_syscall3)(__NR_readlink, (UWord)path, (UWord)buf, bufsiz);
 #  elif defined(VGO_solaris)
    res = VG_(do_syscall4)(__NR_readlinkat, VKI_AT_FDCWD, (UWord)path,
@@ -727,7 +730,7 @@ Int VG_(access) ( const HChar* path, Boo
              | (ixusr ? VKI_X_OK : 0);
 #  if defined(VGP_arm64_linux)
    SysRes res = VG_(do_syscall3)(__NR_faccessat, VKI_AT_FDCWD, (UWord)path, w);
-#  elif defined(VGO_linux) || defined(VGO_darwin)
+#  elif defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_netbsd)
    SysRes res = VG_(do_syscall2)(__NR_access, (UWord)path, w);
 #  elif defined(VGO_solaris)
    SysRes res = VG_(do_syscall4)(__NR_faccessat, VKI_AT_FDCWD, (UWord)path,
@@ -872,6 +875,10 @@ SysRes VG_(pread) ( Int fd, void* buf, I
       || defined(VGP_mips64_linux) || defined(VGP_arm64_linux)
    res = VG_(do_syscall4)(__NR_pread64, fd, (UWord)buf, count, offset);
    return res;
+#  elif defined(VGP_amd64_netbsd)
+   vg_assert(sizeof(OffT) == 8);
+   res = VG_(do_syscall4)(__NR_pread, fd, (UWord)buf, count, offset);
+   return res;
 #  elif defined(VGP_amd64_darwin)
    vg_assert(sizeof(OffT) == 8);
    res = VG_(do_syscall4)(__NR_pread_nocancel, fd, (UWord)buf, count, offset);
@@ -1023,7 +1030,7 @@ UShort VG_(ntohs) ( UShort x )
 */
 Int VG_(connect_via_socket)( const HChar* str )
 {
-#  if defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_solaris)
+#  if defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_solaris) || defined(VGO_netbsd)
    Int sd, res;
    struct vki_sockaddr_in servAddr;
    UInt   ip   = 0;
@@ -1124,7 +1131,7 @@ Int VG_(socket) ( Int domain, Int type, 
 
 #  elif defined(VGP_amd64_linux) || defined(VGP_arm_linux) \
         || defined(VGP_mips32_linux) || defined(VGP_mips64_linux) \
-        || defined(VGP_arm64_linux)
+        || defined(VGP_arm64_linux) || defined(VGO_netbsd)
    SysRes res;
    res = VG_(do_syscall3)(__NR_socket, domain, type, protocol );
    return sr_isError(res) ? -1 : sr_Res(res);
@@ -1179,7 +1186,7 @@ Int my_connect ( Int sockfd, struct vki_
 
 #  elif defined(VGP_amd64_linux) || defined(VGP_arm_linux) \
         || defined(VGP_mips32_linux) || defined(VGP_mips64_linux) \
-        || defined(VGP_arm64_linux)
+        || defined(VGP_arm64_linux) || defined(VGO_netbsd)
    SysRes res;
    res = VG_(do_syscall3)(__NR_connect, sockfd, (UWord)serv_addr, addrlen);
    return sr_isError(res) ? -1 : sr_Res(res);
@@ -1226,7 +1233,7 @@ Int VG_(write_socket)( Int sd, const voi
 
 #  elif defined(VGP_amd64_linux) || defined(VGP_arm_linux) \
         || defined(VGP_mips32_linux) || defined(VGP_mips64_linux) \
-        || defined(VGP_arm64_linux)
+        || defined(VGP_arm64_linux) || defined(VGO_netbsd)
    SysRes res;
    res = VG_(do_syscall6)(__NR_sendto, sd, (UWord)msg, 
                                        count, VKI_MSG_NOSIGNAL, 0,0);
@@ -1262,7 +1269,7 @@ Int VG_(getsockname) ( Int sd, struct vk
    return sr_isError(res) ? -1 : sr_Res(res);
 
 #  elif defined(VGP_amd64_linux) || defined(VGP_arm_linux) \
-        || defined(VGP_mips64_linux) || defined(VGP_arm64_linux)
+        || defined(VGP_mips64_linux) || defined(VGP_arm64_linux) || defined(VGO_netbsd)
    SysRes res;
    res = VG_(do_syscall3)( __NR_getsockname,
                            (UWord)sd, (UWord)name, (UWord)namelen );
@@ -1300,7 +1307,7 @@ Int VG_(getpeername) ( Int sd, struct vk
    return sr_isError(res) ? -1 : sr_Res(res);
 
 #  elif defined(VGP_amd64_linux) || defined(VGP_arm_linux) \
-        || defined(VGP_mips64_linux) || defined(VGP_arm64_linux)
+        || defined(VGP_mips64_linux) || defined(VGP_arm64_linux) || defined(VGO_netbsd)
    SysRes res;
    res = VG_(do_syscall3)( __NR_getpeername,
                            (UWord)sd, (UWord)name, (UWord)namelen );
@@ -1341,14 +1348,14 @@ Int VG_(getsockopt) ( Int sd, Int level,
 
 #  elif defined(VGP_amd64_linux) || defined(VGP_arm_linux) \
         || defined(VGP_mips32_linux) || defined(VGP_mips64_linux) \
-        || defined(VGP_arm64_linux)
+        || defined(VGP_arm64_linux) || defined(VGO_netbsd)
    SysRes res;
    res = VG_(do_syscall5)( __NR_getsockopt,
                            (UWord)sd, (UWord)level, (UWord)optname, 
                            (UWord)optval, (UWord)optlen );
    return sr_isError(res) ? -1 : sr_Res(res);
 
-#  elif defined(VGO_darwin)
+#  elif defined(VGO_darwin) || defined(VGO_netbsd)
    SysRes res;
    res = VG_(do_syscall5)( __NR_getsockopt,
                            (UWord)sd, (UWord)level, (UWord)optname, 
