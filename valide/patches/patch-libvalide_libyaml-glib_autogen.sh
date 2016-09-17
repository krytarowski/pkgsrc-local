$NetBSD$

--- libvalide/libyaml-glib/autogen.sh.orig	2011-02-20 14:11:41.000000000 +0000
+++ libvalide/libyaml-glib/autogen.sh
@@ -29,7 +29,6 @@ autoconf || exit $?
 
 cd $ORIGDIR || exit $?
 
-if ! test x$1 == x--no-configure; then
+if ! test x$1 = x--no-configure; then
 ./configure --enable-maintainer-mode $*
 fi;
-
