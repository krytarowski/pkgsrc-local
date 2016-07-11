# $NetBSD: Makefile,v 1.14 2012/09/24 18:26:53 asau Exp $

DISTNAME=	chromium-51.0.2704.103
PKGNAME=	${DISTNAME:S/chromium/chromium-browser/}
CATEGORIES=	www
MASTER_SITES=	http://commondatastorage.googleapis.com/chromium-browser-official/
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://dev.chromium.org/Home
COMMENT=	Open-source browser project
LICENSE=	modified-bsd

USE_TOOLS+=	bash bison flex gmake pax perl pkg-config
USE_LANGUAGES=	c c++

BUILD_DEPENDS+=	gperf-[0-9]*:../../devel/gperf
BUILD_DEPENDS+=	yasm-[0-9]*:../../devel/yasm

ONLY_FOR_PLATFORM=	*-*-arm *-*-i386 *-*-x86_64

.include "../../mk/bsd.prefs.mk"

.if ${OPSYS} == "Linux" || ${OPSYS} == "DragonFly" || ${OPSYS} == "FreeBSD" || ${OPSYS} == "NetBSD"
.include "../../audio/alsa-lib/buildlink3.mk"
.endif

REPLACE_PYTHON+=	tools/gn/bootstrap/bootstrap.py

# Chromium builds better with Clang
PKGSRC_COMPILER=	clang
PKG_CC=			clang
PKG_CXX=		clang++
CXXFLAGS+=		-std=gnu++11

pre-configure:
	${RUN} cd ${WRKSRC} && ${PKGSRC_SETENV} ${MAKE_ENV} ${PYTHONBIN} ./tools/gn/bootstrap/bootstrap.py

.include "../../devel/GConf/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/libevent/buildlink3.mk"
.include "../../devel/nss/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../lang/python/pyversion.mk"
.include "../../lang/python/application.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../multimedia/libvpx/buildlink3.mk"
.include "../../textproc/libxslt/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../x11/libXScrnSaver/buildlink3.mk"
.include "../../x11/libXtst/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
