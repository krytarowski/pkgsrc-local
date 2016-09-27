$NetBSD$

--- src/Method.cxx.orig	2016-09-27 02:19:15.867016360 +0000
+++ src/Method.cxx
@@ -515,8 +515,6 @@ long Cint::G__MethodInfo::FilePosition()
       return((long)ifunc->pentry[index]->pos.__pos);
 #elif defined(G__NONSCALARFPOS_QNX)      
       return((long)ifunc->pentry[index]->pos._Off);
-#elif defined(__NetBSD__)
-      return((long)ifunc->pentry[index]->pos._pos);
 #else
       return((long)ifunc->pentry[index]->pos);
 #endif
