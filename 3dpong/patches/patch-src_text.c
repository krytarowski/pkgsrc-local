$NetBSD$

--- src/text.c.orig	1997-12-10 23:27:49.000000000 +0000
+++ src/text.c
@@ -6,6 +6,7 @@
 */
 
 #include <X11/Xlib.h>
+#include <string.h>
 #include "text.h"
 
 int FontHeight(XFontStruct *font_struct)
