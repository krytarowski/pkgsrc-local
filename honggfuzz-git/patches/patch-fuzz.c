$NetBSD$

--- fuzz.c.orig	2018-08-13 23:34:18.801736693 +0000
+++ fuzz.c
@@ -534,6 +534,7 @@ static void* fuzz_threadNew(void* arg) {
         .origFileName = "[DYNAMIC]",
 
         .linux.attachedPid = 0,
+        .netbsd.attachedPid = 0,
     };
 
     /* Do not try to handle input files with socketfuzzer */
