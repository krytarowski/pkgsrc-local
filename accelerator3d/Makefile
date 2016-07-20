# $NetBSD$

DISTNAME=	accelerator-0.1.1
PKGNAME=	${DISTNAME:S/accelerator/accelerator3d/}
CATEGORIES=	games
MASTER_SITES=	https://sourceforge.net/projects/accelerator3d/files/accelerator/0.1.1/
EXTRACT_SUFX=	.zip

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://sourceforge.net/projects/accelerator3d/files/accelerator/0.1.1/
COMMENT=	Fast-paced, 3D, first-person shoot/dodge-'em-up
LICENSE=	artistic

WRKSRC=		${WRKDIR}/${PKGBASE}
USE_LANGUAGES=	# none

DEPENDS+=	${PYPKGPREFIX}-game-[0-9]*:../../devel/py-game
DEPENDS+=	${PYPKGPREFIX}-ode-[0-9]*:../../wip/py-ode
DEPENDS+=	${PYPKGPREFIX}-OpenGL-[0-9]*:../../graphics/py-OpenGL

REPLACE_PYTHON+=	accelerator.py

NO_BUILD=	yes

.include "../../lang/python/application.mk"
.include "../../lang/python/pyversion.mk"
.include "../../mk/bsd.pkg.mk"
