# $NetBSD$

GITHUB_PROJECT=	OpenSubdiv
DISTNAME=	OpenSubdiv-3.1.0.RC2
PKGNAME=	${DISTNAME:tl}
CATEGORIES=	multimedia
MASTER_SITES=	${MASTER_SITE_GITHUB:=PixarAnimationStudios/}
GITHUB_TAG=	v${PKGVERSION_NOREV:S/./_/g:tu}

# https://github.com/PixarAnimationStudios/OpenSubdiv/archive/v3-1.0.rc2.tar.gz
# https://github.com/PixarAnimationStudios/OpenSubdiv/archive/v3-1.0.RC2.tar.gz
# https://github.com/PixarAnimationStudios/OpenSubdiv/archive/v3-1-0-RC2.tar.gz
# https://github.com/PixarAnimationStudios/OpenSubdiv/archive/v3_1_0_RC2.zip

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://graphics.pixar.com/opensubdiv/docs/intro.html
COMMENT=	High performance subdivision surface for parallel architectures
LICENSE=	apache-2.0

USE_CMAKE=	yes
USE_LANGUAGES=	c c++

.include "../../mk/bsd.pkg.mk"
