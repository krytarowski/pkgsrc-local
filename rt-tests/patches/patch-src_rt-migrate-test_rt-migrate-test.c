$NetBSD$

--- src/rt-migrate-test/rt-migrate-test.c.orig	2016-05-13 18:30:12.000000000 +0000
+++ src/rt-migrate-test/rt-migrate-test.c
@@ -39,8 +39,8 @@
 #include <fcntl.h>
 #include <signal.h>
 #include <sys/time.h>
-#include <linux/unistd.h>
-#include <sys/syscall.h>
+//#include <linux/unistd.h>
+//#include <sys/syscall.h>
 #include <errno.h>
 #include <sched.h>
 #include <pthread.h>
