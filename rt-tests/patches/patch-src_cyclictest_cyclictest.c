$NetBSD$

--- src/cyclictest/cyclictest.c.orig	2016-05-13 18:30:12.000000000 +0000
+++ src/cyclictest/cyclictest.c
@@ -25,17 +25,17 @@
 #include <time.h>
 #include <errno.h>
 #include <limits.h>
-#include <linux/unistd.h>
+//#include <linux/unistd.h>
 
-#include <sys/prctl.h>
+//#include <sys/prctl.h>
 #include <sys/stat.h>
-#include <sys/sysinfo.h>
+//#include <sys/sysinfo.h>
 #include <sys/types.h>
 #include <sys/time.h>
 #include <sys/resource.h>
 #include <sys/utsname.h>
 #include <sys/mman.h>
-#include <sys/syscall.h>
+//#include <sys/syscall.h>
 #include "rt_numa.h"
 
 #include "rt-utils.h"
