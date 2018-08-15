$NetBSD$

--- hfuzz_cc/hfuzz-cc.c.orig	2018-08-15 03:14:56.481916447 +0000
+++ hfuzz_cc/hfuzz-cc.c
@@ -391,7 +391,7 @@ static int ldMode(int argc, char** argv)
 #endif /* _HF_ARCH_DARWIN */
 
     /* Needed by the libhfcommon */
-    args[j++] = "-lpthread";
+    args[j++] = "-pthread";
 
     return execCC(j, args);
 }
