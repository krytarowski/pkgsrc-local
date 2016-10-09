# $NetBSD$

GITHUB_PROJECT=	ArchC
DISTNAME=	ArchC-2.4.1
PKGNAME=	${DISTNAME:tl}
CATEGORIES=	cad
MASTER_SITES=	${MASTER_SITE_GITHUB:=ArchC/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	INSERT_YOUR_MAIL_ADDRESS_HERE
HOMEPAGE=	https://github.com/ArchC/ArchC/
COMMENT=	TODO: Short description of the package
#LICENSE=	# TODO: (see mk/license.mk)

WRKSRC=		${WRKDIR}/ArchC-2.4.1
USE_TOOLS+=	pkg-config
USE_LANGUAGES=	c c++

PKGCONFIG_OVERRIDE+=	pc/archc.pc.in
PKGCONFIG_OVERRIDE+=	pc/powersc.pc.in

.include "../../mk/bsd.pkg.mk"
