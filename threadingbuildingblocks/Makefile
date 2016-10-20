# $NetBSD$

TBB_VERSION=	2017_20160916

DISTNAME=	tbb${TBB_VERSION}oss_src
PKGNAME=	threadingbuildingblocks-${TBB_VERSION:S/_/./}
CATEGORIES=	devel
MASTER_SITES=	https://www.threadingbuildingblocks.org/sites/default/files/software_releases/source/
EXTRACT_SUFX=	.tgz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.threadingbuildingblocks.org/sites/default/files/software_releases/source/
COMMENT=	Intel Threading Building Block
LICENSE=	apache-2.0

WRKSRC=		${WRKDIR}/tbb${TBB_VERSION}oss
USE_LANGUAGES=	c c++

USE_TOOLS+=	gmake

.include "../../mk/bsd.pkg.mk"
