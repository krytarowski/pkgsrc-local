$NetBSD$

--- src/x86_64/Los-netbsd.c.orig	2018-09-04 16:46:09.587426950 +0000
+++ src/x86_64/Los-netbsd.c
@@ -0,0 +1,5 @@
+#define UNW_LOCAL_ONLY
+#include <libunwind.h>
+#if defined(UNW_LOCAL_ONLY) && !defined(UNW_REMOTE_ONLY)
+#include "Gos-netbsd.c"
+#endif
