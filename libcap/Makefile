# $NetBSD$

DISTNAME=	libcap-2.25
CATEGORIES=	local
MASTER_SITES=	https://www.kernel.org/pub/linux/libs/security/linux-privs/libcap2/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://sites.google.com/site/fullycapable/
COMMENT=	Library for getting and setting POSIX.1e capabilities
LICENSE=	gnu-gpl-v2

USE_TOOLS+=	pkg-config gmake perl

#ONLY_FOR_PLATFORM=	Linux-*-*

PKGCONFIG_OVERRIDE+=	libcap/libcap.pc.in

MAKE_FLAGS+=	prefix=${PREFIX}
MAKE_FLAGS+= 	lib=${PREFIX}/lib
MAKE_FLAGS+=	LIBDIR=${PREFIX}/lib
MAKE_FLAGS+=	SBINDIR=${PREFIX}/sbin
MAKE_FLAGS+=	INCDIR=${PREFIX}/include
MAKE_FLAGS+=	MANDIR=${PREFIX}/${PKGMANDIR}
MAKE_FLAGS+=	PKGCONFDIR=${PREFIX}/lib/pkgconfig

#MAKE_INSTALL_FLAGS+=	RAISE_SETFCAP=no
MAKE_INSTALL_FLAGS+=	DESTDIR=%{DESTDIR}

PKG_DESTDIR_SUPPORT=	destdir
PRIVILEGED_STAGES+=	install

.include "../../mk/bsd.pkg.mk"
