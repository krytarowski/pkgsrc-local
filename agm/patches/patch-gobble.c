$NetBSD$

--- gobble.c.orig	2016-07-27 08:59:42.595830335 +0000
+++ gobble.c
@@ -22,6 +22,9 @@ char gobble_RCSid[] = "Revision: 1.4 $";
 
 #include "agm.h"
 
+#include <stdlib.h>
+
+void
 gobble_file (filename, command)
     char *filename, *command;
 {
@@ -81,4 +84,3 @@ gobble_file (filename, command)
   }
   if (notquiet) printf (" %d words\n", wordcount - before_count);
 }
-
