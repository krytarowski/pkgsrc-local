$NetBSD$

--- libhfcommon/log.c.orig	2018-08-08 23:14:18.000000000 +0000
+++ libhfcommon/log.c
@@ -41,9 +41,12 @@
 #if defined(_HF_ARCH_LINUX)
 #include <sys/syscall.h>
 #define __hf_pid() (pid_t) syscall(__NR_gettid)
-#else /* defined(_HF_ARCH_LINUX) */
+#elif defined(_HF_ARCH_NETBSD)
+#include <lwp.h>
+#define __hf_pid() _lwp_self()
+#else
 #define __hf_pid() getpid()
-#endif /* defined(_HF_ARCH_LINUX) */
+#endif
 
 static int log_fd = STDERR_FILENO;
 static bool log_fd_isatty = false;
