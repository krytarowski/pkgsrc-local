# $NetBSD$

DISTNAME=	brlcad-7.24.2
CATEGORIES=	cad
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=brlcad/}
# https://sourceforge.net/projects/brlcad/files/BRL-CAD%20Source/7.24.2/brlcad-7.24.2.tar.gz/download

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://brlcad.org/
COMMENT=	Open source cross-platform solid modeling system
#LICENSE=	# TODO: (see mk/license.mk)

USE_LANGUAGES=	c c++
USE_CMAKE=	yes
#HAS_CONFIGURE=	yes

.include "../../graphics/png/buildlink3.mk"
.include "../../lang/tcl/buildlink3.mk"
.include "../../x11/tk/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
