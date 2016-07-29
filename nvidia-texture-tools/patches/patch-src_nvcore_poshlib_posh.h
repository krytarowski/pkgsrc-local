$NetBSD$

--- src/nvcore/poshlib/posh.h.orig	2010-05-15 09:12:05.000000000 +0000
+++ src/nvcore/poshlib/posh.h
@@ -372,6 +372,11 @@ Metrowerks:
 #  define POSH_OS_STRING "Amiga"
 #endif
 
+#if defined __NetBSD__
+#  define POSH_OS_NETBSD 1 
+#  define POSH_OS_STRING "NetBSD"
+#endif
+
 #if defined __unix__
 #  define POSH_OS_UNIX 1 
 #  if !defined POSH_OS_STRING
@@ -1003,5 +1008,3 @@ extern posh_i64_t  POSH_ReadI64FromBig( 
 #ifdef __cplusplus
 }
 #endif
-
-
