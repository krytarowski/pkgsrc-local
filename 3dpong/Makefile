# $NetBSD$

DISTNAME=	3dpong-0.5
CATEGORIES=	games
MASTER_SITES=	ftp://ftp.tuxpaint.org/unix/x/3dpong/src/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	ftp://ftp.tuxpaint.org/unix/x/3dpong/src/
COMMENT=	3D Pong game for 1 or 2 players
LICENSE=	gnu-gpl-v2

USE_TOOLS+=	gmake

MAKE_FLAGS+=	MAN_PREFIX=${PREFIX}/${PKGMANDIR}
MAKE_FLAGS+=	XLIB="${COMPILER_RPATH_FLAG}${X11BASE}/lib -L${X11BASE}/lib -lX11"

.include "../../mk/x11.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
