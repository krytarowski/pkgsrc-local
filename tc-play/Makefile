# $NetBSD$

DISTNAME=	tc-play-2.0
CATEGORIES=	security
MASTER_SITES=	${MASTER_SITE_GITHUB:=bwalex/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/bwalex/tc-play/
COMMENT=	Free and simple TrueCrypt Implementation based on dm-crypt
LICENSE=	2-clause-bsd

USE_CMAKE=	yes
USE_TOOLS+=	pkg-config
USE_LANGUAGES=	c c++

.include "../../devel/libuuid/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
