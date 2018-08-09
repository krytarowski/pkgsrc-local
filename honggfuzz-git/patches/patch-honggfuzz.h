$NetBSD$

--- honggfuzz.h.orig	2018-08-09 01:52:21.909145071 +0000
+++ honggfuzz.h
@@ -298,6 +298,27 @@ typedef struct {
         bool useClone;
         sigset_t waitSigSet;
     } linux;
+    /* For the NetBSD code */
+    struct {
+        int exeFd;
+        hwcnt_t hwCnts;
+        uint64_t dynamicCutOffAddr;
+        bool disableRandomization;
+        void* ignoreAddr;
+        size_t numMajorFrames;
+        pid_t pid;
+        const char* pidFile;
+        char pidCmd[55];
+        const char* symsBlFile;
+        char** symsBl;
+        size_t symsBlCnt;
+        const char* symsWlFile;
+        char** symsWl;
+        size_t symsWlCnt;
+        uintptr_t cloneFlags;
+        bool kernelOnly;
+        sigset_t waitSigSet;
+    } netbsd;
 } honggfuzz_t;
 
 typedef struct {
