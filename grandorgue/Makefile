# $NetBSD$

SVNREV=		2137

DISTNAME=	ourorgan-svn-${SVNREV}-trunk
PKGNAME=	grandorgue-0.${SVNREV}.1
CATEGORIES=	audio
MASTER_SITES=	https://sourceforge.net/code-snapshots/svn/o/ou/ourorgan/svn/
EXTRACT_SUFX=	.zip

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://sourceforge.net/projects/ourorgan/
COMMENT=	Virtual Pipe Organ Software
LICENSE=	gnu-gpl-v2

USE_CMAKE=	yes
USE_TOOLS+=	pkg-config
USE_LANGUAGES=	c c++ fortran

PKGCONFIG_OVERRIDE+=	src/fftw/src/fftw.pc.in

.include "../../mk/bsd.pkg.mk"
