$NetBSD$

--- wordfuncs.c.orig	2016-07-27 09:03:24.626725323 +0000
+++ wordfuncs.c
@@ -14,6 +14,8 @@ char wordfuncs_RCSid[] = "Revision: 1.2 
 
 #include "agm.h"
 
+#include <stdlib.h>
+
 int contains (word, subword, length)
     char *word, *subword;
     unsigned int *length;
