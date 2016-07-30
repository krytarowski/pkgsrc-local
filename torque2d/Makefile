# $NetBSD$

DISTNAME=	Torque2D-3.3
PKGNAME=	${DISTNAME:tl}
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=GarageGames/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://torque2d.org/
COMMENT=	Open Source version of Torque 3D from GarageGames
LICENSE=	mit

USE_LANGUAGES=	c c++
USE_TOOLS+=	gmake

BUILD_DIRS=	engine/compilers/Make

.include "../../mk/jpeg.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
