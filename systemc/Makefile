# $NetBSD$

GITHUB_PROJECT=	SystemC
DISTNAME=	v2.3.1
PKGNAME=	${GITHUB_PROJECT}-${DISTNAME}
CATEGORIES=	local
MASTER_SITES=	${MASTER_SITE_GITHUB:=ArchC/}
EXTRACT_SUFX=	.zip
DIST_SUBDIR=	${GITHUB_PROJECT}

MAINTAINER=	INSERT_YOUR_MAIL_ADDRESS_HERE
HOMEPAGE=	https://github.com/ArchC/SystemC/
COMMENT=	TODO: Short description of the package
#LICENSE=	# TODO: (see mk/license.mk)

WRKSRC=		${WRKDIR}/SystemC-2.3.1
GNU_CONFIGURE=	yes
USE_TOOLS+=	pkg-config
USE_LANGUAGES=	c c++

PKGCONFIG_OVERRIDE+=	src/sysc/systemc.pc.in
PKGCONFIG_OVERRIDE+=	src/tlm_core/tlm.pc.in

.include "../../mk/bsd.pkg.mk"
