# $NetBSD$

DISTNAME=	libiptcdata-1.0.4
CATEGORIES=	graphics
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=libiptcdata/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://libiptcdata.sourceforge.net/
COMMENT=	Library for manipulating the IPTC metadata
LICENSE=	gnu-lgpl-v2

GNU_CONFIGURE=		yes
USE_LIBTOOL=		yes
USE_TOOLS+=		pkg-config
USE_PKGLOCALEDIR=	yes

PKGCONFIG_OVERRIDE+=	libiptcdata/libiptcdata.pc.in

.include "../../mk/bsd.pkg.mk"
