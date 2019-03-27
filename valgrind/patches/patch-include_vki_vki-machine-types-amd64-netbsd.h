$NetBSD$

--- include/vki/vki-machine-types-amd64-netbsd.h.orig	2019-03-27 08:51:35.158301294 +0000
+++ include/vki/vki-machine-types-amd64-netbsd.h
@@ -0,0 +1,84 @@
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
+//----------------------------------------------------------------------
+// From sys/arch/amd64/include/types.h
+//----------------------------------------------------------------------
+
+typedef unsigned long   vki_paddr_t;
+typedef unsigned long   vki_psize_t;
+typedef unsigned long   vki_vaddr_t;
+typedef unsigned long   vki_vsize_t;
+typedef long int        vki_register_t;
+typedef int             vki_register32_t;
+
+typedef long int        vki___register_t;
+typedef unsigned char   vki___cpu_simple_lock_nv_t;
+
+//----------------------------------------------------------------------
+// From sys/arch/amd64/include/ansi.h
+//----------------------------------------------------------------------
+
+typedef unsigned int    vki_bsd_clock_t;
+typedef long            vki_bsd_ptrdiff_t;
+typedef unsigned long   vki_bsd_size_t;
+typedef long            vki_bsd_ssize_t;
+typedef vki_int64_t     vki_bsd_time_t;
+typedef int             vki_bsd_clockid_t;
+typedef int             vki_bsd_timer_t;
+typedef int             vki_bsd_suseconds_t;
+typedef unsigned int    vki_bsd_useconds_t;
+typedef int             vki_bsd_wchar_t;
+typedef int             vki_bsd_wint_t;
+
+#endif // __VKI_MACHINE_TYPES_AMD64_NETBSD_H
+
+/*--------------------------------------------------------------------*/
+/*--- end                                                          ---*/
+/*--------------------------------------------------------------------*/
