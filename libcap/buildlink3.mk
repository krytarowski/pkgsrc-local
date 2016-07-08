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
# XXX	BUILDLINK_DEPMETHOD.libcap?=	build

BUILDLINK_TREE+=	libcap

.if !defined(LIBCAP_BUILDLINK3_MK)
LIBCAP_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libcap+=	libcap>=2.25
BUILDLINK_PKGSRCDIR.libcap?=	../../local/libcap
.endif	# LIBCAP_BUILDLINK3_MK

BUILDLINK_TREE+=	-libcap
