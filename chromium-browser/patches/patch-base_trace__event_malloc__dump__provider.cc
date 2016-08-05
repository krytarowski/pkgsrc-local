$NetBSD$

--- base/trace_event/malloc_dump_provider.cc.orig	2016-08-05 17:13:37.000000000 +0000
+++ base/trace_event/malloc_dump_provider.cc
@@ -26,7 +26,7 @@
 namespace base {
 namespace trace_event {
 
-#if BUILDFLAG(USE_EXPERIMENTAL_ALLOCATOR_SHIM)
+#if 0 // BUILDFLAG(USE_EXPERIMENTAL_ALLOCATOR_SHIM)
 namespace {
 
 using allocator::AllocatorDispatch;
@@ -200,7 +200,7 @@ bool MallocDumpProvider::OnMemoryDump(co
 }
 
 void MallocDumpProvider::OnHeapProfilingEnabled(bool enabled) {
-#if BUILDFLAG(USE_EXPERIMENTAL_ALLOCATOR_SHIM)
+#if 0 // BUILDFLAG(USE_EXPERIMENTAL_ALLOCATOR_SHIM)
   if (enabled) {
     {
       AutoLock lock(allocation_register_lock_);
