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
@@ -73,18 +73,26 @@ VG_(pre_exec_check)(const HChar* exe_nam
    SizeT bufsz = sizeof buf, fsz;
    Bool is_setuid = False;
 
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    // Check it's readable
    res = VG_(open)(exe_name, VKI_O_RDONLY, 0);
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    if (sr_isError(res)) {
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       return res;
    }
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    fd = sr_Res(res);
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
 
    // Check we have execute permissions
    ret = VG_(check_executable)(&is_setuid, exe_name, allow_setuid);
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    if (0 != ret) {
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       VG_(close)(fd);
       if (is_setuid && !VG_(clo_xml)) {
+         VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
          VG_(message)(Vg_UserMsg, "\n");
          VG_(message)(Vg_UserMsg,
                       "Warning: Can't execute setuid/setgid/setcap executable: %s\n",
@@ -96,36 +104,55 @@ VG_(pre_exec_check)(const HChar* exe_nam
       return VG_(mk_SysRes_Error)(ret);
    }
 
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
+
    fsz = (SizeT)VG_(fsize)(fd);
-   if (fsz < bufsz)
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
+   if (fsz < bufsz) {
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       bufsz = fsz;
+   }
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
 
    res = VG_(pread)(fd, buf, bufsz, 0);
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    if (sr_isError(res) || sr_Res(res) != bufsz) {
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       VG_(close)(fd);
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       return VG_(mk_SysRes_Error)(VKI_EACCES);
    }
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    bufsz = sr_Res(res);
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
 
    // Look for a matching executable format
    for (i = 0; i < EXE_HANDLER_COUNT; i++) {
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       if ((*exe_handlers[i].match_fn)(buf, bufsz)) {
+         VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
          res = VG_(mk_SysRes_Success)(i);
          break;
       }
    }
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    if (i == EXE_HANDLER_COUNT) {
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       // Rejected by all executable format handlers.
       res = VG_(mk_SysRes_Error)(VKI_ENOEXEC);
    }
 
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    // Write the 'out_fd' param if necessary, or close the file.
    if (!sr_isError(res) && out_fd) {
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       *out_fd = fd; 
    } else { 
+      VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
       VG_(close)(fd);
    }
 
+   VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    return res;
 }
 
@@ -140,16 +167,24 @@ Int VG_(do_exec_inner)(const HChar* exe,
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
@@ -208,10 +243,13 @@ static Int do_exec_shell_followup(Int re
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
 
@@ -220,16 +258,22 @@ static Int do_exec_shell_followup(Int re
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
@@ -237,38 +281,51 @@ static Int do_exec_shell_followup(Int re
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
 
@@ -282,14 +339,19 @@ Int VG_(do_exec)(const HChar* exe_name, 
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
 
