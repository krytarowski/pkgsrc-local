# $NetBSD$

DISTNAME=	ptex-2.1.28
CATEGORIES=	graphics
MASTER_SITES=	${MASTER_SITE_GITHUB:=wdas/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://ptex.us/
COMMENT=	Per-Face Texture Mapping for Production Rendering
LICENSE=	modified-bsd # with slightly changes spelling

USE_CMAKE=	yes
USE_LANGUAGES=	c c++

BUILDLINK_TRANSFORM+=	opt:-std=c++98:-std=gnu++98 # alloca(3)

.include "../../mk/bsd.pkg.mk"
