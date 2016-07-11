# $NetBSD$

GITHUB_PROJECT=	rtaudio
DISTNAME=	4.1.2
PKGNAME=	${GITHUB_PROJECT}-${DISTNAME}
CATEGORIES=	local
MASTER_SITES=	${MASTER_SITE_GITHUB:=thestk/}
EXTRACT_SUFX=	.zip
DIST_SUBDIR=	${GITHUB_PROJECT}

MAINTAINER=	INSERT_YOUR_MAIL_ADDRESS_HERE
HOMEPAGE=	https://github.com/thestk/rtaudio/
COMMENT=	TODO: Short description of the package
#LICENSE=	# TODO: (see mk/license.mk)

WRKSRC=		${WRKDIR}/rtaudio-4.1.2
USE_TOOLS+=	pkg-config automake autoconf autoreconf
USE_LIBTOOL=	yes
USE_LANGUAGES=	c c++

HAS_CONFIGURE=	yes

PKGCONFIG_OVERRIDE+=	rtaudio.pc.in

pre-configure:
	${RUN} cd ${WRKSRC} && ./autogen.sh --no-configure

.include "../../mk/bsd.pkg.mk"
