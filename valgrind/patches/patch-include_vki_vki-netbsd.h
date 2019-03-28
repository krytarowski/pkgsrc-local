$NetBSD$

--- include/vki/vki-netbsd.h.orig	2019-03-28 13:36:58.539662750 +0000
+++ include/vki/vki-netbsd.h
@@ -0,0 +1,699 @@
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
+#endif // __VKI_NETBSD_H
+
+/*--------------------------------------------------------------------*/
+/*--- end                                                          ---*/
+/*--------------------------------------------------------------------*/
