$NetBSD$

--- memcheck/mc_leakcheck.c.orig	2018-05-05 07:42:22.000000000 +0000
+++ memcheck/mc_leakcheck.c
@@ -1997,7 +1997,7 @@ static MC_Mempool *find_mp_of_chunk (MC_
 void MC_(detect_memory_leaks) ( ThreadId tid, LeakCheckParams* lcp)
 {
    Int i, j;
-   
+
    tl_assert(lcp->mode != LC_Off);
 
    // Verify some assertions which are used in lc_scan_memory.
@@ -2284,4 +2284,3 @@ void MC_(who_points_at) ( Addr address, 
 /*--------------------------------------------------------------------*/
 /*--- end                                                          ---*/
 /*--------------------------------------------------------------------*/
-
