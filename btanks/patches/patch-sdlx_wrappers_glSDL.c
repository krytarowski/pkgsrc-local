$NetBSD$

--- sdlx/wrappers/glSDL.c.orig	2008-01-09 11:39:11.000000000 +0000
+++ sdlx/wrappers/glSDL.c
@@ -11,8 +11,6 @@
 
 #ifdef HAVE_OPENGL
 
-//#define LEAK_TRACKING
-
 #define	DBG(x)		/*error messages, warnings*/
 #define	DBG2(x)		/*texture allocation*/
 #define	DBG3(x)		/*chopping/tiling*/
@@ -951,7 +949,6 @@ SDL_Surface *glSDL_SetVideoMode(int widt
 	}
 	gl_doublebuf = flags & SDL_DOUBLEBUF;
 	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, gl_doublebuf);
-	//SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, gl_doublebuf ? 1: 0);
 
 	scale = 1;
 
