# $NetBSD$

DISTNAME=	gemrb-0.8.4
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_GITHUB:=gemrb/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://gemrb.org/
COMMENT=	Engine Made with preRendered Background
LICENSE=	gnu-gpl-v2

USE_CMAKE=	yes

USE_LANGUAGES=	c c++

CONFIGURE_DIRS=	${WRKDIR}/build
CMAKE_ARG_PATH=	${WRKSRC}
CMAKE_ARGS+=	-DUSE_SDL2:BOOL=TRUE

post-extract:
	${RUN} mkdir -p ${WRKDIR}/build

.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../graphics/freetype2/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../audio/openal-soft/buildlink3.mk"
.include "../../audio/libvorbis/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../audio/SDL2_mixer/buildlink3.mk"
.include "../../devel/SDL2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
