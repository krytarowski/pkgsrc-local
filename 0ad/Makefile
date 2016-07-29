# $NetBSD$

DISTNAME=	0ad-0.0.20-alpha-unix-build
PKGNAME=	${DISTNAME:S/-unix-build//:S/-alpha/alpha/}
CATEGORIES=	games
MASTER_SITES=	http://releases.wildfiregames.com/
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://releases.wildfiregames.com/
COMMENT=	TODO: Short description of the package
LICENSE=	gnu-gpl-v2 AND gnu-lgpl-v2.1

WRKSRC=		${WRKDIR}/${DISTNAME:S/-unix-build//}
USE_LANGUAGES=	c c++

USE_TOOLS+=	gmake

.include "../../mk/bsd.pkg.mk"
