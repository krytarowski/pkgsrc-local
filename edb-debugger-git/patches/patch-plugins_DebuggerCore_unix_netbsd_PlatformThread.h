$NetBSD$

--- plugins/DebuggerCore/unix/netbsd/PlatformThread.h.orig	2019-06-14 00:22:08.252931185 +0000
+++ plugins/DebuggerCore/unix/netbsd/PlatformThread.h
@@ -0,0 +1,68 @@
+/*
+Copyright (C) 2018 - 2018 Evan Teran
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
+#ifndef PLATFORM_THREAD_20181225_H_
+#define PLATFORM_THREAD_20181225_H_
+
+#include "IThread.h"
+#include "IBreakpoint.h"
+#include <memory>
+#include <QCoreApplication>
+
+class IProcess;
+
+namespace DebuggerCorePlugin {
+
+class DebuggerCore;
+class PlatformState;
+
+class PlatformThread : public IThread {
+	Q_DECLARE_TR_FUNCTIONS(PlatformThread)
+	friend class DebuggerCore;
+	friend class PlatformProcess;
+
+public:
+	edb::tid_t tid() const override;
+	QString name() const override;
+	int priority() const override;
+	edb::address_t instruction_pointer() const override;
+	QString runState() const override;
+
+public:
+	void get_state(State *state) override;
+	void set_state(const State &state) override;
+
+public:
+	Status step() override;
+	Status step(edb::EVENT_STATUS status) override;
+	Status resume() override;
+	Status resume(edb::EVENT_STATUS status) override;
+
+public:
+	bool isPaused() const override;
+
+private:
+	DebuggerCore *const       core_;
+	std::shared_ptr<IProcess> process_;
+	edb::tid_t                tid_;
+	int                       status_ = 0;
+};
+
+}
+
+#endif
