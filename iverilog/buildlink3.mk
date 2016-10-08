# $NetBSD$

BUILDLINK_TREE+=	iverilog

.if !defined(IVERILOG_BUILDLINK3_MK)
IVERILOG_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.iverilog+=	iverilog>=10.1
BUILDLINK_PKGSRCDIR.iverilog?=	../../local/iverilog
.endif	# IVERILOG_BUILDLINK3_MK

BUILDLINK_TREE+=	-iverilog
