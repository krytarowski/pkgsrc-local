$NetBSD$

--- plugins/DebuggerCore/unix/Posix.h.orig	2019-06-13 22:49:27.000000000 +0000
+++ plugins/DebuggerCore/unix/Posix.h
@@ -3,6 +3,9 @@
 #define POSIX_20181211_H_
 
 #include "OSTypes.h"
+#include <sys/types.h>
+#include <sys/time.h>
+
 #include <cstdint>
 
 namespace DebuggerCorePlugin {
