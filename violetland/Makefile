# $NetBSD$

DISTNAME=	violetland-0.5
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_GITHUB:=ooxi/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://violetland.github.io/
COMMENT=	Help a girl by name of Violet to struggle with monsters
LICENSE=	gnu-gpl-v3 AND cc-by-sa-v3.0

USE_CMAKE=	yes
USE_TOOLS+=	intltool
USE_LANGUAGES=	c c++

.include "../../devel/boost-libs/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
