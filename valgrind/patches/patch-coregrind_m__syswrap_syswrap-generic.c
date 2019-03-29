$NetBSD$

--- coregrind/m_syswrap/syswrap-generic.c.orig	2018-05-05 07:42:22.000000000 +0000
+++ coregrind/m_syswrap/syswrap-generic.c
@@ -30,7 +30,7 @@
    The GNU General Public License is contained in the file COPYING.
 */
 
-#if defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_solaris)
+#if defined(VGO_linux) || defined(VGO_darwin) || defined(VGO_solaris) || defined(VGO_netbsd)
 
 #include "pub_core_basics.h"
 #include "pub_core_vki.h"
@@ -270,7 +270,7 @@ ML_(notify_core_and_tool_of_mprotect) ( 
 
 
 
-#if HAVE_MREMAP
+#if HAVE_MREMAP && 0
 /* Expand (or shrink) an existing mapping, potentially moving it at
    the same time (controlled by the MREMAP_MAYMOVE flag).  Nightmare.
 */
@@ -926,7 +926,7 @@ void VG_(init_preopened_fds)(void)
   out:
    VG_(close)(sr_Res(f));
 
-#elif defined(VGO_darwin)
+#elif defined(VGO_darwin) || defined(VGO_netbsd)
    init_preopened_fds_without_proc_self_fd();
 
 #elif defined(VGO_solaris)
@@ -1131,6 +1131,11 @@ void pre_mem_read_sockaddr ( ThreadId ti
    VG_(sprintf) ( outmsg, description, "sa_family" );
    PRE_MEM_READ( outmsg, (Addr) &sa->sa_family, sizeof(vki_sa_family_t));
 
+#if defined(VGO_netbsd)
+   VG_(sprintf) ( outmsg, description, ".sa_len" );
+   PRE_MEM_READ( outmsg, (Addr) &sa->sa_len, sizeof(char));
+#endif
+
    /* Don't do any extra checking if we cannot determine the sa_family. */
    if (! ML_(safe_to_deref) (&sa->sa_family, sizeof(vki_sa_family_t)))
       return;
@@ -1818,6 +1823,9 @@ UInt get_sem_count( Int semid )
 
    return buf.sem_nsems;
 
+#  elif defined(VGO_netbsd)
+   return 0;
+
 #  else
    struct vki_semid_ds buf;
    arg.buf = &buf;
@@ -1844,8 +1852,10 @@ ML_(generic_PRE_sys_semctl) ( ThreadId t
    case VKI_SEM_INFO:
    case VKI_IPC_INFO|VKI_IPC_64:
    case VKI_SEM_INFO|VKI_IPC_64:
+#if !defined(VGO_netbsd)
       PRE_MEM_WRITE( "semctl(IPC_INFO, arg.buf)",
                      (Addr)arg.buf, sizeof(struct vki_seminfo) );
+#endif
       break;
 #endif
 
@@ -1923,7 +1933,9 @@ ML_(generic_POST_sys_semctl) ( ThreadId 
    case VKI_SEM_INFO:
    case VKI_IPC_INFO|VKI_IPC_64:
    case VKI_SEM_INFO|VKI_IPC_64:
+#if !defined(VGO_netbsd)
       POST_MEM_WRITE( (Addr)arg.buf, sizeof(struct vki_seminfo) );
+#endif
       break;
 #endif
 
@@ -2456,6 +2468,7 @@ ML_(generic_PRE_sys_mmap) ( ThreadId tid
 #define PRE(name)      DEFN_PRE_TEMPLATE(generic, name)
 #define POST(name)     DEFN_POST_TEMPLATE(generic, name)
 
+#if !defined(VGO_netbsd)
 PRE(sys_exit)
 {
    ThreadState* tst;
@@ -2469,6 +2482,7 @@ PRE(sys_exit)
    tst->os_state.exitcode = ARG1;
    SET_STATUS_Success(0);
 }
+#endif
 
 PRE(sys_ni_syscall)
 {
@@ -3339,7 +3353,7 @@ PRE(sys_fork)
 
    if (!SUCCESS) return;
 
-#if defined(VGO_linux)
+#if defined(VGO_linux) || defined(VGO_netbsd)
    // RES is 0 for child, non-0 (the child's PID) for parent.
    is_child = ( RES == 0 ? True : False );
    child_pid = ( is_child ? -1 : RES );
