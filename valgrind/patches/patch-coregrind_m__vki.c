$NetBSD$

--- coregrind/m_vki.c.orig	2018-05-05 07:42:22.000000000 +0000
+++ coregrind/m_vki.c
@@ -77,7 +77,7 @@ void VG_(vki_do_initial_consistency_chec
 
    /* --- Platform-specific checks on signal sets --- */
 
-#  if defined(VGO_linux) || defined(VGO_solaris)
+#  if defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
    /* nothing to check */
 #  elif defined(VGP_x86_darwin) || defined(VGP_amd64_darwin)
    vg_assert(_VKI_NSIG == NSIG);
@@ -91,7 +91,7 @@ void VG_(vki_do_initial_consistency_chec
 
    /* --- Platform-specific checks on sigactions --- */
 
-#  if defined(VGO_linux)
+#  if defined(VGO_linux) || defined(VGO_netbsd)
    /* the toK- and fromK- forms are identical */
    vg_assert( sizeof(vki_sigaction_toK_t) 
               == sizeof(vki_sigaction_fromK_t) );
