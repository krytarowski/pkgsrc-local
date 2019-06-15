$NetBSD$

--- plugins/DebuggerCore/unix/Posix.cpp.orig	2019-06-13 22:49:27.000000000 +0000
+++ plugins/DebuggerCore/unix/Posix.cpp
@@ -5,7 +5,9 @@
 #include <signal.h>
 #include <sys/types.h>
 #include <sys/wait.h>
+#include <sys/time.h>
 #include <unistd.h>
+#include <signal.h>
 
 #include <QProcess>
 
@@ -18,6 +20,10 @@
 #endif
 #endif
 
+#ifdef Q_OS_NETBSD
+#define USE_SIGTIMEDWAIT
+#endif
+
 namespace DebuggerCorePlugin {
 
 #if !defined(USE_SIGTIMEDWAIT)
