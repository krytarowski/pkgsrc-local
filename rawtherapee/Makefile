# $NetBSD$

DISTNAME=	rawtherapee-4.2
CATEGORIES=	graphics
MASTER_SITES=	http://rawtherapee.com/shared/source/
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://rawtherapee.com/
COMMENT=	Powerful cross-platform raw photo processing program
LICENSE=	gnu-gpl-v3

USE_TOOLS+=	pkg-config

USE_CMAKE=	yes
USE_LANGUAGES=	c c++

CXXFLAGS+=	-std=gnu++11

.include "../../devel/libsigc++1/buildlink3.mk"
.include "../../graphics/tiff/buildlink3.mk"
.include "../../audio/libcanberra/buildlink3.mk"
.include "../../wip/libiptcdata/buildlink3.mk"
.include "../../math/fftwf/buildlink3.mk"
.include "../../graphics/lcms2/buildlink3.mk"
.include "../../x11/gtkmm/buildlink3.mk"
.include "../../devel/glibmm/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
