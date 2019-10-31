$NetBSD$

--- libinput/device.h.orig	2019-07-30 10:25:09.000000000 +0000
+++ libinput/device.h
@@ -20,7 +20,12 @@ along with this program.  If not, see <h
 #ifndef KWIN_LIBINPUT_DEVICE_H
 #define KWIN_LIBINPUT_DEVICE_H
 
+#if defined(__NetBSD__)
+#include <dev/wscons/wsconsio.h>
+#include <sys/ioctl.h>
+#else
 #include <libinput.h>
+#endif
 
 #include <KConfigGroup>
 
