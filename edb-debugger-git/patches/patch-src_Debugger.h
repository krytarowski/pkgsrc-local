$NetBSD$

--- src/Debugger.h.orig	2019-06-13 22:49:27.000000000 +0000
+++ src/Debugger.h
@@ -315,7 +315,7 @@ private:
 	RecentFileManager  *recent_file_manager_ = nullptr;
 	bool                stack_view_locked_   = false;
 
-#if defined(Q_OS_LINUX)
+#if defined(Q_OS_LINUX) || defined(Q_OS_NETBSD)
 	edb::address_t      debug_pointer_       { 0 };
 	bool                dynamic_info_bp_set_ = false;
 #endif
