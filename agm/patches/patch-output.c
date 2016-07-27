$NetBSD$

--- output.c.orig	2016-07-27 09:11:40.798285885 +0000
+++ output.c
@@ -24,6 +24,7 @@ char output_RCSid[] = "Revision: 1.5 $";
 
 #include "agm.h"
 
+void
 print_prevs (percent)
      int percent;
 {
