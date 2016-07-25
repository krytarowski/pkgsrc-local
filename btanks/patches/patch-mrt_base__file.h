$NetBSD$

--- mrt/base_file.h.orig	2009-04-04 20:28:59.000000000 +0000
+++ mrt/base_file.h
@@ -20,6 +20,7 @@
 */
 
 #include <string>
+#include <unistd.h>
 #include "export_mrt.h"
 
 namespace mrt {
