$NetBSD$

--- coregrind/launcher-linux.c.orig	2018-07-13 08:52:05.000000000 +0000
+++ coregrind/launcher-linux.c
@@ -276,6 +276,13 @@ static const char *select_platform(const
                platform = "amd64-solaris";
             }
             else
+#           elif defined(VGO_netbsd)
+            if (header.ehdr64.e_machine == EM_X86_64 &&
+                (header.ehdr64.e_ident[EI_OSABI] == ELFOSABI_SYSV ||
+                 header.ehdr64.e_ident[EI_OSABI] == ELFOSABI_NETBSD)) {
+               platform = "amd64-netbsd";
+            }
+            else
 #           endif
             if (header.ehdr64.e_machine == EM_X86_64 &&
                 (header.ehdr64.e_ident[EI_OSABI] == ELFOSABI_SYSV ||
@@ -397,6 +404,9 @@ int main(int argc, char** argv, char** e
    if ((0==strcmp(VG_PLATFORM,"x86-solaris")) ||
        (0==strcmp(VG_PLATFORM,"amd64-solaris")))
       default_platform = SOLARIS_LAUNCHER_DEFAULT_PLATFORM;
+#  elif defined(VGO_netbsd)
+   if ((0==strcmp(VG_PLATFORM,"amd64-netbsd")))
+      default_platform = NETBSD_LAUNCHER_DEFAULT_PLATFORM;
 #  else
 #    error Unknown OS
 #  endif
@@ -422,6 +432,18 @@ int main(int argc, char** argv, char** e
    /* Figure out the name of this executable (viz, the launcher), so
       we can tell stage2.  stage2 will use the name for recursive
       invocations of valgrind on child processes. */
+#if defined(VGO_netbsd)
+    static const int name[] = {
+        CTL_KERN, KERN_PROC_ARGS, -1, KERN_PROC_PATHNAME,
+    };
+    char launcher_name[MAXPATHLEN];
+    size_t len;
+
+    len = sizeof(path);
+    if (sysctl(name, __arraycount(name), launcher_name, &len, NULL, 0) == -1) {
+      abort();
+    }
+#else
 #  if defined(VGO_linux)
    linkname = "/proc/self/exe";
 #  elif defined(VGO_solaris)
@@ -458,7 +480,7 @@ int main(int argc, char** argv, char** e
       launcher_name = buf;
       break;
    }
-
+#endif
    /* tediously augment the env: VALGRIND_LAUNCHER=launcher_name */
    new_line = malloc(strlen(VALGRIND_LAUNCHER) + 1 
                      + strlen(launcher_name) + 1);
