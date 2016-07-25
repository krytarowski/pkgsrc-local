# $NetBSD$

DISTNAME=	btanks-0.9.8083
CATEGORIES=	local
MASTER_SITES=	https://sourceforge.net/projects/btanks/files/btanks-source/
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	INSERT_YOUR_MAIL_ADDRESS_HERE
HOMEPAGE=	https://sourceforge.net/projects/btanks/files/btanks-source/
COMMENT=	TODO: Short description of the package
#LICENSE=	# TODO: (see mk/license.mk)

USE_LANGUAGES=	c c++
USE_TOOLS+=	pkg-config

BUILD_DEPENDS+=	scons-[0-9]*:../../devel/scons

do-build:
	cd ${WRKSRC} && \
	${SETENV} ${MAKE_ENV} ${PREFIX}/bin/scons

do-install:
	cd ${WRKSRC} && \
	${SETENV} ${INSTALL_ENV} ${PREFIX}/bin/scons install prefix=${DESTDIR}${PREFIX}

.include "../../lang/lua51/buildlink3.mk"
.include "../../audio/libvorbis/buildlink3.mk"
.include "../../graphics/SDL_image/buildlink3.mk"
.include "../../devel/SDL_gfx/buildlink3.mk"
.include "../../multimedia/smpeg/buildlink3.mk"
.include "../../devel/SDL/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
