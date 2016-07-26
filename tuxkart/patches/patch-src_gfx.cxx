$NetBSD$

--- src/gfx.cxx.orig	2004-03-18 16:21:44.000000000 +0000
+++ src/gfx.cxx
@@ -4,9 +4,15 @@
 #ifndef WIN32
 #include <unistd.h>
 #include <string.h>
+#ifdef __NetBSD__
+#include <machine/pio.h>
+#else
 #include <sys/io.h>
+#endif
+#ifdef __GLIBC__
 #include <sys/perm.h>                                                           
 #endif
+#endif
 
 static unsigned int lastKeystroke = 0 ;
 
@@ -172,5 +178,3 @@ void GFX::done ()
     stereo = -stereo ;
   }
 }
-
-
