# $NetBSD$

DISTNAME=	dynamorio-7.0.0.rc1
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=DynamoRIO/}
GITHUB_TAG=	release_${PKGVERSION_NOREV:S/./_/g}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/DynamoRIO/dynamorio/
COMMENT=	Dynamic Instrumentation Tool Platform
LICENSE=	modified-bsd

USE_CMAKE=	yes
USE_TOOLS+=	perl
USE_LANGUAGES+=	c c++

.include "../../graphics/ImageMagick/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
