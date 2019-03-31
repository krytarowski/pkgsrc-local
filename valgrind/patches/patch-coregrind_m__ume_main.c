$NetBSD$

--- coregrind/m_ume/main.c.orig	2018-05-05 07:42:22.000000000 +0000
+++ coregrind/m_ume/main.c
@@ -51,7 +51,7 @@ typedef struct {
 } ExeHandler;
 
 static ExeHandler exe_handlers[] = {
-#  if defined(VGO_linux) || defined(VGO_solaris)
+#  if defined(VGO_linux) || defined(VGO_solaris) || defined(VGO_netbsd)
    { VG_(match_ELF),    VG_(load_ELF) },
 #  elif defined(VGO_darwin)
    { VG_(match_macho),  VG_(load_macho) },
@@ -140,16 +140,24 @@ Int VG_(do_exec_inner)(const HChar* exe,
    Int fd;
    Int ret;
 
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    res = VG_(pre_exec_check)(exe, &fd, False/*allow_setuid*/);
-   if (sr_isError(res))
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
+   if (sr_isError(res)) {
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       return sr_Err(res);
+   }
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
 
    vg_assert2(sr_Res(res) >= 0 && sr_Res(res) < EXE_HANDLER_COUNT, 
               "invalid VG_(pre_exec_check) result");
 
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    ret = (*exe_handlers[sr_Res(res)].load_fn)(fd, exe, info);
 
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    VG_(close)(fd);
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
 
    return ret;
 }
@@ -208,10 +216,13 @@ static Int do_exec_shell_followup(Int re
    const HChar*  default_interp_name = "/bin/sh";
 #  endif
 
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
+
    SysRes res;
    struct vg_stat st;
 
    if (VKI_ENOEXEC == ret) {
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       // It was an executable file, but in an unacceptable format.  Probably
       // is a shell script lacking the "#!" prefix;  try to execute it so.
 
@@ -220,16 +231,22 @@ static Int do_exec_shell_followup(Int re
          VG_(fmsg)("%s: cannot execute binary file\n", exe_name);
          VG_(exit)(126);      // 126 == NOEXEC
       }
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
 
       // Looks like a script.  Run it with /bin/sh.  This includes
       // zero-length files.
       VG_(free)(info->interp_name);
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       info->interp_name = VG_(strdup)("ume.desf.1", default_interp_name);
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       VG_(free)(info->interp_args); info->interp_args = NULL;
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       if (info->argv && info->argv[0] != NULL)
          info->argv[0] = exe_name;
 
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       ret = VG_(do_exec_inner)(info->interp_name, info);
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
 
       if (0 != ret) {
          // Something went wrong with executing the default interpreter
@@ -237,38 +254,51 @@ static Int do_exec_shell_followup(Int re
                      exe_name, info->interp_name, VG_(strerror)(ret));
          VG_(exit)(126);      // 126 == NOEXEC
       }
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
 
    } else if (0 != ret) {
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       // Something else went wrong.  Try to make the error more specific,
       // and then print a message and abort.
       Int exit_code = 126;    // 126 == NOEXEC (bash)
 
       res = VG_(stat)(exe_name, &st);
 
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       // Does the file exist ?
       if (sr_isError(res) && sr_Err(res) == VKI_ENOENT) {
+         VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
          VG_(fmsg)("%s: %s\n", exe_name, VG_(strerror)(ret));
          exit_code = 127;     // 127 == NOTFOUND (bash)
-
+         VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       // Was it a directory?
       } else if (!sr_isError(res) && VKI_S_ISDIR(st.mode)) {
+         VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
          VG_(fmsg)("%s: is a directory\n", exe_name);
+         VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       
       // Was it not executable?
       } else if (0 != VG_(check_executable)(NULL, exe_name, 
                                             False/*allow_setuid*/)) {
+         VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
          VG_(fmsg)("%s: %s\n", exe_name, VG_(strerror)(ret));
-
+         VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       // Did it start with "#!"?  If so, it must have been a bad interpreter.
       } else if (is_hash_bang_file(exe_name)) {
+         VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
          VG_(fmsg)("%s: bad interpreter: %s\n", exe_name, VG_(strerror)(ret));
-
+         VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       // Otherwise it was something else.
       } else {
+         VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
          VG_(fmsg)("%s: %s\n", exe_name, VG_(strerror)(ret));
+         VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       }
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       VG_(exit)(exit_code);
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    }
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    return ret;
 }
 
@@ -282,14 +312,19 @@ Int VG_(do_exec)(const HChar* exe_name, 
 {
    Int ret;
 
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    VG_(free)(info->interp_name); info->interp_name = NULL;
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    VG_(free)(info->interp_args); info->interp_args = NULL;
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
 
    ret = VG_(do_exec_inner)(exe_name, info);
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
 
    if (0 != ret) {
       ret = do_exec_shell_followup(ret, exe_name, info);
    }
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    return ret;
 }
 
