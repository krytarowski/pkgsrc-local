$NetBSD$

--- plugins/DebuggerCore/unix/netbsd/FeatureDetect.cpp.orig	2019-06-15 15:00:37.919358349 +0000
+++ plugins/DebuggerCore/unix/netbsd/FeatureDetect.cpp
@@ -0,0 +1,85 @@
+/*
+Copyright (C) 2016 - 2016 Evan Teran
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
+#include "FeatureDetect.h"
+#include "version.h"
+
+#include <sys/types.h>
+#include <sys/ptrace.h>
+#include <sys/wait.h>
+
+#include <iostream>
+#include <iomanip>
+#include <string>
+#include <fcntl.h>
+#include <unistd.h>
+#include <signal.h>
+
+namespace DebuggerCorePlugin {
+namespace feature {
+namespace {
+
+// Custom class to work with files, since various wrappers
+// appear to be unreliable to check whether writes succeeded
+class File {
+	int fd;
+	bool success;
+
+public:
+    explicit File(const std::string &filename) {
+		fd = ::open(filename.c_str(), O_RDWR);
+		success = fd != -1;
+	}
+
+	ssize_t write(const void *buf, size_t count) {
+		const ssize_t result = ::write(fd, buf, count);
+		success = result != -1;
+		return result;
+	}
+
+	ssize_t read(void *buf, size_t count) {
+		const ssize_t result = ::read(fd, buf, count);
+		success = result != -1;
+		return result;
+	}
+
+	off_t seekp(size_t offset) {
+		const off_t result = ::lseek(fd, offset, SEEK_SET);
+		success = result != -1;
+		return result;
+	}
+
+	~File() {
+		close(fd);
+	}
+
+	explicit operator bool() {
+		return success;
+	}
+};
+
+void kill_child(int pid) {
+	if (kill(pid, SIGKILL) == -1) {
+		perror("failed to kill child");
+	}
+}
+
+}
+
+}
+}
