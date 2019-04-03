$NetBSD$

--- coregrind/m_initimg/initimg-linux.c.orig	2018-07-13 08:52:05.000000000 +0000
+++ coregrind/m_initimg/initimg-linux.c
@@ -641,6 +641,10 @@ Addr setup_client_stack( void*  init_sp,
          case AT_GID:
          case AT_EGID:
          case AT_CLKTCK:
+#if defined(VGO_netbsd)
+         case AT_RUID:
+         case AT_RGID:
+#endif
 #        if !defined(VGPV_arm_linux_android) \
             && !defined(VGPV_x86_linux_android) \
             && !defined(VGPV_mips32_linux_android) \
