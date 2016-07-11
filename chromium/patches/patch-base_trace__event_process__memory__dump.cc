$NetBSD$

--- base/trace_event/process_memory_dump.cc.orig	2016-06-16 19:02:01.000000000 +0000
+++ base/trace_event/process_memory_dump.cc
@@ -121,7 +121,7 @@ size_t ProcessMemoryDump::CountResidentB
     // HANDLE_EINTR tries for 100 times. So following the same pattern.
     do {
       result =
-          mincore(reinterpret_cast<void*>(chunk_start), chunk_size, vec.get());
+          mincore(reinterpret_cast<void*>(chunk_start), chunk_size, reinterpret_cast<char*>(vec.get()));
     } while (result == -1 && errno == EAGAIN && error_counter++ < 100);
     failure = !!result;
 
