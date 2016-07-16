$NetBSD$

--- tools/gn/args.cc.orig	2016-06-16 19:02:41.000000000 +0000
+++ tools/gn/args.cc
@@ -237,6 +237,8 @@ void Args::SetSystemVarsLocked(Scope* de
   os = "linux";
 #elif defined(OS_ANDROID)
   os = "android";
+#elif defined(OS_NETBSD)
+  os = "netbsd";
 #else
   #error Unknown OS type.
 #endif
