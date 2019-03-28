$NetBSD$

--- coregrind/pub_core_initimg.h.orig	2018-05-05 07:42:22.000000000 +0000
+++ coregrind/pub_core_initimg.h
@@ -68,7 +68,7 @@ void VG_(ii_finalise_image)( IIFinaliseI
 
 /* ------------------------- Linux ------------------------- */
 
-#if defined(VGO_linux)
+#if defined(VGO_linux) || defined(VGO_netbsd)
 
 struct _IICreateImageInfo {
    /* ------ Mandatory fields ------ */
