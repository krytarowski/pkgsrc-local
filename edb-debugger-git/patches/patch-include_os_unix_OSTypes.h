$NetBSD$

--- include/os/unix/OSTypes.h.orig	2019-06-13 22:49:27.000000000 +0000
+++ include/os/unix/OSTypes.h
@@ -24,7 +24,11 @@ along with this program.  If not, see <h
 namespace edb {
 	using ::pid_t;
 	using ::uid_t;
+#if defined(Q_OS_NETBSD)
+	using tid_t = ::lwpid_t;
+#else
 	using tid_t = ::pid_t;
+#endif
 }
 
 #endif
