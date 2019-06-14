$NetBSD$

--- plugins/DebuggerCore/unix/netbsd/DialogMemoryAccess.cpp.orig	2019-06-14 00:46:21.718757736 +0000
+++ plugins/DebuggerCore/unix/netbsd/DialogMemoryAccess.cpp
@@ -0,0 +1,33 @@
+/*
+Copyright (C) 2006 - 2015 Evan Teran
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
+#include "DialogMemoryAccess.h"
+
+namespace DebuggerCorePlugin {
+
+DialogMemoryAccess::DialogMemoryAccess(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)  {
+	ui.setupUi(this);
+	adjustSize();
+	setFixedSize(width(), height());
+}
+
+bool DialogMemoryAccess::warnNextTime() const {
+	return !ui.checkNeverShowAgain->isChecked();
+}
+
+}
