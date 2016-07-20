$NetBSD$

--- src/lib/rt-utils.c.orig	2016-05-13 18:30:12.000000000 +0000
+++ src/lib/rt-utils.c
@@ -17,7 +17,7 @@
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <unistd.h>
-#include <sys/syscall.h> /* For SYS_gettid definitions */
+//#include <sys/syscall.h> /* For SYS_gettid definitions */
 #include "rt-utils.h"
 #include "rt-sched.h"
 #include "error.h"
@@ -287,12 +287,18 @@ const char *policy_to_string(int policy)
 		return "SCHED_FIFO";
 	case SCHED_RR:
 		return "SCHED_RR";
+#ifdef SCHED_BATCH
 	case SCHED_BATCH:
 		return "SCHED_BATCH";
+#endif
+#ifdef SCHED_IDLE
 	case SCHED_IDLE:
 		return "SCHED_IDLE";
+#endif
+#ifdef SCHED_DEADLINE
 	case SCHED_DEADLINE:
 		return "SCHED_DEADLINE";
+#endif
 	}
 
 	return "unknown";
@@ -306,17 +312,29 @@ uint32_t string_to_policy(const char *st
 		return SCHED_FIFO;
 	else if (!strcmp(str, "rr"))
 		return SCHED_RR;
+#ifdef SCHED_BATCH
 	else if (!strcmp(str, "batch"))
 		return SCHED_BATCH;
+#endif
+#ifdef SCHED_IDLE
 	else if (!strcmp(str, "idle"))
 		return SCHED_IDLE;
+#endif
+#ifdef SCHED_DEADLINE
 	else if (!strcmp(str, "deadline"))
 		return SCHED_DEADLINE;
+#endif
 
 	return 0;
 }
 
-pid_t gettid(void)
+#include <lwp.h>
+
+lwpid_t gettid(void)
 {
+#ifdef __NetBSD__
+	return _lwp_self();
+#else
 	return syscall(SYS_gettid);
+#endif
 }
