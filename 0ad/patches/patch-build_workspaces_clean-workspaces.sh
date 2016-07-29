$NetBSD$

--- build/workspaces/clean-workspaces.sh.orig	2015-08-19 01:30:09.000000000 +0000
+++ build/workspaces/clean-workspaces.sh
@@ -3,7 +3,7 @@
 # Some of our makefiles depend on GNU make, so we set some sane defaults if MAKE
 # is not set.
 case "`uname -s`" in
-  "FreeBSD" | "OpenBSD" )
+  "FreeBSD" | "NetBSD" | "OpenBSD" )
     MAKE=${MAKE:="gmake"}
     ;;
   * )
