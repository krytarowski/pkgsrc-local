$NetBSD$

--- tools/nudgeunix.c.orig	2016-04-10 21:51:59.000000000 +0000
+++ tools/nudgeunix.c
@@ -145,7 +145,11 @@ main(int argc, const char *argv[])
     assert(success); /* failure means kernel's sigqueueinfo has changed */
 
     /* send the nudge */
+#if defined(__NetBSD__)
+    i = sigqueueinfo(target_pid, &info);
+#else
     i = syscall(SYS_rt_sigqueueinfo, target_pid, NUDGESIG_SIGNUM, &info);
+#endif
     if (i < 0)
         fprintf(stderr, "nudge FAILED with error %d\n", i);
     return i;
