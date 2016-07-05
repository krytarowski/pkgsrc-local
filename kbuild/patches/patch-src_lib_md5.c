$NetBSD$

--- src/lib/md5.c.orig	2015-06-21 21:21:25.000000000 +0000
+++ src/lib/md5.c
@@ -144,7 +144,7 @@ void MD5Final(unsigned char digest[16], 
     MD5Transform(ctx->buf, (uint32 *) ctx->in);
     byteReverse((unsigned char *) ctx->buf, 4);
     memcpy(digest, ctx->buf, 16);
-    memset(ctx, 0, sizeof(ctx));        /* In case it's sensitive */
+    memset(ctx, 0, sizeof(*ctx));        /* In case it's sensitive */
 }
 
 
