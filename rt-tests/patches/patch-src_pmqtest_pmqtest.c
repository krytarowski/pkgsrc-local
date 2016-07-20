$NetBSD$

--- src/pmqtest/pmqtest.c.orig	2016-05-13 18:30:12.000000000 +0000
+++ src/pmqtest/pmqtest.c
@@ -32,7 +32,7 @@
 #include <sys/stat.h>
 #include <sys/time.h>
 #include <sys/mman.h>
-#include <linux/unistd.h>
+//#include <linux/unistd.h>
 #include <utmpx.h>
 #include <mqueue.h>
 #include "rt-utils.h"
