$NetBSD$

--- sdlx/surface.cpp.orig	2008-12-07 19:55:34.000000000 +0000
+++ sdlx/surface.cpp
@@ -425,7 +425,7 @@ void Surface::set_color_key(Uint32 key, 
 		throw_sdl(("SDL_SetColorKey"));
 }
 
-#include "gfx/SDL_rotozoom.h"
+#include <SDL_rotozoom.h>
 
 void Surface::rotozoom(const sdlx::Surface &src, double angle, double zoom, bool smooth) {
 	if (src.isNull())
