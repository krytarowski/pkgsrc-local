$NetBSD$

--- include/vki/vki-netbsd.h.orig	2019-03-27 08:27:00.547921039 +0000
+++ include/vki/vki-netbsd.h
@@ -0,0 +1,72 @@
+
+/*--------------------------------------------------------------------*/
+/*--- NetBSD-specific kernel interface.               vki-netbsd.h ---*/
+/*--------------------------------------------------------------------*/
+
+/*
+   This file is part of Valgrind, a dynamic binary instrumentation
+   framework.
+
+   Copyright (C) 2011-2017 Petr Pavlu
+      setup@dagobah.cz
+
+   This program is free software; you can redistribute it and/or
+   modify it under the terms of the GNU General Public License as
+   published by the Free Software Foundation; either version 2 of the
+   License, or (at your option) any later version.
+
+   This program is distributed in the hope that it will be useful, but
+   WITHOUT ANY WARRANTY; without even the implied warranty of
+   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
+   General Public License for more details.
+
+   You should have received a copy of the GNU General Public License
+   along with this program; if not, write to the Free Software
+   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
+   02111-1307, USA.
+
+   The GNU General Public License is contained in the file COPYING.
+*/
+
+/* Copyright 2013-2017, Ivo Raisr <ivosh@ivosh.net> */
+
+/* Copyright 2013, OmniTI Computer Consulting, Inc. All rights reserved. */
+
+/* The purpose of this file is described in vki-linux.h.
+
+   To avoid any copyright issues, vki-netbsd.h follows the same approach as
+   vki-darwin.h (not copying anything from kernel header files but instead
+   just including them).
+ */
+
+#ifndef __VKI_NETBSD_H
+#define __VKI_NETBSD_H
+
+//----------------------------------------------------------------------
+// Arch-specific POSIX types
+//----------------------------------------------------------------------
+
+#if defined(VGA_amd64)                                                                                                                                     
+#  include "vki-machine-types-amd64-netbsd.h"
+#else
+#  error Unknown platform
+#endif
+
+#include <sys/param.h>
+#include <sys/types.h>
+
+//----------------------------------------------------------------------
+// Now the rest of the arch-specific stuff
+//----------------------------------------------------------------------
+
+#if defined(VGA_amd64)
+#  include "vki-amd64-netbsd.h"
+#else
+#  error Unknown platform
+#endif
+
+#endif // __VKI_NETBSD_H
+
+/*--------------------------------------------------------------------*/
+/*--- end                                                          ---*/
+/*--------------------------------------------------------------------*/
