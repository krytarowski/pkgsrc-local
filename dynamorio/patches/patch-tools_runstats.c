$NetBSD$

--- tools/runstats.c.orig	2016-04-10 21:51:59.000000000 +0000
+++ tools/runstats.c
@@ -43,7 +43,7 @@
 
 #include "configure.h"
 
-#ifdef MACOS
+#if defined(MACOS) || defined(__NetBSD__)
 /* struct timeval.tv_usec is int, not long int */
 #  define USEC_FMT "d"
 #else
