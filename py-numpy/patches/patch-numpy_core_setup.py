$NetBSD$

--- numpy/core/setup.py.orig	2016-07-24 11:35:48.946656208 +0000
+++ numpy/core/setup.py
@@ -272,6 +272,10 @@ def check_types(config_cmd, ext, build_d
     if res:
         private_defines.append(('HAVE_ENDIAN_H', 1))
         public_defines.append(('NPY_HAVE_ENDIAN_H', 1))
+    res = config_cmd.check_header("sys/endian.h")
+    if res:
+        private_defines.append(('HAVE_SYS_ENDIAN_H', 1))
+        public_defines.append(('NPY_HAVE_SYS_ENDIAN_H', 1))
 
     # Check basic types sizes
     for type in ('short', 'int', 'long'):
