$NetBSD$

--- cmdline.c.orig	2018-08-10 21:05:24.767249104 +0000
+++ cmdline.c
@@ -384,6 +384,22 @@ bool cmdlineParse(int argc, char* argv[]
                 .kernelOnly = false,
                 .useClone = true,
             },
+        /* NetBSD code */
+        .netbsd =
+            {
+                .disableRandomization = true,
+                .ignoreAddr = NULL,
+                .numMajorFrames = 7,
+                .pid = 0,
+                .pidFile = NULL,
+                .pidCmd = {},
+                .symsBlFile = NULL,
+                .symsBlCnt = 0,
+                .symsBl = NULL,
+                .symsWlFile = NULL,
+                .symsWlCnt = 0,
+                .symsWl = NULL,
+            },
     };
 
     TAILQ_INIT(&hfuzz->io.dynfileq);
@@ -452,6 +468,15 @@ bool cmdlineParse(int argc, char* argv[]
         { { "linux_ns_pid", no_argument, NULL, 0x0531 }, "Use Linux PID namespace isolation" },
         { { "linux_ns_ipc", no_argument, NULL, 0x0532 }, "Use Linux IPC namespace isolation" },
 #endif // defined(_HF_ARCH_LINUX)
+
+#if defined(_HF_ARCH_NETBSD)
+        { { "netbsd_symbols_bl", required_argument, NULL, 0x504 }, "Symbols blacklist filter file (one entry per line)" },
+        { { "netbsd_symbols_wl", required_argument, NULL, 0x505 }, "Symbols whitelist filter file (one entry per line)" },
+        { { "netbsd_pid", required_argument, NULL, 'p' }, "Attach to a pid (and its thread group)" },
+        { { "netbsd_file_pid", required_argument, NULL, 0x502 }, "Attach to pid (and its thread group) read from file" },
+        { { "netbsd_addr_low_limit", required_argument, NULL, 0x500 }, "Address limit (from si.si_addr) below which crashes are not reported, (default: 0)" },
+        { { "netbsd_keep_aslr", no_argument, NULL, 0x501 }, "Don't disable ASLR randomization, might be useful with MSAN" },
+#endif // defined(_HF_ARCH_NETBSD)
         { { 0, 0, 0, 0 }, NULL },
     };
     // clang-format on
@@ -671,6 +696,20 @@ bool cmdlineParse(int argc, char* argv[]
                 hfuzz->linux.cloneFlags |= (CLONE_NEWUSER | CLONE_NEWIPC);
                 break;
 #endif /* defined(_HF_ARCH_LINUX) */
+#if defined(_HF_ARCH_NETBSD)
+            case 0x500:
+                hfuzz->netbsd.ignoreAddr = (void*)strtoul(optarg, NULL, 0);
+                break;
+            case 0x501:
+                hfuzz->netbsd.disableRandomization = false;
+                break;
+            case 0x504:
+                hfuzz->netbsd.symsBlFile = optarg;
+                break;
+            case 0x505:
+                hfuzz->netbsd.symsWlFile = optarg;
+                break;
+#endif /* defined(_HF_ARCH_NETBSD) */
             default:
                 cmdlineUsage(argv[0], custom_opts);
                 return false;
