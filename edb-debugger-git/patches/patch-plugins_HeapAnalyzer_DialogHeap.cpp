$NetBSD$

--- plugins/HeapAnalyzer/DialogHeap.cpp.orig	2019-06-13 22:49:27.000000000 +0000
+++ plugins/HeapAnalyzer/DialogHeap.cpp
@@ -360,7 +360,7 @@ void DialogHeap::collectBlocks(edb::addr
 		const int min_string_length = edb::v1::config().min_string_length;
 
 		if(start_address != 0 && end_address != 0) {
-	#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD) || defined(Q_OS_OPENBSD)
+	#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD) || defined(Q_OS_OPENBSD) || defined(Q_OS_NETBSD)
 			malloc_chunk<Addr> currentChunk;
 			malloc_chunk<Addr> nextChunk;
 			edb::address_t currentChunkAddress = start_address;
@@ -514,7 +514,7 @@ void DialogHeap::do_find() {
 		QString ldName;
 
 		get_library_names(&libcName, &ldName);
-	#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD) || defined(Q_OS_OPENBSD)
+	#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD) || defined(Q_OS_OPENBSD) || defined(Q_OS_NETBSD)
 
 		if(std::shared_ptr<Symbol> s = edb::v1::symbol_manager().find(libcName + "::__curbrk")) {
 			end_address = s->address;
