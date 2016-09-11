$NetBSD$

--- jerry-core/vm/vm.c.orig	2016-09-01 12:52:10.000000000 +0000
+++ jerry-core/vm/vm.c
@@ -36,7 +36,7 @@
 #include "vm.h"
 #include "vm-stack.h"
 
-#include <alloca.h>
+#include <stdlib.h>
 
 /** \addtogroup vm Virtual machine
  * @{
