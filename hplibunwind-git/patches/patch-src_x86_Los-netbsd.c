$NetBSD$

--- src/x86/Los-netbsd.c.orig	2018-09-04 16:41:38.192708648 +0000
+++ src/x86/Los-netbsd.c
@@ -0,0 +1,5 @@
+#define UNW_LOCAL_ONLY
+#include <libunwind.h>
+#if defined(UNW_LOCAL_ONLY) && !defined(UNW_REMOTE_ONLY)
+#include "Gos-netbsd.c"
+#endif
