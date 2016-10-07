$NetBSD$

--- Makefile.inc.orig	2013-01-02 11:19:33.445822000 +0000
+++ Makefile.inc
@@ -1,5 +1,6 @@
 CXXFLAGS= -Wall -pthread -O0 -g $(INCLUDE_DIRS)
 CFLAGS= -Wall -pthread -O0 -g $(INCLUDE_DIRS)
+CPPFLAGS?=
 INCLUDE_DIRS=-I./include -I../include
 
 CC=gcc
