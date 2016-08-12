$NetBSD$

--- rwengine/src/render/OpenGLRenderer.cpp.orig	2016-08-11 22:19:42.000000000 +0000
+++ rwengine/src/render/OpenGLRenderer.cpp
@@ -15,7 +15,18 @@ GLuint compileShader(GLenum type, const 
 	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
 
 	if( status != GL_TRUE ) {
-		std::cerr << "[OGL] Shader Compilation Failed" << std::endl;
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
+		std::cerr << "[OGL] Shader Compilation Failed: " << errorLog << std::endl;
 	}
 
 	GLint len;
