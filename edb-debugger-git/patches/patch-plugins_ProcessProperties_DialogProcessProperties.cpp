$NetBSD$

--- plugins/ProcessProperties/DialogProcessProperties.cpp.orig	2019-06-13 22:49:27.000000000 +0000
+++ plugins/ProcessProperties/DialogProcessProperties.cpp
@@ -38,7 +38,7 @@ along with this program.  If not, see <h
 #include <QStringListModel>
 #include <QUrl>
 
-#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD) || defined(Q_OS_OPENBSD)
+#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD) || defined(Q_OS_OPENBSD) || defined(Q_OS_NETBSD)
 #include <link.h>
 #include <arpa/inet.h>
 #endif
