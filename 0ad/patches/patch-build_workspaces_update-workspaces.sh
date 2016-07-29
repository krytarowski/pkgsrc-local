$NetBSD$

--- build/workspaces/update-workspaces.sh.orig	2015-06-14 20:43:12.000000000 +0000
+++ build/workspaces/update-workspaces.sh
@@ -26,7 +26,7 @@ JOBS=${JOBS:="-j2"}
 # Some of our makefiles depend on GNU make, so we set some sane defaults if MAKE
 # is not set.
 case "`uname -s`" in
-  "FreeBSD" | "OpenBSD" )
+  "FreeBSD" | "NetBSD" | "OpenBSD" )
     MAKE=${MAKE:="gmake"}
     ;;
   * )
