$NetBSD$

--- include/llvm/ADT/Triple.h.orig	2017-08-10 16:47:06.818587692 +0000
+++ include/llvm/ADT/Triple.h
@@ -91,6 +91,7 @@ public:
     kalimba,        // Kalimba: generic kalimba
     shave,          // SHAVE: Movidius vector VLIW processors
     lanai,          // Lanai: Lanai 32-bit
+    vax,            // DEC VAX
     wasm32,         // WebAssembly with 32-bit pointers
     wasm64,         // WebAssembly with 64-bit pointers
     renderscript32, // 32-bit RenderScript
