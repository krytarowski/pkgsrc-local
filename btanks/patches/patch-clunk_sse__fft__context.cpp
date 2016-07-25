$NetBSD$

--- clunk/sse_fft_context.cpp.orig	2009-08-04 21:28:34.000000000 +0000
+++ clunk/sse_fft_context.cpp
@@ -12,7 +12,7 @@ void * aligned_allocator::allocate(size_
 #ifdef _WINDOWS
 	ptr = _aligned_malloc(size, alignment);
 #else
-	ptr = memalign(alignment, size);
+	ptr = aligned_alloc(alignment, size);
 #endif
 	if (ptr == NULL)
 		throw std::bad_alloc();
