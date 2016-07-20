$NetBSD$

--- src/hackbench/hackbench.c.orig	2016-05-13 18:30:12.000000000 +0000
+++ src/hackbench/hackbench.c
@@ -212,12 +212,14 @@ static int create_worker(childinfo_t *ch
 			return -1;
 		}
 
+#if 0
 #ifndef __ia64__
 		if (pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN) != 0) {
 			sneeze("pthread_attr_setstacksize()");
 			return -1;
 		}
 #endif
+#endif
 
 		if ((err=pthread_create(&child->threadid, &attr, func, ctx)) != 0) {
 			sneeze("pthread_create failed()");
