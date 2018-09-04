$NetBSD$

--- src/x86_64/ucontext_i.h.orig	2018-09-04 09:38:02.000000000 +0000
+++ src/x86_64/ucontext_i.h
@@ -78,5 +78,32 @@ WITH THE SOFTWARE OR THE USE OR OTHER DE
 #define UC_MCONTEXT_FPOWNED_FPU 0x20001
 #define UC_MCONTEXT_FPFMT_XMM   0x10002
 #define UC_MCONTEXT_MC_LEN_VAL  0x320
+#elif defined __NetBSD__
+#define UC_SIGMASK              0x10
+#define UC_MCONTEXT_GREGS_RDI   0x38
+#define UC_MCONTEXT_GREGS_RSI   0x40
+#define UC_MCONTEXT_GREGS_RDX   0x48
+#define UC_MCONTEXT_GREGS_RCX   0x50
+#define UC_MCONTEXT_GREGS_R8    0x58
+#define UC_MCONTEXT_GREGS_R9    0x60
+#define UC_MCONTEXT_GREGS_RAX   0xa8
+#define UC_MCONTEXT_GREGS_RBX   0xa0
+#define UC_MCONTEXT_GREGS_RBP   0x98
+#define UC_MCONTEXT_GREGS_R10   0x68
+#define UC_MCONTEXT_GREGS_R11   0x70
+#define UC_MCONTEXT_GREGS_R12   0x78
+#define UC_MCONTEXT_GREGS_R13   0x80
+#define UC_MCONTEXT_GREGS_R14   0x88
+#define UC_MCONTEXT_GREGS_R15   0x90
+#define UC_MCONTEXT_FS          0xb8
+#define UC_MCONTEXT_GS          0xb0
+#define UC_MCONTEXT_ES          0xc0
+#define UC_MCONTEXT_DS          0xc8
+#define UC_MCONTEXT_GREGS_RIP   0xe0
+#define UC_MCONTEXT_CS          0xe8
+#define UC_MCONTEXT_RFLAGS      0xf0
+#define UC_MCONTEXT_GREGS_RSP   0xf8
+#define UC_MCONTEXT_SS          0x100
+#define UC_MCONTEXT_FPREGS      0x110
 
 #endif
