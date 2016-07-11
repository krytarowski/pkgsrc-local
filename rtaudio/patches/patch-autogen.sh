$NetBSD$

--- autogen.sh.orig	2016-02-22 21:15:53.000000000 +0000
+++ autogen.sh
@@ -22,8 +22,8 @@ fi
 }
 
 # Make some directories required by automake, if they don't exist
-if ! [ -d config ]; then mkdir -v config; fi
-if ! [ -d m4     ]; then mkdir -v m4;     fi
+if ! [ -d config ]; then mkdir config; fi
+if ! [ -d m4     ]; then mkdir m4;     fi
 
 if ! autoreconf --version </dev/null >/dev/null 2>&1
 then
