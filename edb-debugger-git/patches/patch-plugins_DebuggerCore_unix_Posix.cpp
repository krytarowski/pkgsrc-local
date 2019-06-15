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
@@ -121,10 +127,13 @@ ssize_t Posix::write(int fd, const void 
  * @return
  */
 int Posix::select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
+	struct timespec ts;
+	TIMEVAL_TO_TIMESPEC(timeout, &ts);
 	int ret;
 	do {
-		ret = ::select(nfds, readfds, writefds, exceptfds, timeout);
+		ret = ::select(nfds, readfds, writefds, exceptfds, &ts);
 	} while (ret == -1 && errno == EINTR);
+	TIMESPEC_TO_TIMEVAL(&s, timeout);
 	return ret;
 }
 
