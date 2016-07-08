# $NetBSD$

DISTNAME=	libcap-2.25
CATEGORIES=	local
MASTER_SITES=	https://www.kernel.org/pub/linux/libs/security/linux-privs/libcap2/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://sites.google.com/site/fullycapable/
COMMENT=	Library for getting and setting POSIX.1e capabilities
LICENSE=	gnu-gpl-v2

USE_TOOLS+=	pkg-config

ONLY_FOR_PLATFORM=	Linux-*-*

PKGCONFIG_OVERRIDE+=	libcap/libcap.pc.in

.include "../../mk/bsd.pkg.mk"
