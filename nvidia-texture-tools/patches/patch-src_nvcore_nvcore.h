$NetBSD$

--- src/nvcore/nvcore.h.orig	2010-05-15 09:12:05.000000000 +0000
+++ src/nvcore/nvcore.h
@@ -43,6 +43,9 @@
 #elif defined POSH_OS_MINGW
 #	define NV_OS_MINGW 1
 #	define NV_OS_WIN32 1
+#elif defined POSH_OS_NETBSD
+#	define NV_OS_NETBSD 1
+#	define NV_OS_UNIX 1
 #elif defined POSH_OS_OSX
 #	define NV_OS_DARWIN 1
 #	define NV_OS_UNIX 1
@@ -158,7 +161,7 @@
 #elif NV_CC_GNUC
 #	if NV_OS_LINUX
 #		include "DefsGnucLinux.h"
-#	elif NV_OS_DARWIN
+#	elif NV_OS_DARWIN || NV_OS_NETBSD
 #		include "DefsGnucDarwin.h"
 #	elif NV_OS_MINGW
 #		include "DefsGnucWin32.h"
