# $NetBSD$

DISTNAME=	calamares-2.4.5
CATEGORIES=	sysutils
MASTER_SITES=	${MASTER_SITE_GITHUB:=calamares/}
GITHUB_RELEASE=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://calamares.io
COMMENT=	Distribution-independent installer framework
LICENSE=	gnu-gpl-v3

USE_CMAKE=	yes
USE_LANGUAGES=	c c++

.include "../../devel/kparts/buildlink3.mk"
.include "../../security/polkit-qt5/buildlink3.mk"
.include "../../textproc/yaml-cpp/buildlink3.mk"
.include "../../x11/qt5-qttools/buildlink3.mk"
.include "../../x11/qt5-qtbase/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
