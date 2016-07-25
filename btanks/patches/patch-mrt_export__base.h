$NetBSD$

--- mrt/export_base.h.orig	2008-01-09 11:14:14.000000000 +0000
+++ mrt/export_base.h
@@ -1,7 +1,7 @@
 #ifndef MRT_EXPORT_MACRO_H__
 #define MRT_EXPORT_MACRO_H__
 
-// Shared library support
+/* Shared library support */
 #ifdef _WINDOWS
 
 #	pragma warning(disable:4251)  /* needs to have dll-interface used by client */
