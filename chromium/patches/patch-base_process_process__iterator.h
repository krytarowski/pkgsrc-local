$NetBSD$

--- base/process/process_iterator.h.orig	2016-06-16 19:02:01.000000000 +0000
+++ base/process/process_iterator.h
@@ -24,6 +24,11 @@
 #include <tlhelp32.h>
 #elif defined(OS_MACOSX) || defined(OS_OPENBSD)
 #include <sys/sysctl.h>
+#elif defined(OS_NETBSD)
+//#define _KMEMUSER
+#include <sys/param.h>
+#include <sys/types.h>
+#include <sys/sysctl.h>
 #elif defined(OS_FREEBSD)
 #include <sys/user.h>
 #elif defined(OS_POSIX)
@@ -109,8 +114,11 @@ class BASE_EXPORT ProcessIterator {
 #if defined(OS_WIN)
   HANDLE snapshot_;
   bool started_iteration_;
-#elif defined(OS_MACOSX) || defined(OS_BSD)
-  std::vector<kinfo_proc> kinfo_procs_;
+#elif defined(OS_MACOSX) || defined(OS_FREEBSD) || defined(OS_OPENBSD)
+  std::vector<struct kinfo_proc> kinfo_procs_;
+  size_t index_of_kinfo_proc_;
+#elif defined(OS_NETBSD)
+  std::vector<struct kinfo_proc2> kinfo_procs_;
   size_t index_of_kinfo_proc_;
 #elif defined(OS_POSIX)
   DIR* procfs_dir_;
