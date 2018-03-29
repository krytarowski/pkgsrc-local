# $NetBSD$

DISTNAME=	dynamorio-7.0.0
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=DynamoRIO/}
#GITHUB_TAG=	release_${PKGVERSION_NOREV:S/./_/g}
GITHUB_TAG=	998da669f4653e2fce5e9a33c01ea6d076d12d33 # Sat, 24 Mar 2018 16:04:13 -0400

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/DynamoRIO/dynamorio/
COMMENT=	Dynamic Instrumentation Tool Platform
LICENSE=	modified-bsd

USE_CMAKE=	yes
USE_TOOLS+=	perl
USE_LANGUAGES+=	c c++

# Hack in CMakeLists.txt to workaround warning for cpp -E
#BUILDLINK_TRANSFORM+=	rm:-E

.include "../../graphics/ImageMagick/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
