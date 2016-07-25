$NetBSD$

--- clunk/source.cpp.orig	2009-08-04 21:23:14.000000000 +0000
+++ clunk/source.cpp
@@ -27,7 +27,7 @@
 #include <assert.h>
 #include "clunk_assert.h"
 
-#if defined _MSC_VER || __APPLE__ || __FreeBSD__
+#if defined _MSC_VER || __APPLE__ || __FreeBSD__ || __NetBSD__
 #	define pow10f(x) powf(10.0f, (x))
 #	define log2f(x) (logf(x) / M_LN2)
 #endif
