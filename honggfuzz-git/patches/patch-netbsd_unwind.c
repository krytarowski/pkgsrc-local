$NetBSD$

--- netbsd/unwind.c.orig	2018-08-10 00:06:20.432335085 +0000
+++ netbsd/unwind.c
@@ -0,0 +1,81 @@
+/*
+ *
+ * honggfuzz - architecture dependent code (NETBSD/UNWIND)
+ * -----------------------------------------
+ *
+ * Author: Robert Swiecki <swiecki@google.com>
+ *
+ * Copyright 2010-2018 by Google Inc. All Rights Reserved.
+ *
+ * Licensed under the Apache License, Version 2.0 (the "License"); you may
+ * not use this file except in compliance with the License. You may obtain
+ * a copy of the License at
+ *
+ * http://www.apache.org/licenses/LICENSE-2.0
+ *
+ * Unless required by applicable law or agreed to in writing, software
+ * distributed under the License is distributed on an "AS IS" BASIS,
+ * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
+ * implied. See the License for the specific language governing
+ * permissions and limitations under the License.
+ *
+ */
+
+#include "unwind.h"
+
+#include <endian.h>
+#include <stdio.h>
+#include <stdlib.h>
+#include <string.h>
+#include <libunwind.h>
+
+#include "honggfuzz.h"
+#include "libhfcommon/common.h"
+#include "libhfcommon/log.h"
+
+/*
+ * WARNING: Ensure that _UPT-info structs are not shared between threads
+ * http://www.nongnu.org/libunwind/man/libunwind-ptrace(3).html
+ */
+
+typedef struct {
+    unsigned long start;
+    unsigned long end;
+    char perms[6];
+    unsigned long offset;
+    char dev[8];
+    unsigned long inode;
+    char name[PATH_MAX];
+} procMap_t;
+
+size_t arch_unwindStack(pid_t pid __unused, funcs_t* funcs __unused) {
+    return 0;
+}
+
+/*
+ * Nested loop not most efficient approach, although it's assumed that list is
+ * usually target specific and thus small.
+ */
+char* arch_btContainsSymbol(
+    size_t symbolsListSz, char** symbolsList, size_t num_frames, funcs_t* funcs) {
+    for (size_t frame = 0; frame < num_frames; frame++) {
+        size_t len = strlen(funcs[frame].func);
+
+        /* Try only for frames that have symbol name from backtrace */
+        if (strlen(funcs[frame].func) > 0) {
+            for (size_t i = 0; i < symbolsListSz; i++) {
+                /* Wildcard symbol string special case */
+                char* wOff = strchr(symbolsList[i], '*');
+                if (wOff) {
+                    /* Length always > 3 as checked at input file parsing step */
+                    len = wOff - symbolsList[i] - 1;
+                }
+
+                if (strncmp(funcs[frame].func, symbolsList[i], len) == 0) {
+                    return funcs[frame].func;
+                }
+            }
+        }
+    }
+    return NULL;
+}
