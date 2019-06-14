$NetBSD$

--- plugins/DebuggerCore/unix/netbsd/PlatformRegion.h.orig	2019-06-14 00:28:36.262155058 +0000
+++ plugins/DebuggerCore/unix/netbsd/PlatformRegion.h
@@ -0,0 +1,67 @@
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
+#ifndef PLATFORM_REGION_20120330_H_
+#define PLATFORM_REGION_20120330_H_
+
+#include "IRegion.h"
+#include <QString>
+#include <QCoreApplication>
+
+namespace DebuggerCorePlugin {
+
+class PlatformRegion : public IRegion {
+	Q_DECLARE_TR_FUNCTIONS(PlatformRegion)
+
+public:
+	PlatformRegion(edb::address_t start, edb::address_t end, edb::address_t base, const QString &name, permissions_t permissions);
+	~PlatformRegion() override = default;
+
+public:
+	IRegion *clone() const override;
+
+public:
+	bool accessible() const override;
+	bool readable() const override;
+	bool writable() const override;
+	bool executable() const override;
+	size_t size() const override;
+
+public:
+	void set_permissions(bool read, bool write, bool execute) override;
+	void set_start(edb::address_t address) override;
+	void set_end(edb::address_t address) override;
+
+public:
+	edb::address_t start() const override;
+	edb::address_t end() const override;
+	edb::address_t base() const override;
+	QString name() const override;
+	permissions_t permissions() const override;
+
+private:
+	edb::address_t start_;
+	edb::address_t end_;
+	edb::address_t base_;
+	QString        name_;
+	permissions_t  permissions_;
+};
+
+}
+
+#endif
