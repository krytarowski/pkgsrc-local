$NetBSD$

--- src/randnum.c.orig	1997-12-10 01:56:00.000000000 +0000
+++ src/randnum.c
@@ -10,6 +10,7 @@
 
 #include <stdio.h>
 #include <sys/time.h>
+#include <stdlib.h>
 #include "randnum.h"
 
 void randinit()
