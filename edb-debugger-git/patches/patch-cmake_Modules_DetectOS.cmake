$NetBSD$

--- cmake/Modules/DetectOS.cmake.orig	2019-06-13 22:49:27.000000000 +0000
+++ cmake/Modules/DetectOS.cmake
@@ -5,6 +5,8 @@ elseif (CMAKE_SYSTEM_NAME MATCHES "Linux
 	set(TARGET_PLATFORM_LINUX 1)
 elseif (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
 	set(TARGET_PLATFORM_FREEBSD 1)
+elseif (CMAKE_SYSTEM_NAME MATCHES "NetBSD")
+	set(TARGET_PLATFORM_NETBSD 1)
 else()
 	message(FATAL_ERROR "Unsupported OS: ${CMAKE_SYSTEM_NAME}")
 endif ()
