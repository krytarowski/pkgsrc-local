$NetBSD$

--- include/vki/vki-netbsd.h.orig	2019-03-29 03:02:33.032190346 +0000
+++ include/vki/vki-netbsd.h
@@ -0,0 +1,1580 @@
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
+#define VKI_PRIO_MIN        -20
+#define VKI_PRIO_MAX        20
+
+#define VKI_PRIO_PROCESS    0
+#define VKI_PRIO_PGRP       1
+#define VKI_PRIO_USER       2
+
+#define VKI_RUSAGE_SELF     0
+#define VKI_RUSAGE_CHILDREN -1
+
+struct  vki_rusage {
+        struct vki_timeval ru_utime;    /* user time used */
+        struct vki_timeval ru_stime;    /* system time used */
+        long    ru_maxrss;              /* maximum resident set size */                                                                                      
+#define ru_first        ru_ixrss
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
+#define ru_last         ru_nivcsw
+};
+
+struct vki_wrusage {
+        struct vki_rusage   wru_self;
+        struct vki_rusage   wru_children;
+};
+
+#define VKI_RLIMIT_CPU      0               /* cpu time in milliseconds */
+#define VKI_RLIMIT_FSIZE    1               /* maximum file size */
+#define VKI_RLIMIT_DATA     2               /* data size */
+#define VKI_RLIMIT_STACK    3               /* stack size */
+#define VKI_RLIMIT_CORE     4               /* core file size */
+#define VKI_RLIMIT_RSS      5               /* resident set size */
+#define VKI_RLIMIT_MEMLOCK  6               /* locked-in-memory address space */
+#define VKI_RLIMIT_NPROC    7               /* number of processes */
+#define VKI_RLIMIT_NOFILE   8               /* number of open files */
+#define VKI_RLIMIT_SBSIZE   9               /* maximum size of all socket buffers */
+#define VKI_RLIMIT_AS       10              /* virtual process size (inclusive of mmap) */
+#define VKI_RLIMIT_VMEM     VKI_RLIMIT_AS       /* common alias */
+#define VKI_RLIMIT_NTHR     11              /* number of threads */
+
+#define VKI_RLIM_NLIMITS    12              /* number of resource limits */
+
+#define VKI_RLIM_INFINITY   (~((vki_u_quad_t)1 << 63))  /* no limit */
+#define VKI_RLIM_SAVED_MAX  VKI_RLIM_INFINITY   /* unrepresentable hard limit */
+#define VKI_RLIM_SAVED_CUR  VKI_RLIM_INFINITY   /* unrepresentable soft limit */
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
+//----------------------------------------------------------------------
+// From sys/socket.h
+//----------------------------------------------------------------------
+
+typedef vki___sa_family_t   vki_sa_family_t;
+
+typedef vki___socklen_t     vki_socklen_t;
+
+struct  vki_linger {
+        int     l_onoff;                /* option on/off */
+        int     l_linger;               /* linger time in seconds */
+};
+
+struct  vki_accept_filter_arg {
+        char    af_name[16];
+        char    af_arg[256-16];
+};
+
+struct vki_sockaddr {
+        vki_uint8_t       sa_len;         /* total length */
+        vki_sa_family_t     sa_family;      /* address family */
+        char            sa_data[14];    /* actually longer; address value */
+};
+
+#define VKI__SS_MAXSIZE     128
+#define VKI__SS_ALIGNSIZE   (sizeof(vki_int64_t))
+#define VKI__SS_PAD1SIZE    (VKI__SS_ALIGNSIZE - 2)
+#define VKI__SS_PAD2SIZE    (VKI__SS_MAXSIZE - 2 - \
+                                VKI__SS_PAD1SIZE - VKI__SS_ALIGNSIZE)
+
+struct vki_sockaddr_storage {
+        vki_uint8_t       ss_len;         /* address length */
+        vki_sa_family_t     ss_family;      /* address family */
+        char            __ss_pad1[VKI__SS_PAD1SIZE];
+        vki_int64_t     __ss_align;/* force desired structure storage alignment */                                                                             
+        char            __ss_pad2[VKI__SS_PAD2SIZE];
+};
+
+struct vki_sockcred {
+        vki_pid_t   sc_pid;                 /* process id */
+        vki_uid_t   sc_uid;                 /* real user id */
+        vki_uid_t   sc_euid;                /* effective user id */
+        vki_gid_t   sc_gid;                 /* real group id */
+        vki_gid_t   sc_egid;                /* effective group id */
+        int     sc_ngroups;             /* number of supplemental groups */
+        vki_gid_t   sc_groups[1];           /* variable length */
+};
+
+struct vki_kinfo_pcb {
+        vki_uint64_t      ki_pcbaddr;     /* PTR: pcb addr */
+        vki_uint64_t      ki_ppcbaddr;    /* PTR: ppcb addr */
+        vki_uint64_t      ki_sockaddr;    /* PTR: socket addr */
+
+        vki_uint32_t      ki_family;      /* INT: protocol family */
+        vki_uint32_t      ki_type;        /* INT: socket type */
+        vki_uint32_t      ki_protocol;    /* INT: protocol */
+        vki_uint32_t      ki_pflags;      /* INT: generic protocol flags */
+
+        vki_uint32_t      ki_sostate;     /* INT: socket state */
+        vki_uint32_t      ki_prstate;     /* INT: protocol state */
+        vki_int32_t       ki_tstate;      /* INT: tcp state */
+        vki_uint32_t      ki_tflags;      /* INT: tcp flags */
+
+        vki_uint64_t      ki_rcvq;        /* U_LONG: receive queue len */
+        vki_uint64_t      ki_sndq;        /* U_LONG: send queue len */
+
+        union {
+                struct vki_sockaddr _kis_src; /* STRUCT: local address */
+                char _kis_pad[256 + 8];         /* pad to max addr length */
+        } ki_s;
+        union {
+                struct vki_sockaddr _kid_dst; /* STRUCT: remote address */
+                char _kid_pad[256 + 8];         /* pad to max addr length */
+        } ki_d;
+
+        vki_uint64_t      ki_inode;       /* INO_T: fake inode number */                                                                                       
+        vki_uint64_t      ki_vnode;       /* PTR: if associated with file */
+        vki_uint64_t      ki_conn;        /* PTR: control block of peer */
+        vki_uint64_t      ki_refs;        /* PTR: referencing socket */
+        vki_uint64_t      ki_nextref;     /* PTR: link in refs list */
+};
+
+#define vki_ki_src ki_s._kis_src
+#define vki_ki_dst ki_d._kid_dst
+#define vki_ki_spad ki_s._kis_pad
+#define vki_ki_dpad ki_d._kid_pad
+
+struct vki_msghdr {
+        void            *msg_name;      /* optional address */
+        vki_socklen_t       msg_namelen;    /* size of address */
+        struct vki_iovec    *msg_iov;       /* scatter/gather array */
+        int             msg_iovlen;     /* # elements in msg_iov */
+        void            *msg_control;   /* ancillary data, see below */
+        vki_socklen_t       msg_controllen; /* ancillary data buffer len */
+        int             msg_flags;      /* flags on received message */
+};
+
+struct vki_mmsghdr {
+        struct vki_msghdr msg_hdr;
+        unsigned int msg_len;
+};
+
+struct vki_cmsghdr {
+        vki_socklen_t       cmsg_len;       /* data byte count, including hdr */
+        int             cmsg_level;     /* originating protocol */
+        int             cmsg_type;      /* protocol-specific type */
+/* followed by  u_char  cmsg_data[]; */
+};
+
+//----------------------------------------------------------------------
+// From sys/signal.h
+//----------------------------------------------------------------------
+
+#define VKI__NSIG           64
+#define VKI_NSIG VKI__NSIG
+
+#define VKI_SIGHUP          1       /* hangup */   
+#define VKI_SIGINT          2       /* interrupt */
+#define VKI_SIGQUIT         3       /* quit */
+#define VKI_SIGILL          4       /* illegal instruction (not reset when caught) */
+#define VKI_SIGTRAP         5       /* trace trap (not reset when caught) */
+#define VKI_SIGABRT         6       /* abort() */                                                                                                                
+#define VKI_SIGIOT          VKI_SIGABRT /* compatibility */
+#define VKI_SIGEMT          7       /* EMT instruction */
+#define VKI_SIGFPE          8       /* floating point exception */
+#define VKI_SIGKILL         9       /* kill (cannot be caught or ignored) */
+#define VKI_SIGBUS          10      /* bus error */
+#define VKI_SIGSEGV         11      /* segmentation violation */
+#define VKI_SIGSYS          12      /* bad argument to system call */
+#define VKI_SIGPIPE         13      /* write on a pipe with no one to read it */
+#define VKI_SIGALRM         14      /* alarm clock */                                                                                                            
+#define VKI_SIGTERM         15      /* software termination signal from kill */
+#define VKI_SIGURG          16      /* urgent condition on IO channel */
+#define VKI_SIGSTOP         17      /* sendable stop signal not from tty */
+#define VKI_SIGTSTP         18      /* stop signal from tty */
+#define VKI_SIGCONT         19      /* continue a stopped process */
+#define VKI_SIGCHLD         20      /* to parent on child stop or exit */
+#define VKI_SIGTTIN         21      /* to readers pgrp upon background tty read */
+#define VKI_SIGTTOU         22      /* like TTIN for output if (tp->t_local&LTOSTOP) */
+#define VKI_SIGIO           23      /* input/output possible signal */                                                                                           
+#define VKI_SIGXCPU         24      /* exceeded CPU time limit */
+#define VKI_SIGXFSZ         25      /* exceeded file size limit */
+#define VKI_SIGVTALRM       26      /* virtual time alarm */
+#define VKI_SIGPROF         27      /* profiling time alarm */
+#define VKI_SIGWINCH        28      /* window size changes */
+#define VKI_SIGINFO         29      /* information request */
+#define VKI_SIGUSR1         30      /* user defined signal 1 */
+#define VKI_SIGUSR2         31      /* user defined signal 2 */
+#define VKI_SIGPWR          32      /* power fail/restart (not reset when caught) */                                                                             
+#define VKI_SIGRTMIN        33
+#define VKI_SIGRTMAX        63
+
+#define VKI_SIG_DFL         ((void (*)(int))  0)
+#define VKI_SIG_IGN         ((void (*)(int))  1)
+#define VKI_SIG_ERR         ((void (*)(int)) -1)
+#define VKI_SIG_HOLD        ((void (*)(int))  3)
+
+struct  vki_sigaction {
+        union {
+                void (*_sa_handler)(int);
+                void (*_sa_sigaction)(int, vki_siginfo_t *, void *);
+        } _sa_u;        /* signal handler */
+        vki_sigset_t sa_mask;               /* signal mask to apply */  
+        int     sa_flags;               /* see signal options below */
+};
+
+typedef  struct vki_sigaction  vki_sigaction_toK_t; // compat with linux
+typedef  struct vki_sigaction  vki_sigaction_fromK_t; // compat with linux
+
+#define vki_sa_handler _sa_u._sa_handler
+
+#define VKI_SA_ONSTACK      0x0001  /* take signal on signal stack */
+#define VKI_SA_RESTART      0x0002  /* restart system call on signal return */
+#define VKI_SA_RESETHAND    0x0004  /* reset to SIG_DFL when taking signal */
+#define VKI_SA_NODEFER      0x0010  /* don't mask the signal we're delivering */
+
+#define VKI_SA_NOCLDSTOP    0x0008  /* do not generate SIGCHLD on child stop */
+#define VKI_SA_NOCLDWAIT    0x0020  /* do not generate zombies on unwaited child */
+
+#define VKI_SA_SIGINFO      0x0040  /* take sa_sigaction handler */
+
+#define VKI_SA_NOKERNINFO   0x0080  /* siginfo does not print kernel info on tty */
+
+#define VKI_SIG_BLOCK       1       /* block specified signal set */
+#define VKI_SIG_UNBLOCK     2       /* unblock specified signal set */
+#define VKI_SIG_SETMASK     3       /* set specified signal set */
+
+#define VKI_SS_INIT 
+
+#define VKI_SS_ONSTACK      0x0001  /* take signals on alternate stack */
+#define VKI_SS_DISABLE      0x0004  /* disable taking signals on alternate stack */
+
+#define VKI_MINSIGSTKSZ     8192                    /* minimum allowable stack */
+#define VKI_SIGSTKSZ        (VKI_MINSIGSTKSZ + 32768)   /* recommended stack size */
+
+struct  vki_sigstack {
+        void    *ss_sp;                 /* signal stack pointer */
+        int     ss_onstack;             /* current status */
+};
+
+#define VKI_BADSIG          VKI_SIG_ERR
+
+struct  vki_sigevent {
+        int     sigev_notify;                                                                                                                                
+        int     sigev_signo;
+        union vki_sigval    sigev_value;
+        void    (*sigev_notify_function)(union vki_sigval);
+        void /* pthread_attr_t */       *sigev_notify_attributes;
+};
+
+#define VKI_SIGEV_NONE      0  
+#define VKI_SIGEV_SIGNAL    1
+#define VKI_SIGEV_THREAD    2
+
+#define VKI_SIGEV_SA        3
+
+//----------------------------------------------------------------------
+// From sys/ucontext.h
+//----------------------------------------------------------------------
+
+typedef struct vki___ucontext       vki_ucontext_t;
+
+struct vki___ucontext {
+        unsigned int    uc_flags;       /* properties */
+        vki_ucontext_t *    uc_link;        /* context to resume */
+        vki_sigset_t        uc_sigmask;     /* signals blocked in this context */ 
+        vki_stack_t         uc_stack;       /* the stack used by this context */ 
+        vki_mcontext_t      uc_mcontext;    /* machine state */
+#if defined(VKI__UC_MACHINE_PAD)
+        long            __uc_pad[VKI__UC_MACHINE_PAD];
+#endif
+};
+
+#define vki_ucontext vki___ucontext // compat with linux
+
+//----------------------------------------------------------------------
+// From sys/stat.h
+//----------------------------------------------------------------------
+
+struct vki_stat {
+        vki_dev_t     st_dev;               /* inode's device */
+        vki_mode_t    st_mode;              /* inode protection mode */
+        vki_ino_t     st_ino;               /* inode's number */
+        vki_nlink_t   st_nlink;             /* number of hard links */
+        vki_uid_t     st_uid;               /* user ID of the file's owner */
+        vki_gid_t     st_gid;               /* group ID of the file's group */
+        vki_dev_t     st_rdev;              /* device type */
+        struct    vki_timespec st_atim;     /* time of last access */
+        struct    vki_timespec st_mtim;     /* time of last data modification */
+        struct    vki_timespec st_ctim;     /* time of last file status change */
+        struct    vki_timespec st_birthtim; /* time of creation */
+        vki_off_t     st_size;              /* file size, in bytes */
+        vki_blkcnt_t  st_blocks;            /* blocks allocated for file */
+        vki_blksize_t st_blksize;           /* optimal blocksize for I/O */
+        vki_uint32_t  st_flags;             /* user defined flags for file */
+        vki_uint32_t  st_gen;               /* file generation number */
+        vki_uint32_t  st_spare[2];
+};
+
+#define st_atime                st_atim.tv_sec
+#define st_mtime                st_mtim.tv_sec
+#define st_ctime                st_ctim.tv_sec
+#define st_birthtime            st_birthtim.tv_sec
+
+#define st_atimespec            st_atim
+#define st_atimensec            st_atim.tv_nsec
+#define st_mtimespec            st_mtim
+#define st_mtimensec            st_mtim.tv_nsec
+#define st_ctimespec            st_ctim
+#define st_ctimensec            st_ctim.tv_nsec
+#define st_birthtimespec        st_birthtim
+#define st_birthtimensec        st_birthtimespec.tv_nsec
+
+#define VKI_S_ISUID 0004000                 /* set user id on execution */
+#define VKI_S_ISGID 0002000                 /* set group id on execution */
+
+#define VKI_S_ISTXT 0001000                 /* sticky bit */
+
+#define VKI_S_IRWXU 0000700                 /* RWX mask for owner */
+#define VKI_S_IRUSR 0000400                 /* R for owner */                                                                                                    
+#define VKI_S_IWUSR 0000200                 /* W for owner */
+#define VKI_S_IXUSR 0000100                 /* X for owner */
+
+#define VKI_S_IREAD         VKI_S_IRUSR
+#define VKI_S_IWRITE        VKI_S_IWUSR
+#define VKI_S_IEXEC         VKI_S_IXUSR
+#define VKI_S_IRWXG 0000070                 /* RWX mask for group */
+#define VKI_S_IRGRP 0000040                 /* R for group */
+#define VKI_S_IWGRP 0000020                 /* W for group */
+#define VKI_S_IXGRP 0000010                 /* X for group */
+
+#define VKI_S_IRWXO 0000007                 /* RWX mask for other */
+#define VKI_S_IROTH 0000004                 /* R for other */
+#define VKI_S_IWOTH 0000002                 /* W for other */
+#define VKI_S_IXOTH 0000001                 /* X for other */                                                                                                    
+
+#define VKI__S_IFMT   0170000               /* type of file mask */
+#define VKI__S_IFIFO  0010000               /* named pipe (fifo) */
+#define VKI__S_IFCHR  0020000               /* character special */
+#define VKI__S_IFDIR  0040000               /* directory */
+#define VKI__S_IFBLK  0060000               /* block special */
+#define VKI__S_IFREG  0100000               /* regular */
+#define VKI__S_IFLNK  0120000               /* symbolic link */
+#define VKI__S_ISVTX  0001000               /* save swapped text even after use */                                                                               
+#define VKI__S_IFSOCK 0140000               /* socket */
+#define VKI__S_IFWHT  0160000               /* whiteout */
+
+#define VKI__S_ARCH1  0200000               /* Archive state 1, ls -l shows 'a' */
+#define VKI__S_ARCH2  0400000               /* Archive state 2, ls -l shows 'A' */
+
+#define VKI_S_IFMT   VKI__S_IFMT
+#define VKI_S_IFIFO  VKI__S_IFIFO
+#define VKI_S_IFCHR  VKI__S_IFCHR                                                                                                                                    
+#define VKI_S_IFDIR  VKI__S_IFDIR
+#define VKI_S_IFBLK  VKI__S_IFBLK
+#define VKI_S_IFREG  VKI__S_IFREG
+#define VKI_S_IFLNK  VKI__S_IFLNK
+#define VKI_S_ISVTX  VKI__S_ISVTX
+
+#define VKI_S_IFSOCK VKI__S_IFSOCK
+
+#define VKI_S_IFWHT  VKI__S_IFWHT
+
+#define VKI_S_ARCH1 VKI__S_ARCH1 
+#define VKI_S_ARCH2 VKI__S_ARCH2 
+
+#define VKI_S_ISDIR(m)      (((m) & VKI__S_IFMT) == VKI__S_IFDIR)   /* directory */
+#define VKI_S_ISCHR(m)      (((m) & VKI__S_IFMT) == VKI__S_IFCHR)   /* char special */
+#define VKI_S_ISBLK(m)      (((m) & VKI__S_IFMT) == VKI__S_IFBLK)   /* block special */
+#define VKI_S_ISREG(m)      (((m) & VKI__S_IFMT) == VKI__S_IFREG)   /* regular file */
+#define VKI_S_ISFIFO(m)     (((m) & VKI__S_IFMT) == VKI__S_IFIFO)   /* fifo */
+
+#define VKI_S_ISLNK(m)      (((m) & VKI__S_IFMT) == VKI__S_IFLNK)   /* symbolic link */
+
+#define VKI_S_ISSOCK(m)     (((m) & VKI__S_IFMT) == VKI__S_IFSOCK)  /* socket */
+
+#define VKI_S_ISWHT(m)      (((m) & VKI__S_IFMT) == VKI__S_IFWHT)   /* whiteout */
+
+#define VKI_ACCESSPERMS     (VKI_S_IRWXU|VKI_S_IRWXG|VKI_S_IRWXO)       /* 0777 */
+                                                        /* 7777 */                                                                                           
+#define VKI_ALLPERMS        (VKI_S_ISUID|VKI_S_ISGID|VKI_S_ISTXT|VKI_S_IRWXU|VKI_S_IRWXG|VKI_S_IRWXO)
+                                                        /* 0666 */
+#define VKI_DEFFILEMODE     (VKI_S_IRUSR|VKI_S_IWUSR|VKI_S_IRGRP|VKI_S_IWGRP|VKI_S_IROTH|VKI_S_IWOTH)
+
+#define VKI_S_BLKSIZE       512             /* block size used in the stat struct */
+
+#define VKI_UF_SETTABLE     0x0000ffff      /* mask of owner changeable flags */
+#define VKI_UF_NODUMP       0x00000001      /* do not dump file */
+#define VKI_UF_IMMUTABLE    0x00000002      /* file may not be changed */
+#define VKI_UF_APPEND       0x00000004      /* writes to file may only append */
+#define VKI_UF_OPAQUE       0x00000008      /* directory is opaque wrt. union */
+
+#define VKI_SF_SETTABLE     0xffff0000      /* mask of superuser changeable flags */
+#define VKI_SF_ARCHIVED     0x00010000      /* file is archived */
+#define VKI_SF_IMMUTABLE    0x00020000      /* file may not be changed */
+#define VKI_SF_APPEND       0x00040000      /* writes to file may only append */
+/*      VKI_SF_NOUNLINK     0x00100000         [NOT IMPLEMENTED] */
+#define VKI_SF_SNAPSHOT     0x00200000      /* snapshot inode */
+#define VKI_SF_LOG          0x00400000      /* WAPBL log file inode */                                                                                           
+#define VKI_SF_SNAPINVAL    0x00800000      /* snapshot is invalid */
+
+#define VKI_UTIME_NOW       ((1 << 30) - 1)
+#define VKI_UTIME_OMIT      ((1 << 30) - 2)
+
+//----------------------------------------------------------------------
+// From sys/fntl.h
+//----------------------------------------------------------------------
+
+#define VKI_O_RDONLY        0x00000000      /* open for reading only */
+#define VKI_O_WRONLY        0x00000001      /* open for writing only */
+#define VKI_O_RDWR          0x00000002      /* open for reading and writing */
+#define VKI_O_ACCMODE       0x00000003      /* mask for above modes */
+
+#define VKI_FREAD           0x00000001
+#define VKI_FWRITE          0x00000002
+
+#define VKI_O_NONBLOCK      0x00000004      /* no delay */
+#define VKI_O_APPEND        0x00000008      /* set append mode */
+
+#define VKI_O_SHLOCK        0x00000010      /* open with shared file lock */
+#define VKI_O_EXLOCK        0x00000020      /* open with exclusive file lock */
+#define VKI_O_ASYNC         0x00000040      /* signal pgrp when data ready */
+
+#define VKI_O_SYNC          0x00000080      /* synchronous writes */
+
+#define VKI_O_NOFOLLOW      0x00000100      /* don't follow symlinks on the last */
+
+#define VKI_O_CREAT         0x00000200      /* create if nonexistent */
+#define VKI_O_TRUNC         0x00000400      /* truncate to zero length */
+#define VKI_O_EXCL          0x00000800      /* error if already exists */
+
+#define VKI_O_NOCTTY        0x00008000      /* don't assign controlling terminal */
+
+#define VKI_O_DSYNC         0x00010000      /* write: I/O data completion */
+#define VKI_O_RSYNC         0x00020000      /* read: I/O completion as for write */
+
+#define VKI_O_ALT_IO        0x00040000      /* use alternate i/o semantics */
+#define VKI_O_DIRECT        0x00080000      /* direct I/O hint */
+
+#define VKI_O_DIRECTORY     0x00200000      /* fail if not a directory */
+#define VKI_O_CLOEXEC       0x00400000      /* set close on exec */
+
+#define VKI_O_SEARCH        0x00800000      /* skip search permission checks */
+
+#define VKI_O_NOSIGPIPE     0x01000000      /* don't deliver sigpipe */
+#define VKI_O_REGULAR       0x02000000      /* fail if not a regular file */
+
+#define VKI_FAPPEND         VKI_O_APPEND        /* kernel/compat */
+#define VKI_FASYNC          VKI_O_ASYNC         /* kernel/compat */
+#define VKI_O_FSYNC         VKI_O_SYNC          /* compat */
+#define VKI_FNDELAY         VKI_O_NONBLOCK      /* compat */
+#define VKI_O_NDELAY        VKI_O_NONBLOCK      /* compat */
+
+#define VKI_F_DUPFD         0               /* duplicate file descriptor */
+#define VKI_F_GETFD         1               /* get file descriptor flags */
+#define VKI_F_SETFD         2               /* set file descriptor flags */
+#define VKI_F_GETFL         3               /* get file status flags */                                                                                          
+#define VKI_F_SETFL         4               /* set file status flags */
+
+#define VKI_F_GETOWN        5               /* get SIGIO/SIGURG proc/pgrp */
+#define VKI_F_SETOWN        6               /* set SIGIO/SIGURG proc/pgrp */
+
+#define VKI_F_GETLK         7               /* get record locking information */
+#define VKI_F_SETLK         8               /* set record locking information */
+#define VKI_F_SETLKW        9               /* F_SETLK; wait if blocked */ 
+
+#define VKI_F_CLOSEM        10              /* close all fds >= to the one given */
+#define VKI_F_MAXFD         11              /* return the max open fd */
+#define VKI_F_DUPFD_CLOEXEC 12              /* close on exec duplicated fd */
+#define VKI_F_GETNOSIGPIPE  13              /* get SIGPIPE disposition */
+#define VKI_F_SETNOSIGPIPE  14              /* set SIGPIPE disposition */
+
+#define VKI_FD_CLOEXEC      1               /* close-on-exec flag */
+
+#define VKI_F_RDLCK         1               /* shared or read lock */
+#define VKI_F_UNLCK         2               /* unlock */
+#define VKI_F_WRLCK         3               /* exclusive or write lock */
+
+#define VKI_F_PARAM_MASK    0xfff
+#define VKI_F_PARAM_LEN(x)  (((x) >> 16) & VKI_F_PARAM_MASK)
+#define VKI_F_PARAM_MAX     4095
+#define VKI_F_FSCTL         (int)0x80000000 /* This fcntl goes to the fs */                                                                                      
+#define VKI_F_FSVOID        (int)0x40000000 /* no parameters */
+#define VKI_F_FSOUT         (int)0x20000000 /* copy out parameter */
+#define VKI_F_FSIN          (int)0x10000000 /* copy in parameter */
+#define VKI_F_FSINOUT       (VKI_F_FSIN | VKI_F_FSOUT)
+#define VKI_F_FSDIRMASK     (int)0x70000000 /* mask for IN/OUT/VOID */
+#define VKI_F_FSPRIV        (int)0x00008000 /* command is fs-specific */
+
+#define VKI__FCN(inout, num, len) \
+                (VKI_F_FSCTL | inout | ((len & VKI_F_PARAM_MASK) << 16) | (num))
+#define VKI__FCNO(c)        VKI__FCN(F_FSVOID,  (c), 0)
+#define VKI__FCNR(c, t)     VKI__FCN(F_FSIN,    (c), (int)sizeof(t))
+#define VKI__FCNW(c, t)     VKI__FCN(F_FSOUT,   (c), (int)sizeof(t))
+#define VKI__FCNRW(c, t)    VKI__FCN(F_FSINOUT, (c), (int)sizeof(t))
+
+#define VKI__FCN_FSPRIV(inout, fs, num, len) \
+        (VKI_F_FSCTL | VKI_F_FSPRIV | inout | ((len & VKI_F_PARAM_MASK) << 16) |    \
+         (fs) << 8 | (num))
+#define VKI__FCNO_FSPRIV(f, c)      VKI__FCN_FSPRIV(F_FSVOID,  (f), (c), 0)
+#define VKI__FCNR_FSPRIV(f, c, t)   VKI__FCN_FSPRIV(F_FSIN,    (f), (c), (int)sizeof(t))
+#define VKI__FCNW_FSPRIV(f, c, t)   VKI__FCN_FSPRIV(F_FSOUT,   (f), (c), (int)sizeof(t))                                                                             
+#define VKI__FCNRW_FSPRIV(f, c, t)  VKI__FCN_FSPRIV(F_FSINOUT, (f), (c), (int)sizeof(t))
+
+struct vki_flock {                                                                                                                                               
+        vki_off_t   l_start;        /* starting offset */
+        vki_off_t   l_len;          /* len = 0 means until end of file */
+        vki_pid_t   l_pid;          /* lock owner */
+        short   l_type;         /* lock type: read/write, etc. */
+        short   l_whence;       /* type of l_start */
+};
+
+#define VKI_LOCK_SH         0x01            /* shared file lock */
+#define VKI_LOCK_EX         0x02            /* exclusive file lock */
+#define VKI_LOCK_NB         0x04            /* don't block when locking */
+#define VKI_LOCK_UN         0x08            /* unlock file */
+
+/* Always ensure that these are consistent with <stdio.h> and <unistd.h>! */
+#ifndef VKI_SEEK_SET
+#define VKI_SEEK_SET        0       /* set file offset to offset */
+#endif
+
+#ifndef VKI_SEEK_CUR
+#define VKI_SEEK_CUR        1       /* set file offset to current plus offset */
+#endif
+
+#ifndef VKI_SEEK_END
+#define VKI_SEEK_END        2       /* set file offset to EOF plus offset */
+#endif
+
+#define VKI_POSIX_FADV_NORMAL       0       /* default advice / no advice */
+#define VKI_POSIX_FADV_RANDOM       1       /* random access */
+#define VKI_POSIX_FADV_SEQUENTIAL   2       /* sequential access(lower to higher) */
+#define VKI_POSIX_FADV_WILLNEED     3       /* be needed in near future */
+#define VKI_POSIX_FADV_DONTNEED     4       /* not be needed in near future */                                                                                   
+#define VKI_POSIX_FADV_NOREUSE      5       /* be accessed once */
+
+#define VKI_AT_FDCWD                -100    /* Use cwd for relative link target */                                                                               
+#define VKI_AT_EACCESS              0x100   /* Use euig/egid for access checks */
+#define VKI_AT_SYMLINK_NOFOLLOW     0x200   /* Do not follow symlinks */
+#define VKI_AT_SYMLINK_FOLLOW       0x400   /* Follow symlinks */
+#define VKI_AT_REMOVEDIR            0x800   /* Remove directory only */
+
+//----------------------------------------------------------------------
+// From sys/errno.h
+//----------------------------------------------------------------------
+
+#define VKI_EPERM		1		/* Operation not permitted */
+#define VKI_ENOENT		2		/* No such file or directory */
+#define VKI_ESRCH		3		/* No such process */
+#define VKI_EINTR		4		/* Interrupted system call */
+#define VKI_EIO		5		/* Input/output error */
+#define VKI_ENXIO		6		/* Device not configured */
+#define VKI_E2BIG		7		/* Argument list too long */
+#define VKI_ENOEXEC		8		/* Exec format error */
+#define VKI_EBADF		9		/* Bad file descriptor */
+#define VKI_ECHILD		10		/* No child processes */
+#define VKI_EDEADLK		11		/* Resource deadlock avoided */
+#define VKI_ENOMEM		12		/* Cannot allocate memory */
+#define VKI_EACCES		13		/* Permission denied */
+#define VKI_EFAULT		14		/* Bad address */
+#define VKI_ENOTBLK		15		/* Block device required */
+#define VKI_EBUSY		16		/* Device busy */
+#define VKI_EEXIST		17		/* File exists */
+#define VKI_EXDEV		18		/* Cross-device link */
+#define VKI_ENODEV		19		/* Operation not supported by device */
+#define VKI_ENOTDIR		20		/* Not a directory */
+#define VKI_EISDIR		21		/* Is a directory */
+#define VKI_EINVAL		22		/* Invalid argument */
+#define VKI_ENFILE		23		/* Too many open files in system */
+#define VKI_EMFILE		24		/* Too many open files */
+#define VKI_ENOTTY		25		/* Inappropriate ioctl for device */
+#define VKI_ETXTBSY		26		/* Text file busy */
+#define VKI_EFBIG		27		/* File too large */
+#define VKI_ENOSPC		28		/* No space left on device */
+#define VKI_ESPIPE		29		/* Illegal seek */
+#define VKI_EROFS		30		/* Read-only file system */
+#define VKI_EMLINK		31		/* Too many links */
+#define VKI_EPIPE		32		/* Broken pipe */
+#define VKI_EDOM		33		/* Numerical argument out of domain */
+#define VKI_ERANGE		34		/* Result too large or too small */
+#define VKI_EAGAIN		35		/* Resource temporarily unavailable */
+#define VKI_EWOULDBLOCK	EAGAIN		/* Operation would block */
+#define VKI_EINPROGRESS	36		/* Operation now in progress */
+#define VKI_EALREADY	37		/* Operation already in progress */
+#define VKI_ENOTSOCK	38		/* Socket operation on non-socket */
+#define VKI_EDESTADDRREQ	39		/* Destination address required */
+#define VKI_EMSGSIZE	40		/* Message too long */
+#define VKI_EPROTOTYPE	41		/* Protocol wrong type for socket */
+#define VKI_ENOPROTOOPT	42		/* Protocol option not available */
+#define VKI_EPROTONOSUPPORT	43		/* Protocol not supported */
+#define VKI_ESOCKTNOSUPPORT	44		/* Socket type not supported */
+#define VKI_EOPNOTSUPP	45		/* Operation not supported */
+#define VKI_EPFNOSUPPORT	46		/* Protocol family not supported */
+#define VKI_EAFNOSUPPORT	47		/* Address family not supported by protocol family */
+#define VKI_EADDRINUSE	48		/* Address already in use */
+#define VKI_EADDRNOTAVAIL	49		/* Can't assign requested address */
+#define VKI_ENETDOWN	50		/* Network is down */
+#define VKI_ENETUNREACH	51		/* Network is unreachable */
+#define VKI_ENETRESET	52		/* Network dropped connection on reset */
+#define VKI_ECONNABORTED	53		/* Software caused connection abort */
+#define VKI_ECONNRESET	54		/* Connection reset by peer */
+#define VKI_ENOBUFS		55		/* No buffer space available */
+#define VKI_EISCONN		56		/* Socket is already connected */
+#define VKI_ENOTCONN	57		/* Socket is not connected */
+#define VKI_ESHUTDOWN	58		/* Can't send after socket shutdown */
+#define VKI_ETOOMANYREFS	59		/* Too many references: can't splice */
+#define VKI_ETIMEDOUT	60		/* Operation timed out */
+#define VKI_ECONNREFUSED	61		/* Connection refused */
+#define VKI_ELOOP		62		/* Too many levels of symbolic links */
+#define VKI_ENAMETOOLONG	63		/* File name too long */
+#define VKI_EHOSTDOWN	64		/* Host is down */
+#define VKI_EHOSTUNREACH	65		/* No route to host */
+#define VKI_ENOTEMPTY	66		/* Directory not empty */
+#define VKI_EPROCLIM	67		/* Too many processes */
+#define VKI_EUSERS		68		/* Too many users */
+#define VKI_EDQUOT		69		/* Disc quota exceeded */
+#define VKI_ESTALE		70		/* Stale NFS file handle */
+#define VKI_EREMOTE		71		/* Too many levels of remote in path */
+#define VKI_EBADRPC		72		/* RPC struct is bad */
+#define VKI_ERPCMISMATCH	73		/* RPC version wrong */
+#define VKI_EPROGUNAVAIL	74		/* RPC prog. not avail */
+#define VKI_EPROGMISMATCH	75		/* Program version wrong */
+#define VKI_EPROCUNAVAIL	76		/* Bad procedure for program */
+#define VKI_ENOLCK		77		/* No locks available */
+#define VKI_ENOSYS		78		/* Function not implemented */
+#define VKI_EFTYPE		79		/* Inappropriate file type or format */
+#define VKI_EAUTH		80		/* Authentication error */
+#define VKI_ENEEDAUTH	81		/* Need authenticator */
+#define VKI_EIDRM		82		/* Identifier removed */
+#define VKI_ENOMSG		83		/* No message of desired type */
+#define VKI_EOVERFLOW	84		/* Value too large to be stored in data type */
+#define VKI_EILSEQ		85		/* Illegal byte sequence */
+#define VKI_ENOTSUP		86		/* Not supported */
+#define VKI_ECANCELED	87		/* Operation canceled */
+#define VKI_EBADMSG		88		/* Bad or Corrupt message */
+#define VKI_ENODATA		89		/* No message available */
+#define VKI_ENOSR		90		/* No STREAM resources */
+#define VKI_ENOSTR		91		/* Not a STREAM */
+#define VKI_ETIME		92		/* STREAM ioctl timeout */
+#define VKI_ENOATTR		93		/* Attribute not found */
+#define VKI_EMULTIHOP	94		/* Multihop attempted */ 
+#define VKI_ENOLINK		95		/* Link has been severed */
+#define VKI_EPROTO		96		/* Protocol error */
+#define VKI_ELAST		96		/* Must equal largest errno */
+#define VKI_EJUSTRETURN	-2		/* don't modify regs, just return */
+#define VKI_ERESTART	-3		/* restart syscall */
+#define VKI_EPASSTHROUGH	-4		/* ioctl not handled by this layer */
+#define VKI_EDUPFD		-5		/* Dup given fd */
+#define VKI_EMOVEFD		-6		/* Move given fd */
+
+//----------------------------------------------------------------------
+// From unistd.h
+//----------------------------------------------------------------------
+
+#define VKI__POSIX_JOB_CONTROL      1
+
+#define VKI__POSIX_VERSION                  200112L
+#define VKI__POSIX2_VERSION                 200112L
+
+#define VKI__POSIX_SPAWN                    200809L
+
+#undef  VKI__POSIX_ADVISORY_INFO
+                                        /* asynchronous I/O is available */
+#define VKI__POSIX_ASYNCHRONOUS_IO          200112L
+                                        /* barriers */
+#define VKI__POSIX_BARRIERS                 200112L
+                                        /* chown requires correct privileges */
+#define VKI__POSIX_CHOWN_RESTRICTED         1
+                                        /* clock selection */
+#define VKI__POSIX_CLOCK_SELECTION          -1
+                                        /* cputime clock */
+#define VKI__POSIX_CPUTIME                  200112L
+                                        /* CPU type */
+#undef  VKI__POSIX_CPUTYPE
+                                        /* file synchronization is available */
+#define VKI__POSIX_FSYNC                    1
+
+                                        /* support IPv6 */                                                                                                   
+#define VKI__POSIX_IPV6                     0
+                                        /* job control is available */
+#define VKI__POSIX_JOB_CONTROL              1
+                                        /* memory mapped files */
+#define VKI__POSIX_MAPPED_FILES             1
+                                        /* memory locking whole address space */
+#define VKI__POSIX_MEMLOCK                  1
+                                        /* memory locking address ranges */
+#define VKI__POSIX_MEMLOCK_RANGE            1                                                                                                                    
+                                        /* memory access protections */
+#define VKI__POSIX_MEMORY_PROTECTION        1
+                                        /* message passing is available */
+#define VKI__POSIX_MESSAGE_PASSING          200112L
+                                        /* monotonic clock */
+#define VKI__POSIX_MONOTONIC_CLOCK          200112L
+                                        /* too-long path comp generate errors */
+#define VKI__POSIX_NO_TRUNC                 1
+
+
+                                        /* prioritized I/O */                                                                                                
+#define VKI__POSIX_PRIORITIZED_IO           -1
+                                        /* priority scheduling */
+#define VKI__POSIX_PRIORITY_SCHEDULING      200112L
+                                        /* raw sockets */
+#define VKI__POSIX_RAW_SOCKETS              200112L
+                                        /* read/write locks */
+#define VKI__POSIX_READER_WRITER_LOCKS      200112L
+                                        /* realtime signals */
+#undef  VKI__POSIX_REALTIME_SIGNALS                                                                                                                              
+                                        /* regular expressions */
+#define VKI__POSIX_REGEXP                   1
+                                        /* semaphores */
+#define VKI__POSIX_SEMAPHORES               0
+                                        /* shared memory objects */
+#define VKI__POSIX_SHARED_MEMORY_OBJECTS    0
+                                        /* shell */
+#define VKI__POSIX_SHELL                    1
+
+
+                                        /* spin locks */                                                                                                     
+#define VKI__POSIX_SPIN_LOCKS               200112L
+                                        /* sporadic server */
+#undef  VKI__POSIX_SPORADIC_SERVER
+                                        /* synchronized I/O is available */
+#define VKI__POSIX_SYNCHRONIZED_IO          1
+                                        /* threads */
+#define VKI__POSIX_THREADS                  200112L
+                                        /* pthread_attr for stack size */
+#define VKI__POSIX_THREAD_ATTR_STACKSIZE    200112L                                                                                                              
+                                        /* pthread_attr for stack address */
+#define VKI__POSIX_THREAD_ATTR_STACKADDR    200112L
+                                        /* thread cputime clock */
+#define VKI__POSIX_THREAD_CPUTIME           200112L
+                                        /* _r functions */
+#define VKI__POSIX_THREAD_PRIO_PROTECT      200112L
+                                        /* PTHREAD_PRIO_PROTECT */
+#define VKI__POSIX_THREAD_SAFE_FUNCTIONS    200112L
+
+                                        /* timeouts */                                                                                                       
+#undef  VKI__POSIX_TIMEOUTS
+                                        /* timers */
+#define VKI__POSIX_TIMERS                   200112L
+                                        /* typed memory objects */
+#undef  VKI__POSIX_TYPED_MEMORY_OBJECTS
+                                        /* may disable terminal spec chars */
+#define VKI__POSIX_VDISABLE                 ((unsigned char)'\377')
+
+                                        /* C binding */                                                                                                      
+#define VKI__POSIX2_C_BIND                  200112L
+
+                                        /* XPG4.2 shared memory */
+#define VKI__XOPEN_SHM                      0
+
+/* access function */
+#define VKI_F_OK            0       /* test for existence of file */
+#define VKI_X_OK            0x01    /* test for execute or search permission */
+#define VKI_W_OK            0x02    /* test for write permission */                                                                                              
+#define VKI_R_OK            0x04    /* test for read permission */
+
+/* whence values for lseek(2) */
+#define VKI_SEEK_SET        0       /* set file offset to offset */
+#define VKI_SEEK_CUR        1       /* set file offset to current plus offset */
+#define VKI_SEEK_END        2       /* set file offset to EOF plus offset */
+
+#define VKI_L_SET           VKI_SEEK_SET
+#define VKI_L_INCR          VKI_SEEK_CUR
+#define VKI_L_XTND          VKI_SEEK_END
+
+#define VKI_FDATASYNC       0x0010  /* sync data and minimal metadata */
+#define VKI_FFILESYNC       0x0020  /* sync data and metadata */
+#define VKI_FDISKSYNC       0x0040  /* flush disk caches after sync */
+
+#define VKI__PC_LINK_MAX             1
+#define VKI__PC_MAX_CANON            2
+#define VKI__PC_MAX_INPUT            3
+#define VKI__PC_NAME_MAX             4
+#define VKI__PC_PATH_MAX             5
+#define VKI__PC_PIPE_BUF             6
+#define VKI__PC_CHOWN_RESTRICTED     7
+#define VKI__PC_NO_TRUNC             8                                                                                                                           
+#define VKI__PC_VDISABLE             9
+#define VKI__PC_SYNC_IO             10
+#define VKI__PC_FILESIZEBITS        11
+#define VKI__PC_SYMLINK_MAX         12
+#define VKI__PC_2_SYMLINKS          13
+#define VKI__PC_ACL_EXTENDED        14
+
+#define VKI__PC_MIN_HOLE_SIZE       15 
+
+#define VKI__SC_ARG_MAX              1
+#define VKI__SC_CHILD_MAX            2
+#define VKI__O_SC_CLK_TCK            3 /* Old version, always 100 */
+#define VKI__SC_NGROUPS_MAX          4
+#define VKI__SC_OPEN_MAX             5
+#define VKI__SC_JOB_CONTROL          6
+#define VKI__SC_SAVED_IDS            7
+#define VKI__SC_VERSION              8
+#define VKI__SC_BC_BASE_MAX          9
+#define VKI__SC_BC_DIM_MAX          10
+#define VKI__SC_BC_SCALE_MAX        11
+#define VKI__SC_BC_STRING_MAX       12
+#define VKI__SC_COLL_WEIGHTS_MAX    13
+#define VKI__SC_EXPR_NEST_MAX       14
+#define VKI__SC_LINE_MAX            15
+#define VKI__SC_RE_DUP_MAX          16
+#define VKI__SC_2_VERSION           17
+#define VKI__SC_2_C_BIND            18
+#define VKI__SC_2_C_DEV             19                                                                                                                           
+#define VKI__SC_2_CHAR_TERM         20
+#define VKI__SC_2_FORT_DEV          21
+#define VKI__SC_2_FORT_RUN          22
+#define VKI__SC_2_LOCALEDEF         23
+#define VKI__SC_2_SW_DEV            24
+#define VKI__SC_2_UPE               25
+#define VKI__SC_STREAM_MAX          26
+#define VKI__SC_TZNAME_MAX          27
+#define VKI__SC_PAGESIZE            28                                                                                                                           
+#define VKI__SC_PAGE_SIZE           VKI__SC_PAGESIZE    /* 1170 compatibility */
+#define VKI__SC_FSYNC               29
+#define VKI__SC_XOPEN_SHM           30
+#define VKI__SC_SYNCHRONIZED_IO     31
+#define VKI__SC_IOV_MAX             32
+#define VKI__SC_MAPPED_FILES        33
+#define VKI__SC_MEMLOCK             34
+#define VKI__SC_MEMLOCK_RANGE       35
+#define VKI__SC_MEMORY_PROTECTION   36                                                                                                                           
+#define VKI__SC_LOGIN_NAME_MAX      37
+#define VKI__SC_MONOTONIC_CLOCK     38
+#define VKI__SC_CLK_TCK             39 /* New, variable version */
+#define VKI__SC_ATEXIT_MAX          40
+#define VKI__SC_THREADS             41
+#define VKI__SC_SEMAPHORES          42
+#define VKI__SC_BARRIERS            43
+#define VKI__SC_TIMERS              44
+#define VKI__SC_SPIN_LOCKS          45                                                                                                                           
+#define VKI__SC_READER_WRITER_LOCKS 46
+#define VKI__SC_GETGR_R_SIZE_MAX    47
+#define VKI__SC_GETPW_R_SIZE_MAX    48
+#define VKI__SC_CLOCK_SELECTION     49
+#define VKI__SC_ASYNCHRONOUS_IO     50
+#define VKI__SC_AIO_LISTIO_MAX      51
+#define VKI__SC_AIO_MAX             52
+#define VKI__SC_MESSAGE_PASSING     53
+#define VKI__SC_MQ_OPEN_MAX         54                                                                                                                           
+#define VKI__SC_MQ_PRIO_MAX         55
+#define VKI__SC_PRIORITY_SCHEDULING 56
+#define VKI__SC_THREAD_DESTRUCTOR_ITERATIONS 57
+#define VKI__SC_THREAD_KEYS_MAX             58
+#define VKI__SC_THREAD_STACK_MIN            59
+#define VKI__SC_THREAD_THREADS_MAX          60
+#define VKI__SC_THREAD_ATTR_STACKADDR       61
+#define VKI__SC_THREAD_ATTR_STACKSIZE       62
+#define VKI__SC_THREAD_PRIORITY_SCHEDULING  63                                                                                                                   
+#define VKI__SC_THREAD_PRIO_INHERIT         64
+#define VKI__SC_THREAD_PRIO_PROTECT         65
+#define VKI__SC_THREAD_PROCESS_SHARED       66
+#define VKI__SC_THREAD_SAFE_FUNCTIONS       67
+#define VKI__SC_TTY_NAME_MAX                68
+#define VKI__SC_HOST_NAME_MAX               69
+#define VKI__SC_PASS_MAX                    70
+#define VKI__SC_REGEXP                      71
+#define VKI__SC_SHELL                       72                                                                                                                   
+#define VKI__SC_SYMLOOP_MAX                 73
+
+/* Actually, they are not supported or implemented yet */
+#define VKI__SC_V6_ILP32_OFF32              74
+#define VKI__SC_V6_ILP32_OFFBIG             75
+#define VKI__SC_V6_LP64_OFF64               76
+#define VKI__SC_V6_LPBIG_OFFBIG             77
+#define VKI__SC_2_PBS                       80
+#define VKI__SC_2_PBS_ACCOUNTING            81                                                                                                                   
+#define VKI__SC_2_PBS_CHECKPOINT            82
+#define VKI__SC_2_PBS_LOCATE                83
+#define VKI__SC_2_PBS_MESSAGE               84
+#define VKI__SC_2_PBS_TRACK                 85
+
+/* These are implemented */
+#define VKI__SC_SPAWN                       86
+#define VKI__SC_SHARED_MEMORY_OBJECTS       87
+#define VKI__SC_TIMER_MAX                   88
+#define VKI__SC_SEM_NSEMS_MAX               89
+#define VKI__SC_CPUTIME                     90
+#define VKI__SC_THREAD_CPUTIME              91
+#define VKI__SC_DELAYTIMER_MAX              92
+#define VKI__SC_SIGQUEUE_MAX                93
+#define VKI__SC_REALTIME_SIGNALS            94
+
+/* Extensions found in Solaris and Linux. */                                                                                                                 
+#define VKI__SC_PHYS_PAGES          121
+
+/* Commonly provided sysconf() extensions */
+#define VKI__SC_NPROCESSORS_CONF    1001
+#define VKI__SC_NPROCESSORS_ONLN    1002
+/* Native variables */
+#define VKI__SC_SCHED_RT_TS         2001
+#define VKI__CS_PATH                 1
+
+//----------------------------------------------------------------------
+// From netinet/in.h
+//----------------------------------------------------------------------
+
+typedef vki___in_addr_t     vki_in_addr_t;
+typedef vki___in_port_t     vki_in_port_t;
+typedef vki___sa_family_t   vki_sa_family_t;
+
+#define VKI_IPPROTO_IP              0               /* dummy for IP */
+#define VKI_IPPROTO_HOPOPTS         0               /* IP6 hop-by-hop options */
+#define VKI_IPPROTO_ICMP            1               /* control message protocol */
+#define VKI_IPPROTO_IGMP            2               /* group mgmt protocol */
+#define VKI_IPPROTO_GGP             3               /* gateway^2 (deprecated) */
+#define VKI_IPPROTO_IPV4            4               /* IP header */
+#define VKI_IPPROTO_IPIP            4               /* IP inside IP */
+#define VKI_IPPROTO_TCP             6               /* tcp */
+#define VKI_IPPROTO_EGP             8               /* exterior gateway protocol */
+#define VKI_IPPROTO_PUP             12              /* pup */
+#define VKI_IPPROTO_UDP             17              /* user datagram protocol */
+#define VKI_IPPROTO_IDP             22              /* xns idp */
+#define VKI_IPPROTO_TP              29              /* tp-4 w/ class negotiation */
+#define VKI_IPPROTO_DCCP            33              /* DCCP */
+#define VKI_IPPROTO_IPV6            41              /* IP6 header */
+#define VKI_IPPROTO_ROUTING         43              /* IP6 routing header */
+#define VKI_IPPROTO_FRAGMENT        44              /* IP6 fragmentation header */
+#define VKI_IPPROTO_RSVP            46              /* resource reservation */
+#define VKI_IPPROTO_GRE             47              /* GRE encaps RFC 1701 */                                                                                    
+#define VKI_IPPROTO_ESP             50              /* encap. security payload */
+#define VKI_IPPROTO_AH              51              /* authentication header */
+#define VKI_IPPROTO_MOBILE          55              /* IP Mobility RFC 2004 */
+#define VKI_IPPROTO_IPV6_ICMP       58              /* IPv6 ICMP */
+#define VKI_IPPROTO_ICMPV6          58              /* ICMP6 */
+#define VKI_IPPROTO_NONE            59              /* IP6 no next header */
+#define VKI_IPPROTO_DSTOPTS         60              /* IP6 destination option */
+#define VKI_IPPROTO_EON             80              /* ISO cnlp */
+#define VKI_IPPROTO_ETHERIP         97              /* Ethernet-in-IP */                                                                                         
+#define VKI_IPPROTO_ENCAP           98              /* encapsulation header */
+#define VKI_IPPROTO_PIM             103             /* Protocol indep. multicast */
+#define VKI_IPPROTO_IPCOMP          108             /* IP Payload Comp. Protocol */
+#define VKI_IPPROTO_VRRP            112             /* VRRP RFC 2338 */
+#define VKI_IPPROTO_CARP            112             /* Common Address Resolution Protocol */
+#define VKI_IPPROTO_L2TP            115             /* L2TPv3 */
+#define VKI_IPPROTO_SCTP            132             /* SCTP */
+#define VKI_IPPROTO_PFSYNC      240     /* PFSYNC */
+#define VKI_IPPROTO_RAW             255             /* raw IP packet */                                                                                          
+#define VKI_IPPROTO_MAX             256
+
+/* last return value of *_input(), meaning "all job for this pkt is done".  */
+#define VKI_IPPROTO_DONE            257
+
+/* sysctl placeholder for (FAST_)IPSEC */
+#define VKI_CTL_IPPROTO_IPSEC       258
+
+#define VKI_IPPORT_RESERVED         1024
+#define VKI_IPPORT_ANONMIN          49152
+#define VKI_IPPORT_ANONMAX          65535
+#define VKI_IPPORT_RESERVEDMIN      600
+#define VKI_IPPORT_RESERVEDMAX      (VKI_IPPORT_RESERVED-1)
+
+struct vki_in_addr {
+        vki_in_addr_t s_addr;
+} __attribute__((__packed__));
+
+#define VKI___IPADDR(x)     ((vki_uint32_t)(x))
+
+#define VKI_IN_CLASSA(i)            (((vki_uint32_t)(i) & VKI___IPADDR(0x80000000)) == \
+                                 VKI___IPADDR(0x00000000))
+#define VKI_IN_CLASSA_NET           VKI___IPADDR(0xff000000)
+#define VKI_IN_CLASSA_NSHIFT        24                                                                                                                           
+#define VKI_IN_CLASSA_HOST          VKI___IPADDR(0x00ffffff)
+#define VKI_IN_CLASSA_MAX           128
+
+#define VKI_IN_CLASSB(i)            (((vki_uint32_t)(i) & VKI___IPADDR(0xc0000000)) == \
+                                 VKI___IPADDR(0x80000000))
+#define VKI_IN_CLASSB_NET           VKI___IPADDR(0xffff0000)
+#define VKI_IN_CLASSB_NSHIFT        16
+#define VKI_IN_CLASSB_HOST          VKI___IPADDR(0x0000ffff)
+
+#define VKI_IN_CLASSB_MAX           65536                                                                                                                        
+
+#define VKI_IN_CLASSC(i)            (((vki_uint32_t)(i) & VKI___IPADDR(0xe0000000)) == \
+                                 VKI___IPADDR(0xc0000000))
+#define VKI_IN_CLASSC_NET           VKI___IPADDR(0xffffff00)
+#define VKI_IN_CLASSC_NSHIFT        8
+#define VKI_IN_CLASSC_HOST          VKI___IPADDR(0x000000ff)
+
+#define VKI_IN_CLASSD(i)            (((vki_uint32_t)(i) & VKI___IPADDR(0xf0000000)) == \
+                                 VKI___IPADDR(0xe0000000))                                                                                                       
+/* These ones aren't really net and host fields, but routing needn't know. */
+#define VKI_IN_CLASSD_NET           VKI___IPADDR(0xf0000000)
+#define VKI_IN_CLASSD_NSHIFT        28
+#define VKI_IN_CLASSD_HOST          VKI___IPADDR(0x0fffffff)
+#define VKI_IN_MULTICAST(i)         VKI_IN_CLASSD(i)
+
+#define VKI_IN_EXPERIMENTAL(i)      (((vki_uint32_t)(i) & VKI___IPADDR(0xf0000000)) == \
+                                 VKI___IPADDR(0xf0000000))
+
+#define VKI_IN_BADCLASS(i)          (((vki_uint32_t)(i) & VKI___IPADDR(0xf0000000)) == \
+                                 VKI___IPADDR(0xf0000000))
+
+#define VKI_IN_LINKLOCAL(i) (((vki_uint32_t)(i) & VKI___IPADDR(0xffff0000)) == \
+                         VKI___IPADDR(0xa9fe0000))
+
+#define VKI_IN_PRIVATE(i)   ((((vki_uint32_t)(i) & VKI___IPADDR(0xff000000)) ==     \
+                          VKI___IPADDR(0x0a000000)) ||                      \
+                         (((vki_uint32_t)(i) & VKI___IPADDR(0xfff00000)) ==     \
+                          VKI___IPADDR(0xac100000)) ||                      \
+                         (((vki_uint32_t)(i) & VKI___IPADDR(0xffff0000)) ==     \
+                          VKI___IPADDR(0xc0a80000)))
+
+#define VKI_IN_LOCAL_GROUP(i)       (((vki_uint32_t)(i) & VKI___IPADDR(0xffffff00)) == \
+                                 VKI___IPADDR(0xe0000000))
+
+#define VKI_IN_ANY_LOCAL(i)         (VKI_IN_LINKLOCAL(i) || VKI_IN_LOCAL_GROUP(i))
+
+#define VKI_INADDR_ANY              VKI___IPADDR(0x00000000)                                                                                                         
+#define VKI_INADDR_LOOPBACK         VKI___IPADDR(0x7f000001)
+#define VKI_INADDR_BROADCAST        VKI___IPADDR(0xffffffff)    /* must be masked */
+#define VKI_INADDR_NONE             VKI___IPADDR(0xffffffff)    /* -1 return */
+
+#define VKI_INADDR_UNSPEC_GROUP     VKI___IPADDR(0xe0000000)    /* 224.0.0.0 */
+#define VKI_INADDR_ALLHOSTS_GROUP   VKI___IPADDR(0xe0000001)    /* 224.0.0.1 */
+#define VKI_INADDR_ALLRTRS_GROUP    VKI___IPADDR(0xe0000002)    /* 224.0.0.2 */
+#define VKI_INADDR_CARP_GROUP       VKI___IPADDR(0xe0000012)    /* 224.0.0.18 */
+#define VKI_INADDR_MAX_LOCAL_GROUP  VKI___IPADDR(0xe00000ff)    /* 224.0.0.255 */                                                                                    
+
+#define VKI_IN_LOOPBACKNET          127                     /* official! */
+
+struct vki_sockaddr_in {
+        vki_uint8_t         sin_len;
+        vki_sa_family_t     sin_family;
+        vki_in_port_t       sin_port;
+        struct vki_in_addr  sin_addr;
+        vki_int8_t        sin_zero[8];
+};
+
+#define VKI_INET_ADDRSTRLEN                 16
+
+struct vki_ip_opts {
+        struct vki_in_addr  ip_dst;         /* first hop, 0 w/o src rt */
+        vki_int8_t        ip_opts[40];    /* actually variable in size */
+};
+
+#define VKI_IP_OPTIONS              1    /* buf/ip_opts; set/get IP options */
+#define VKI_IP_HDRINCL              2    /* int; header is included with data */
+#define VKI_IP_TOS                  3    /* int; IP type of service and preced. */
+#define VKI_IP_TTL                  4    /* int; IP time to live */
+#define VKI_IP_RECVOPTS             5    /* bool; receive all IP opts w/dgram */
+#define VKI_IP_RECVRETOPTS          6    /* bool; receive IP opts for response */
+#define VKI_IP_RECVDSTADDR          7    /* bool; receive IP dst addr w/dgram */
+#define VKI_IP_RETOPTS              8    /* ip_opts; set/get IP options */
+#define VKI_IP_MULTICAST_IF         9    /* in_addr; set/get IP multicast i/f  */                                                                                
+#define VKI_IP_MULTICAST_TTL        10   /* u_char; set/get IP multicast ttl */
+#define VKI_IP_MULTICAST_LOOP       11   /* u_char; set/get IP multicast loopback */
+/* The add and drop membership option numbers need to match with the v6 ones */
+#define VKI_IP_ADD_MEMBERSHIP       12   /* ip_mreq; add an IP group membership */
+#define VKI_IP_DROP_MEMBERSHIP      13   /* ip_mreq; drop an IP group membership */
+#define VKI_IP_PORTALGO             18   /* int; port selection algo (rfc6056) */
+#define VKI_IP_PORTRANGE            19   /* int; range to use for ephemeral port */
+#define VKI_IP_RECVIF               20   /* bool; receive reception if w/dgram */
+
+#define VKI_IP_ERRORMTU             21   /* int; get MTU of last xmit = EMSGSIZE */                                                                              
+#define VKI_IP_IPSEC_POLICY         22   /* struct; get/set security policy */
+#define VKI_IP_RECVTTL              23   /* bool; receive IP TTL w/dgram */
+#define VKI_IP_MINTTL               24   /* minimum TTL for packet or drop */
+#define VKI_IP_PKTINFO              25   /* struct; set default src if/addr */
+#define VKI_IP_RECVPKTINFO          26   /* int; receive dst if/addr w/dgram */
+
+#define VKI_IP_SENDSRCADDR VKI_IP_RECVDSTADDR /* FreeBSD compatibility */
+
+/*                                                                                                                                                           
+ * Information sent in the control message of a datagram socket for
+ * IP_PKTINFO and IP_RECVPKTINFO.
+ */
+struct vki_in_pktinfo {
+        struct vki_in_addr  ipi_addr;       /* src/dst address */
+        unsigned int ipi_ifindex;       /* interface index */
+};
+
+#define ipi_spec_dst ipi_addr   /* Solaris/Linux compatibility */                                                                                            
+
+/*
+ * Defaults and limits for options
+ */
+#define VKI_IP_DEFAULT_MULTICAST_TTL  1     /* normally limit m'casts to 1 hop  */
+#define VKI_IP_DEFAULT_MULTICAST_LOOP 1     /* normally hear sends if a member  */
+#define VKI_IP_MAX_MEMBERSHIPS      20      /* per socket; must fit in one mbuf */
+
+/*                                                                                                                                                           
+ * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
+ */
+struct vki_ip_mreq {
+        struct  vki_in_addr imr_multiaddr;  /* IP multicast address of group */
+        struct  vki_in_addr imr_interface;  /* local IP address of interface */
+};
+
+#define VKI_IP_PORTRANGE_DEFAULT    0       /* default range */
+#define VKI_IP_PORTRANGE_HIGH       1       /* same as DEFAULT (FreeBSD compat) */
+#define VKI_IP_PORTRANGE_LOW        2       /* use privileged range */
+
+#define VKI_IPCTL_FORWARDING        1       /* act as router */                                                                                                  
+#define VKI_IPCTL_SENDREDIRECTS     2       /* may send redirects when forwarding */
+#define VKI_IPCTL_DEFTTL            3       /* default TTL */
+/* IPCTL_DEFMTU=4, never implemented */
+#define VKI_IPCTL_FORWSRCRT         5       /* forward source-routed packets */
+#define VKI_IPCTL_DIRECTEDBCAST     6       /* default broadcast behavior */
+#define VKI_IPCTL_ALLOWSRCRT        7       /* allow/drop all source-routed pkts */
+#define VKI_IPCTL_SUBNETSARELOCAL   8       /* treat subnets as local addresses */
+#define VKI_IPCTL_MTUDISC           9       /* allow path MTU discovery */
+
+#define VKI_IPCTL_ANONPORTMIN      10       /* minimum ephemeral port */                                                                                         
+#define VKI_IPCTL_ANONPORTMAX      11       /* maximum ephemeral port */
+#define VKI_IPCTL_MTUDISCTIMEOUT   12       /* allow path MTU discovery */
+#define VKI_IPCTL_MAXFLOWS         13       /* maximum ip flows allowed */
+#define VKI_IPCTL_HOSTZEROBROADCAST 14      /* is host zero a broadcast addr? */
+#define VKI_IPCTL_GIF_TTL          15       /* default TTL for gif encap packet */
+#define VKI_IPCTL_LOWPORTMIN       16       /* minimum reserved port */
+#define VKI_IPCTL_LOWPORTMAX       17       /* maximum reserved port */
+#define VKI_IPCTL_MAXFRAGPACKETS   18       /* max packets reassembly queue */
+
+#define VKI_IPCTL_GRE_TTL          19       /* default TTL for gre encap packet */                                                                               
+#define VKI_IPCTL_CHECKINTERFACE   20       /* drop pkts in from 'wrong' iface */
+#define VKI_IPCTL_IFQ              21       /* IP packet input queue */
+#define VKI_IPCTL_RANDOMID         22       /* use random IP ids (if configured) */
+#define VKI_IPCTL_LOOPBACKCKSUM    23       /* do IP checksum on loopback */
+#define VKI_IPCTL_STATS             24      /* IP statistics */
+#define VKI_IPCTL_DAD_COUNT        25       /* DAD packets to send */
+
+#endif // __VKI_NETBSD_H
+
+/*--------------------------------------------------------------------*/
+/*--- end                                                          ---*/
+/*--------------------------------------------------------------------*/
