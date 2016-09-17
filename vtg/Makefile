# $NetBSD$

DISTNAME=	vtg-0.12.1
CATEGORIES=	local
MASTER_SITES=	https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/vtg/
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	INSERT_YOUR_MAIL_ADDRESS_HERE
HOMEPAGE=	https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/vtg/
COMMENT=	TODO: Short description of the package
#LICENSE=	# TODO: (see mk/license.mk)

GNU_CONFIGURE=	yes
USE_TOOLS+=	pkg-config intltool

PKGCONFIG_OVERRIDE+=	afrodite/libafrodite.pc.in

.include "../../lang/vala/buildlink3.mk"
.include "../../x11/gtk3/buildlink3.mk"
.include "../../devel/glib2/schemas.mk"
.include "../../mk/bsd.pkg.mk"
