$NetBSD$

--- include/vki/vki-netbsd.h.orig	2019-03-28 13:36:58.539662750 +0000
+++ include/vki/vki-netbsd.h
@@ -0,0 +1,464 @@
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
+//#include <sys/param.h>
+//#include <sys/types.h>
+
+//----------------------------------------------------------------------
+// sys/ansi.h
+//----------------------------------------------------------------------
+
+typedef char *                  vki___caddr_t;
+typedef vki_uint32_t            vki___gid_t;
+typedef vki_uint32_t            vki___in_addr_t;
+typedef vki_uint16_t            vki___in_port_t;
+typedef vki_uint32_t            vki___mode_t;
+typedef vki_int64_t             vki___off_t;
+typedef vki_int32_t             vki___pid_t;
+typedef vki_uint8_t             vki___sa_family_t;
+typedef unsigned int            vki___socklen_t;
+typedef vki_uint32_t            vki___uid_t;
+typedef vki_uint64_t            vki___fsblkcnt_t;
+typedef vki_uint64_t            vki___fsfilcnt_t;
+
+struct vki___tag_wctrans_t;
+typedef struct vki___tag_wctrans_t *vki___wctrans_t;
+
+struct vki___tag_wctype_t;
+typedef struct vki___tag_wctype_t *vki___wctype_t;
+
+typedef union {
+        vki_int64_t __mbstateL; /* for alignment */
+        char __mbstate8[128];
+} vki___mbstate_t;
+
+typedef vki_uint64_t            vki___fsfilcnt_t;
+
+//----------------------------------------------------------------------
+// sys/types.h
+//----------------------------------------------------------------------
+
+typedef vki_uint8_t             vki_u_int8_t;
+typedef vki_uint16_t            vki_u_int16_t;
+typedef vki_uint32_t            vki_u_int32_t;                                                                                                               
+typedef vki_uint64_t            vki_u_int64_t;
+
+typedef unsigned char           vki_u_char;
+typedef unsigned short          vki_u_short;
+typedef unsigned int            vki_u_int;
+typedef unsigned long           vki_u_long;
+
+typedef unsigned char           vki_unchar;
+typedef unsigned short          vki_ushort;
+typedef unsigned int            vki_uint;
+typedef unsigned long           vki_ulong;
+
+typedef vki_uint64_t            vki_u_quad_t;
+typedef vki_int64_t             vki_quad_t;
+typedef vki_quad_t *            vki_qaddr_t;
+
+typedef vki_int64_t             vki_longlong_t;
+typedef vki_uint64_t            vki_u_longlong_t;
+
+typedef vki_int64_t             vki_blkcnt_t;
+typedef vki_int32_t             vki_blksize_t;
+
+typedef vki___fsblkcnt_t        vki_fsblkcnt_t;
+typedef vki___fsfilcnt_t        vki_fsfilcnt_t;
+typedef vki___caddr_t           vki_caddr_t;
+typedef vki_int64_t             vki_daddr_t;
+
+typedef vki_uint64_t            vki_dev_t;
+typedef vki_uint32_t            vki_fixpt_t;
+typedef vki___gid_t             vki_gid_t;
+
+typedef vki_uint32_t            vki_id_t;
+typedef vki_uint64_t            vki_ino_t;
+typedef long                    vki_key_t;
+
+typedef vki___mode_t            vki_mode_t;
+
+typedef vki_uint32_t            vki_nlink_t;
+
+typedef vki___off_t             vki_off_t;
+typedef vki___pid_t             vki_pid_t;
+typedef vki_int32_t             vki_lwpid_t;
+typedef vki_uint64_t            vki_rlim_t;
+typedef vki_int32_t             vki_segsz_t;
+typedef vki_int32_t             vki_swblk_t;
+
+typedef vki___uid_t             vki_uid_t;
+
+typedef int                     vki_mqd_t;
+
+typedef unsigned long           vki_cpuid_t;
+
+typedef int                     vki_psetid_t;
+
+typedef volatile vki___cpu_simple_lock_nv_t vki___cpu_simple_lock_t;
+
+typedef int                     vki_boolean_t;
+
+typedef vki_int32_t             vki___devmajor_t;
+typedef vki_int32_t             vki___devminor_t;
+
+typedef vki___devmajor_t        vki_devmajor_t;
+typedef vki___devminor_t        vki_devminor_t;
+
+typedef vki_bsd_clock_t         vki_clock_t;
+typedef vki_bsd_ptrdiff_t       vki_ptrdiff_t;
+typedef vki_bsd_size_t          vki_size_t;
+typedef vki_bsd_ssize_t         vki_ssize_t;
+typedef vki_bsd_time_t          vki_time_t;
+typedef vki_bsd_clockid_t       vki_clockid_t;
+typedef vki_bsd_timer_t         vki_timer_t;
+typedef vki_bsd_suseconds_t     vki_suseconds_t;
+typedef vki_bsd_useconds_t      vki_useconds_t;
+
+typedef struct vki_kauth_cred * vki_kauth_cred_t;
+
+typedef int                     vki_pri_t;
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
+//----------------------------------------------------------------------
+// sys/syslimits.h
+//----------------------------------------------------------------------
+
+#define VKI_ARG_MAX             (256 * 1024)
+#define VKI_CHILD_MAX           160
+#define VKI_GID_MAX             2147483647U
+#define VKI_LINK_MAX            32767
+#define VKI_MAX_CANON           255
+#define VKI_MAX_INPUT           255
+#define VKI_NAME_MAX            511
+#define VKI_NGROUPS_MAX         16
+#define VKI_UID_MAX             2147483647U
+#define VKI_OPEN_MAX            128
+#define VKI_PATH_MAX            1024
+#define VKI_PIPE_BUF            512
+#define VKI_BC_BASE_MAX         VKI_INT_MAX
+#define VKI_BC_DIM_MAX          65535
+#define VKI_BC_SCALE_MAX        VKI_INT_MAX
+#define VKI_BC_STRING_MAX       VKI_INT_MAX
+#define VKI_COLL_WEIGHTS_MAX    2
+#define VKI_EXPR_NEST_MAX       32
+#define VKI_LINE_MAX            2048
+#define VKI_RE_DUP_MAX          255
+#define VKI_LOGIN_NAME_MAX      17
+#define VKI_IOV_MAX             1024
+#define VKI_NZERO               20
+
+//----------------------------------------------------------------------
+// sys/timespec.h
+//----------------------------------------------------------------------
+
+struct vki_timespec {
+        vki_time_t  tv_sec;         /* seconds */
+        long    tv_nsec;        /* and nanoseconds */
+};
+
+//----------------------------------------------------------------------
+// sys/time.h
+//----------------------------------------------------------------------
+
+struct vki_timeval {
+        vki_time_t          tv_sec;         /* seconds */
+        vki_suseconds_t     tv_usec;        /* and microseconds */
+};
+
+struct vki_timezone {
+        int     tz_minuteswest; /* minutes west of Greenwich */
+        int     tz_dsttime;     /* type of dst correction */
+};
+
+struct vki_bintime {
+        vki_time_t  sec;
+        vki_uint64_t frac;
+};
+
+struct  vki_itimerval {
+        struct  vki_timeval it_interval;    /* timer interval */
+        struct  vki_timeval it_value;       /* current value */
+};
+
+struct  vki_itimerspec {
+        struct  vki_timespec it_interval;
+        struct  vki_timespec it_value;
+};
+
+
+//----------------------------------------------------------------------
+// From sys/resource.h
+//----------------------------------------------------------------------
+
+struct  vki_rusage {
+        struct vki_timeval ru_utime;    /* user time used */
+        struct vki_timeval ru_stime;    /* system time used */
+        long    ru_maxrss;              /* maximum resident set size */                                                                                      
+        long    ru_ixrss;               /* integral shared memory size */
+        long    ru_idrss;               /* integral unshared data size */
+        long    ru_isrss;               /* integral unshared stack size */
+        long    ru_minflt;              /* page reclaims */                                                                                                  
+        long    ru_majflt;              /* page faults */                                                                                                    
+        long    ru_nswap;               /* swaps */
+        long    ru_inblock;             /* block input operations */
+        long    ru_oublock;             /* block output operations */
+        long    ru_msgsnd;              /* messages sent */
+        long    ru_msgrcv;              /* messages received */
+        long    ru_nsignals;            /* signals received */
+        long    ru_nvcsw;               /* voluntary context switches */
+        long    ru_nivcsw;              /* involuntary " */
+};
+
+struct vki_wrusage {
+        struct vki_rusage   wru_self;
+        struct vki_rusage   wru_children;
+};
+
+struct vki_rlimit {
+        vki_rlim_t  rlim_cur;               /* current (soft) limit */
+        vki_rlim_t  rlim_max;               /* maximum value for rlim_cur */
+};
+
+struct vki_loadavg {
+        vki_fixpt_t ldavg[3];
+        long    fscale;
+};
+
+//----------------------------------------------------------------------
+// From sys/sigtypes.h
+//----------------------------------------------------------------------
+
+typedef struct {
+        vki_uint32_t __bits[4];
+} vki_sigset_t;
+
+typedef struct vki_sigaltstack {
+        void *ss_sp;
+        vki_size_t ss_size;
+        int ss_flags;
+} vki_stack_t;
+
+//----------------------------------------------------------------------
+// From sys/sigtypes.h
+//----------------------------------------------------------------------
+
+typedef union vki_sigval {
+        int sival_int;
+        void *sival_ptr;
+} vki_sigval_t;
+
+struct vki__ksiginfo {
+        int     _signo;
+        int     _code;
+        int     _errno;
+#ifdef _LP64
+        /* In _LP64 the union starts on an 8-byte boundary. */
+        int     _pad;
+#endif
+        union {
+                struct {
+                        vki_pid_t   _pid;  
+                        vki_uid_t   _uid;  
+                        vki_sigval_t        _value;
+                } _rt;
+                
+                struct {
+                        vki_pid_t   _pid;  
+                        vki_uid_t   _uid;
+                        int     _status;
+                        vki_clock_t _utime;
+                        vki_clock_t _stime;
+                } _child;
+
+                struct {
+                        void   *_addr;  
+                        int     _trap; 
+                        int     _trap2;
+                        int     _trap3;
+                } _fault;
+
+                struct {                                                                                                                                     
+                        long    _band;
+                        int     _fd;
+                } _poll;                                                                                                                                     
+        } _reason;
+};
+
+typedef union vki_siginfo {
+        char    si_pad[128];    /* Total size; for future expansion */   
+        struct vki__ksiginfo _info;
+} vki_siginfo_t;
+
+#define vki_si_signo        _info._signo
+#define vki_si_code         _info._code
+#define vki_si_errno        _info._errno
+
+#define vki_si_value        _info._reason._rt._value   
+#define vki_si_pid          _info._reason._child._pid
+#define vki_si_uid          _info._reason._child._uid   
+#define vki_si_status       _info._reason._child._status
+#define vki_si_utime        _info._reason._child._utime                                                                                                          
+#define vki_si_stime        _info._reason._child._stime
+
+#define vki_si_addr         _info._reason._fault._addr
+#define vki_si_trap         _info._reason._fault._trap
+#define vki_si_trap2        _info._reason._fault._trap2
+#define vki_si_trap3        _info._reason._fault._trap3
+
+#define vki_si_band         _info._reason._poll._band
+#define vki_si_fd           _info._reason._poll._fd 
+
+#define VKI_ILL_ILLOPC      1       /* Illegal opcode                       */
+#define VKI_ILL_ILLOPN      2       /* Illegal operand                      */
+#define VKI_ILL_ILLADR      3       /* Illegal addressing mode              */
+#define VKI_ILL_ILLTRP      4       /* Illegal trap                         */
+#define VKI_ILL_PRVOPC      5       /* Privileged opcode                    */
+#define VKI_ILL_PRVREG      6       /* Privileged register                  */
+#define VKI_ILL_COPROC      7       /* Coprocessor error                    */
+#define VKI_ILL_BADSTK      8       /* Internal stack error                 */
+
+#define VKI_FPE_INTDIV      1       /* Integer divide by zero               */
+#define VKI_FPE_INTOVF      2       /* Integer overflow                     */
+#define VKI_FPE_FLTDIV      3       /* Floating point divide by zero        */
+#define VKI_FPE_FLTOVF      4       /* Floating point overflow              */
+#define VKI_FPE_FLTUND      5       /* Floating point underflow             */
+#define VKI_FPE_FLTRES      6       /* Floating point inexact result        */
+#define VKI_FPE_FLTINV      7       /* Invalid Floating point operation     */
+#define VKI_FPE_FLTSUB      8       /* Subscript out of range               */
+
+#define VKI_SEGV_MAPERR     1       /* Address not mapped to object         */
+#define VKI_SEGV_ACCERR     2       /* Invalid permissions for mapped object*/
+
+#define VKI_BUS_ADRALN      1       /* Invalid address alignment            */
+#define VKI_BUS_ADRERR      2       /* Non-existent physical address        */
+#define VKI_BUS_OBJERR      3       /* Object specific hardware error       */
+
+#define VKI_TRAP_BRKPT      1       /* Process breakpoint                   */
+#define VKI_TRAP_TRACE      2       /* Process trace trap                   */
+#define VKI_TRAP_EXEC       3       /* Process exec trap                    */
+#define VKI_TRAP_CHLD       4       /* Process child trap                   */                                                                                   
+#define VKI_TRAP_LWP        5       /* Process lwp trap                     */
+#define VKI_TRAP_DBREG      6       /* Process hardware debug register trap */
+#define VKI_TRAP_SCE        7       /* Process syscall entry trap           */
+#define VKI_TRAP_SCX        8       /* Process syscall exit trap            */
+
+#define VKI_CLD_EXITED      1       /* Child has exited                     */
+#define VKI_CLD_KILLED      2       /* Child has terminated abnormally but  */
+                                /* did not create a core file           */                                                                                   
+#define VKI_CLD_DUMPED      3       /* Child has terminated abnormally and  */
+                                /* created a core file                  */
+#define VKI_CLD_TRAPPED     4       /* Traced child has trapped             */
+#define VKI_CLD_STOPPED     5       /* Child has stopped                    */
+#define VKI_CLD_CONTINUED   6       /* Stopped child has continued          */
+
+#define VKI_POLL_IN         1       /* Data input available                 */
+#define VKI_POLL_OUT        2       /* Output buffers available             */                                                                                   
+#define VKI_POLL_MSG        3       /* Input message available              */
+#define VKI_POLL_ERR        4       /* I/O Error                            */
+#define VKI_POLL_PRI        5       /* High priority input available        */
+#define VKI_POLL_HUP        6       /* Device disconnected                  */
+
+#define VKI_SI_USER         0       /* Sent by kill(2)                      */
+#define VKI_SI_QUEUE        -1      /* Sent by the sigqueue(2)              */                                                                                   
+#define VKI_SI_TIMER        -2      /* Generated by expiration of a timer   */
+                                /* set by timer_settime(2)              */
+#define VKI_SI_ASYNCIO      -3      /* Generated by completion of an        */
+                                /* asynchronous I/O signal              */
+#define VKI_SI_MESGQ        -4      /* Generated by arrival of a message on */
+                                /* an empty message queue               */
+
+#define VKI_SI_LWP          -5      /* Generated by _lwp_kill(2)            */
+#define VKI_SI_NOINFO       32767   /* No signal specific info available    */
+
+//----------------------------------------------------------------------
+// From poll.h
+//----------------------------------------------------------------------
+
+typedef unsigned int    vki_nfds_t;
+
+struct vki_pollfd {
+        int     fd;             /* file descriptor */
+        short   events;         /* events to look for */
+        short   revents;        /* events returned */
+};
+
+#define VKI_POLLIN          0x0001
+#define VKI_POLLPRI         0x0002
+#define VKI_POLLOUT         0x0004
+#define VKI_POLLRDNORM      0x0040
+#define VKI_POLLWRNORM      POLLOUT
+#define VKI_POLLRDBAND      0x0080
+#define VKI_POLLWRBAND      0x0100
+
+#define VKI_POLLERR         0x0008
+#define VKI_POLLHUP         0x0010
+#define VKI_POLLNVAL        0x0020
+
+#define VKI_INFTIM          -1
+
+#endif // __VKI_NETBSD_H
+
+/*--------------------------------------------------------------------*/
+/*--- end                                                          ---*/
+/*--------------------------------------------------------------------*/
