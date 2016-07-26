$NetBSD$

--- src/guNet.cxx.orig	2002-01-30 20:55:06.000000000 +0000
+++ src/guNet.cxx
@@ -32,6 +32,7 @@
  #include <sys/uio.h>
  #include <arpa/inet.h>
  #include <sys/errno.h>
+ #include <errno.h>
 #endif
 #include <fcntl.h>
 
@@ -216,6 +217,3 @@ int guUDPConnection::recvMessage ( char 
   return r ;
 #endif
 }
-
-
-
