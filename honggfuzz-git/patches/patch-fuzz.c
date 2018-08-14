$NetBSD$

--- fuzz.c.orig	2018-08-14 05:00:24.872529478 +0000
+++ fuzz.c
@@ -178,7 +178,8 @@ static void fuzz_setDynamicMainState(run
     }
 }
 
-static void fuzz_perfFeedback(run_t* run) {
+static void fuzz_perfFeedback(run_t* run HF_ATTR_UNUSED) {
+#if defined(_HF_ARCH_LINUX)
     if (run->global->feedback.skipFeedbackOnTimeout && run->tmOutSignaled) {
         return;
     }
@@ -236,6 +237,7 @@ static void fuzz_perfFeedback(run_t* run
             fuzz_notifySocketFuzzerNewCov(run->global);
         }
     }
+#endif
 }
 
 static void fuzz_sanCovFeedback(run_t* run) {
@@ -534,6 +536,7 @@ static void* fuzz_threadNew(void* arg) {
         .origFileName = "[DYNAMIC]",
 
         .linux.attachedPid = 0,
+        .netbsd.attachedPid = 0,
     };
 
     /* Do not try to handle input files with socketfuzzer */
