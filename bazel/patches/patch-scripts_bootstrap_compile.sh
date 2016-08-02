$NetBSD$

--- scripts/bootstrap/compile.sh.orig	2016-07-29 08:22:16.000000000 +0000
+++ scripts/bootstrap/compile.sh
@@ -62,6 +62,16 @@ freebsd)
   GRPC_JAVA_PLUGIN=${GRPC_JAVA_PLUGIN:-third_party/grpc/protoc-gen-grpc-java-0.14.1-linux-x86_32.exe}
   ;;
 
+netbsd)
+  # JAVA_HOME must point to a Java installation.
+  JAVA_HOME="${JAVA_HOME:-/usr/local/openjdk8}"
+  # Note: the linux protoc binary works on freebsd using linux emulation.
+  # We choose the 32-bit version for maximum compatiblity since 64-bit
+  # linux binaries are only supported in FreeBSD-11.
+  PROTOC=${PROTOC:-third_party/protobuf/protoc-linux-x86_32.exe}
+  GRPC_JAVA_PLUGIN=${GRPC_JAVA_PLUGIN:-third_party/grpc/protoc-gen-grpc-java-0.14.1-linux-x86_32.exe}
+  ;;
+
 darwin)
   if [[ -z "$JAVA_HOME" ]]; then
     JAVA_HOME="$(/usr/libexec/java_home -v ${JAVA_VERSION}+ 2> /dev/null)" \
