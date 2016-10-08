# $NetBSD$
# XXX
# XXX This file was created automatically using createbuildlink-3.17.
# XXX After this file has been verified as correct, the comment lines
# XXX beginning with "XXX" should be removed.  Please do not commit
# XXX unverified buildlink3.mk files.
# XXX
# XXX Packages that only install static libraries or headers should
# XXX include the following line:
# XXX
# XXX	BUILDLINK_DEPMETHOD.iverilog?=	build

BUILDLINK_TREE+=	iverilog

.if !defined(IVERILOG_BUILDLINK3_MK)
IVERILOG_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.iverilog+=	iverilog>=10.1
BUILDLINK_PKGSRCDIR.iverilog?=	../../local/iverilog
.endif	# IVERILOG_BUILDLINK3_MK

BUILDLINK_TREE+=	-iverilog
