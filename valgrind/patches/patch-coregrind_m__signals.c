$NetBSD$

--- coregrind/m_signals.c.orig	2018-09-30 04:41:00.000000000 +0000
+++ coregrind/m_signals.c
@@ -512,6 +512,22 @@ typedef struct SigQueue {
       srP->misc.AMD64.r_rbp = (ULong)(ss->__rbp);
    }
 
+#elif defined(VGP_amd64_netbsd)
+#  define VG_UCONTEXT_INSTR_PTR(uc)       VKI__UC_MACHINE_PC(uc)
+#  define VG_UCONTEXT_STACK_PTR(uc)       VKI__UC_MACHINE_SP(uc)
+#  define VG_UCONTEXT_FRAME_PTR(uc)       VKI__UC_MACHINE_FP(uc)
+#  define VG_UCONTEXT_SYSCALL_NUM(uc)     ((uc)->uc_mcontext.__gregs[VKI__REG_RAX])
+#  define VG_UCONTEXT_SYSCALL_SYSRES(uc)                        \
+      /* Convert the value in uc_mcontext.rax into a SysRes. */ \
+      VG_(mk_SysRes_amd64_netbsd)( ((uc)->uc_mcontext.__gregs[VKI__REG_RAX]), \
+         ((uc)->uc_mcontext.__gregs[VKI__REG_RDX]), ((uc)->uc_mcontext.__gregs[VKI__REG_RFALAGS]) != 0 ? True : False )
+#  define VG_UCONTEXT_LINK_REG(uc)        0 /* No LR on amd64 either */                                                                                      
+#  define VG_UCONTEXT_TO_UnwindStartRegs(srP, uc)        \
+      { (srP)->r_pc = VKI__UC_MACHINE_PC(uc);             \
+        (srP)->r_sp = VKI__UC_MACHINE_SP(uc);             \
+        (srP)->misc.AMD64.r_rbp = VKI__UC_MACHINE_FP(uc); \
+      }
+
 #elif defined(VGP_s390x_linux)
 
 #  define VG_UCONTEXT_INSTR_PTR(uc)       ((uc)->uc_mcontext.regs.psw.addr)
@@ -605,7 +621,7 @@ typedef struct SigQueue {
 #if defined(VGO_linux)
 #  define VKI_SIGINFO_si_addr  _sifields._sigfault._addr
 #  define VKI_SIGINFO_si_pid   _sifields._kill._pid
-#elif defined(VGO_darwin) || defined(VGO_solaris)
+#elif defined(VGO_darwin) || defined(VGO_solaris) || defined(VGO_netbsd)
 #  define VKI_SIGINFO_si_addr  si_addr
 #  define VKI_SIGINFO_si_pid   si_pid
 #else
@@ -1031,7 +1047,7 @@ static void handle_SCSS_change ( Bool fo
       ksa.sa_flags    = skss.skss_per_sig[sig].skss_flags;
 #     if !defined(VGP_ppc32_linux) && \
          !defined(VGP_x86_darwin) && !defined(VGP_amd64_darwin) && \
-         !defined(VGP_mips32_linux) && !defined(VGO_solaris)
+         !defined(VGP_mips32_linux) && !defined(VGO_solaris) && !defined(VGO_netbsd)
       ksa.sa_restorer = my_sigreturn;
 #     endif
       /* Re above ifdef (also the assertion below), PaulM says:
@@ -1078,7 +1094,7 @@ static void handle_SCSS_change ( Bool fo
 #        if !defined(VGP_ppc32_linux) && \
             !defined(VGP_x86_darwin) && !defined(VGP_amd64_darwin) && \
             !defined(VGP_mips32_linux) && !defined(VGP_mips64_linux) && \
-            !defined(VGO_solaris)
+            !defined(VGO_solaris) && !defined(VGO_netbsd)
          vg_assert(ksa_old.sa_restorer == my_sigreturn);
 #        endif
          VG_(sigaddset)( &ksa_old.sa_mask, VKI_SIGKILL );
@@ -1199,7 +1215,7 @@ SysRes VG_(do_sys_sigaction) ( Int signo
       old_act->sa_flags    = scss.scss_per_sig[signo].scss_flags;
       old_act->sa_mask     = scss.scss_per_sig[signo].scss_mask;
 #     if !defined(VGP_x86_darwin) && !defined(VGP_amd64_darwin) && \
-         !defined(VGO_solaris)
+         !defined(VGO_solaris) && !defined(VGO_netbsd)
       old_act->sa_restorer = scss.scss_per_sig[signo].scss_restorer;
 #     endif
    }
@@ -1212,7 +1228,7 @@ SysRes VG_(do_sys_sigaction) ( Int signo
 
       scss.scss_per_sig[signo].scss_restorer = NULL;
 #     if !defined(VGP_x86_darwin) && !defined(VGP_amd64_darwin) && \
-         !defined(VGO_solaris)
+         !defined(VGO_solaris) && !defined(VGO_netbsd)
       scss.scss_per_sig[signo].scss_restorer = new_act->sa_restorer;
 #     endif
 
@@ -1558,7 +1574,7 @@ void VG_(kill_self)(Int sigNo)
    sa.ksa_handler = VKI_SIG_DFL;
    sa.sa_flags = 0;
 #  if !defined(VGP_x86_darwin) && !defined(VGP_amd64_darwin) && \
-      !defined(VGO_solaris)
+      !defined(VGO_solaris) && !defined(VGO_netbsd)
    sa.sa_restorer = 0;
 #  endif
    VG_(sigemptyset)(&sa.sa_mask);
@@ -1588,7 +1604,7 @@ void VG_(kill_self)(Int sigNo)
 // pass in some other details that can help when si_code is unreliable.
 static Bool is_signal_from_kernel(ThreadId tid, int signum, int si_code)
 {
-#  if defined(VGO_linux) || defined(VGO_solaris)
+#  if defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
    // On Linux, SI_USER is zero, negative values are from the user, positive
    // values are from the kernel.  There are SI_FROMUSER and SI_FROMKERNEL
    // macros but we don't use them here because other platforms don't have
@@ -2278,7 +2294,7 @@ static int sanitize_si_code(int si_code)
       mask them off) sign extends them when exporting to user space so
       we do the same thing here. */
    return (Short)si_code;
-#elif defined(VGO_darwin) || defined(VGO_solaris)
+#elif defined(VGO_darwin) || defined(VGO_solaris) || defined(VGO_netbsd)
    return si_code;
 #else
 #  error Unknown OS
@@ -2904,7 +2920,7 @@ void pp_ksigaction ( vki_sigaction_toK_t
                sa->ksa_handler, 
                (UInt)sa->sa_flags, 
 #              if !defined(VGP_x86_darwin) && !defined(VGP_amd64_darwin) && \
-                  !defined(VGO_solaris)
+                  !defined(VGO_solaris) && !defined(VGO_netbsd)
                   sa->sa_restorer
 #              else
                   (void*)0
@@ -2927,7 +2943,7 @@ void VG_(set_default_handler)(Int signo)
    sa.ksa_handler = VKI_SIG_DFL;
    sa.sa_flags = 0;
 #  if !defined(VGP_x86_darwin) && !defined(VGP_amd64_darwin) && \
-      !defined(VGO_solaris)
+      !defined(VGO_solaris) && !defined(VGO_netbsd)
    sa.sa_restorer = 0;
 #  endif
    VG_(sigemptyset)(&sa.sa_mask);
@@ -3047,7 +3063,7 @@ void VG_(sigstartup_actions) ( void )
 	 tsa.ksa_handler = (void *)sync_signalhandler;
 	 tsa.sa_flags = VKI_SA_SIGINFO;
 #        if !defined(VGP_x86_darwin) && !defined(VGP_amd64_darwin) && \
-            !defined(VGO_solaris)
+            !defined(VGO_solaris) && !defined(VGO_netbsd)
 	 tsa.sa_restorer = 0;
 #        endif
 	 VG_(sigfillset)(&tsa.sa_mask);
@@ -3075,7 +3091,7 @@ void VG_(sigstartup_actions) ( void )
 
       scss.scss_per_sig[i].scss_restorer = NULL;
 #     if !defined(VGP_x86_darwin) && !defined(VGP_amd64_darwin) && \
-         !defined(VGO_solaris)
+         !defined(VGO_solaris) && !defined(VGO_netbsd)
       scss.scss_per_sig[i].scss_restorer = sa.sa_restorer;
 #     endif
 
