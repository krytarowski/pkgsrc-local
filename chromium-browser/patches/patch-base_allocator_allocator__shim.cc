$NetBSD$

--- base/allocator/allocator_shim.cc.orig	2016-06-16 19:02:01.000000000 +0000
+++ base/allocator/allocator_shim.cc
@@ -245,10 +245,10 @@ void ShimFree(void* address) {
 // Cross-checks.
 
 #if defined(MEMORY_TOOL_REPLACES_ALLOCATOR)
-#error The allocator shim should not be compiled when building for memory tools.
+//#error The allocator shim should not be compiled when building for memory tools.
 #endif
 
 #if (defined(__GNUC__) && defined(__EXCEPTIONS)) || \
     (defined(_HAS_EXCEPTIONS) && _HAS_EXCEPTIONS)
-#error This code cannot be used when exceptions are turned on.
+//#error This code cannot be used when exceptions are turned on.
 #endif
