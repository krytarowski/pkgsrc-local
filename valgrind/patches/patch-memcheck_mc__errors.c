$NetBSD$

--- memcheck/mc_errors.c.orig	2018-05-05 07:42:22.000000000 +0000
+++ memcheck/mc_errors.c
@@ -416,6 +416,8 @@ void MC_(pp_Error) ( const Error* err )
    const Bool xml  = VG_(clo_xml); /* a shorthand */
    MC_Error* extra = VG_(get_error_extra)(err);
 
+   VG_(debugLog)(2, "KR", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
+
    switch (VG_(get_error_kind)(err)) {
       case Err_CoreMem:
          /* What the hell *is* a CoreMemError? jrs 2005-May-18 */
@@ -711,6 +713,7 @@ void MC_(pp_Error) ( const Error* err )
                      VG_(get_error_kind)(err));
          VG_(tool_panic)("unknown error code in mc_pp_Error)");
    }
+   VG_(debugLog)(2, "KR", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
 }
 
 /*------------------------------------------------------------*/
@@ -740,6 +743,8 @@ void MC_(record_address_error) ( ThreadI
    MC_Error extra;
    Bool     just_below_esp;
 
+VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
+
    if (MC_(in_ignored_range)(a)) 
       return;
 
@@ -764,7 +769,9 @@ void MC_(record_address_error) ( ThreadI
    extra.Err.Addr.szB       = szB;
    extra.Err.Addr.maybe_gcc = just_below_esp;
    extra.Err.Addr.ai.tag    = Addr_Undescribed;
+VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
    VG_(maybe_record_error)( tid, Err_Addr, a, /*s*/NULL, &extra );
+VG_(debugLog)(2, "initimg", "%s() %s:%d\n", __func__, __FILE__, __LINE__);
 }
 
 void MC_(record_value_error) ( ThreadId tid, Int szB, UInt otag )
