$NetBSD$

--- vl.c.orig	2019-04-23 18:14:46.000000000 +0000
+++ vl.c
@@ -3643,7 +3643,8 @@ int main(int argc, char **argv, char **e
                                                      optarg, true);
                 optarg = qemu_opt_get(accel_opts, "accel");
                 if (!optarg || is_help_option(optarg)) {
-                    error_printf("Possible accelerators: kvm, xen, hax, tcg\n");
+                    error_printf("Possible accelerators: "
+                        "kvm, xen, hax, nvmm, tcg\n");
                     exit(0);
                 }
                 opts = qemu_opts_create(qemu_find_opts("machine"), NULL,
