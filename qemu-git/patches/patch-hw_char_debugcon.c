$NetBSD$

--- hw/char/debugcon.c.orig	2018-03-05 13:54:07.000000000 +0000
+++ hw/char/debugcon.c
@@ -25,6 +25,7 @@
  */
 
 #include "qemu/osdep.h"
+#include "qemu/log.h"
 #include "qapi/error.h"
 #include "hw/hw.h"
 #include "chardev/char-fe.h"
@@ -62,6 +63,8 @@ static void debugcon_ioport_write(void *
     /* XXX this blocks entire thread. Rewrite to use
      * qemu_chr_fe_write and background I/O callbacks */
     qemu_chr_fe_write_all(&s->chr, &ch, 1);
+
+    qemu_log_mask(CPU_LOG_INT, "%c", ch);
 }
 
 
