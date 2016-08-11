$NetBSD$

--- rwengine/src/loaders/LoaderGXT.cpp.orig	2016-08-11 22:19:42.000000000 +0000
+++ rwengine/src/loaders/LoaderGXT.cpp
@@ -35,7 +35,11 @@ void LoaderGXT::load(GameTexts &texts, F
 
 		char* strbase = tdata+offset;
 
+#if defined(RW_NETBSD)
+		iconv(icv, (const char**)&strbase, &bytes, &uwot, &outSize);
+#else
 		iconv(icv, &strbase, &bytes, &uwot, &outSize);
+#endif
 
 		u8buff[len] = '\0';
 
