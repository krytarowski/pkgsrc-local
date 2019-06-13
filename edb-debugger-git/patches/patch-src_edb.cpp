$NetBSD$

--- src/edb.cpp.orig	2019-06-13 22:49:27.000000000 +0000
+++ src/edb.cpp
@@ -979,7 +979,7 @@ std::shared_ptr<IRegion> primary_data_re
 //------------------------------------------------------------------------------
 std::shared_ptr<IRegion> primary_code_region() {
 
-#if defined(Q_OS_LINUX)
+#if defined(Q_OS_LINUX) || defined(Q_OS_NETBSD)
 	if(debugger_core) {
 		if(IProcess *process = debugger_core->process()) {
 			const address_t address = process->code_address();
