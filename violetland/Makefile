# $NetBSD$

DISTNAME=	violetland-0.5
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_GITHUB:=ooxi/}

CMAKEGETTEXT_GIT=	6ee6405ac4d5edf0c31bb42c079a3b63421bb4f5
FCITX_GIT=		a636a83ec385ab9b2dd003c3c7c5bff7ab75f261

DISTFILES+=	${CMAKEGETTEXT_GIT}.zip
DISTFILES+=	${FCITX_GIT}.zip

SITES.${CMAKEGETTEXT_GIT}.zip+=	https://github.com/jarro2783/CMake-Gettext/archive/
SITES.${FCITX_GIT}.zip+=	https://github.com/fcitx/fcitx/archive/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://violetland.github.io/
COMMENT=	Help a girl by name of Violet to struggle with monsters
LICENSE=	gnu-gpl-v3 AND cc-by-sa-v3.0

USE_CMAKE=	yes
#USE_TOOLS+=	intltool
USE_LANGUAGES=	c c++

.include "../../devel/boost-libs/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
