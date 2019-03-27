$NetBSD$

--- include/vki/vki-machine-types-amd64-netbsd.h.orig	2019-03-27 07:40:44.340511934 +0000
+++ include/vki/vki-machine-types-amd64-netbsd.h
@@ -0,0 +1,54 @@
+
+/*--------------------------------------------------------------------*/
+/*--- amd64/NetBSD-specific kernel interface: posix types.         ---*/
+/*---                                vki_posixtypes-amd64-netbsd.h ---*/
+/*--------------------------------------------------------------------*/
+
+/*
+   This file is part of Valgrind, a dynamic binary instrumentation
+   framework.
+
+   Copyright (C) 2000-2005 Julian Seward 
+      jseward@acm.org
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
+#ifndef __VKI_MACHINE_TYPES_AMD64_NETBSD_H
+#define __VKI_MACHINE_TYPES_AMD64_NETBSD_H
+
+//----------------------------------------------------------------------
+// From sys/arch/amd64/include/int_types.h
+//----------------------------------------------------------------------
+
+typedef signed char	vki_int8_t;
+typedef unsigned char	vki_uint8_t;
+typedef short		vki_int16_t;
+typedef unsigned short	vki_uint16_t;
+typedef int		vki_int32_t;
+typedef unsigned int	vki_uint32_t;
+typedef long		vki_int64_t;
+typedef unsigned long	vki_uint64_t;
+typedef unsigned long	vki_uintptr_t;
+typedef long		vki_intptr_t;
+
+#endif // __VKI_MACHINE_TYPES_AMD64_NETBSD_H
+
+/*--------------------------------------------------------------------*/
+/*--- end                                                          ---*/
+/*--------------------------------------------------------------------*/
