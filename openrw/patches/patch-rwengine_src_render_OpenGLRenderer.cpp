$NetBSD$

--- rwengine/src/render/OpenGLRenderer.cpp.orig	2016-08-11 22:19:42.000000000 +0000
+++ rwengine/src/render/OpenGLRenderer.cpp
@@ -5,6 +5,8 @@
 #include <sstream>
 #include <iostream>
 
+#include <stdio.h>
+
 GLuint compileShader(GLenum type, const char *source)
 {
 	GLuint shader = glCreateShader(type);
@@ -15,7 +17,19 @@ GLuint compileShader(GLenum type, const 
 	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
 
 	if( status != GL_TRUE ) {
+		GLint maxLength = 0;
+		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
+
+		// The maxLength includes the NULL character
+		char errorLog[maxLength+1];
+		glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog);
+
+		// Provide the infolog in whatever manor you deem best.
+		// Exit with failure.
+		glDeleteShader(shader); // Don't leak the shader.
+
 		std::cerr << "[OGL] Shader Compilation Failed" << std::endl;
+		fprintf(stderr, "len=%d string='%s'\n", (int) maxLength, errorLog);
 	}
 
 	GLint len;
