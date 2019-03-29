$NetBSD$

--- coregrind/m_ume/main.c.orig	2018-05-05 07:42:22.000000000 +0000
+++ coregrind/m_ume/main.c
@@ -51,7 +51,7 @@ typedef struct {
 } ExeHandler;
 
 static ExeHandler exe_handlers[] = {
-#  if defined(VGO_linux) || defined(VGO_solaris)
+#  if defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
    { VG_(match_ELF),    VG_(load_ELF) },
 #  elif defined(VGO_darwin)
    { VG_(match_macho),  VG_(load_macho) },
