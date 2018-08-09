$NetBSD$

--- cmdline.c.orig	2018-08-09 01:52:21.908677192 +0000
+++ cmdline.c
@@ -384,6 +384,34 @@ bool cmdlineParse(int argc, char* argv[]
                 .kernelOnly = false,
                 .useClone = true,
             },
+        /* NetBSD code */
+        .netbsd =
+            {
+                .exeFd = -1,
+                .hwCnts =
+                    {
+                        .cpuInstrCnt = 0ULL,
+                        .cpuBranchCnt = 0ULL,
+                        .bbCnt = 0ULL,
+                        .newBBCnt = 0ULL,
+                        .softCntPc = 0ULL,
+                        .softCntCmp = 0ULL,
+                    },
+                .dynamicCutOffAddr = ~(0ULL),
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
+                .kernelOnly = false,
+            },
     };
 
     TAILQ_INIT(&hfuzz->io.dynfileq);
@@ -671,6 +699,38 @@ bool cmdlineParse(int argc, char* argv[]
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
+            case 0x503:
+                hfuzz->netbsd.dynamicCutOffAddr = strtoull(optarg, NULL, 0);
+                break;
+            case 0x504:
+                hfuzz->netbsd.symsBlFile = optarg;
+                break;
+            case 0x505:
+                hfuzz->netbsd.symsWlFile = optarg;
+                break;
+            case 0x510:
+                hfuzz->feedback.dynFileMethod |= _HF_DYNFILE_INSTR_COUNT;
+                break;
+            case 0x511:
+                hfuzz->feedback.dynFileMethod |= _HF_DYNFILE_BRANCH_COUNT;
+                break;
+            case 0x513:
+                hfuzz->feedback.dynFileMethod |= _HF_DYNFILE_BTS_EDGE;
+                break;
+            case 0x514:
+                hfuzz->feedback.dynFileMethod |= _HF_DYNFILE_IPT_BLOCK;
+                break;
+            case 0x515:
+                hfuzz->netbsd.kernelOnly = true;
+                break;
+#endif /* defined(_HF_ARCH_NETBSD) */
             default:
                 cmdlineUsage(argv[0], custom_opts);
                 return false;
