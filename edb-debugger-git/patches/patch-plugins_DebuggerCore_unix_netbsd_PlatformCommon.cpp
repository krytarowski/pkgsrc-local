$NetBSD$

--- plugins/DebuggerCore/unix/netbsd/PlatformCommon.cpp.orig	2019-06-16 23:21:29.801449232 +0000
+++ plugins/DebuggerCore/unix/netbsd/PlatformCommon.cpp
@@ -0,0 +1,28 @@
+/*
+Copyright (C) 2015 - 2015 Evan Teran
+                          evan.teran@gmail.com
+
+This program is free software: you can redistribute it and/or modify
+it under the terms of the GNU General Public License as published by
+the Free Software Foundation, either version 2 of the License, or
+(at your option) any later version.
+
+This program is distributed in the hope that it will be useful,
+but WITHOUT ANY WARRANTY; without even the implied warranty of
+MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+GNU General Public License for more details.
+
+You should have received a copy of the GNU General Public License
+along with this program.  If not, see <http://www.gnu.org/licenses/>.
+*/
+
+#include "PlatformCommon.h"
+#include <sys/wait.h>
+#include <iostream>
+#include <fstream>
+
+namespace DebuggerCorePlugin {
+
+
+
+}
