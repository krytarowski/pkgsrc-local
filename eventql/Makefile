# $NetBSD$

DISTNAME=	eventql-0.3.0.rc0
CATEGORIES=	local
MASTER_SITES=	${MASTER_SITE_GITHUB:=eventql/}
GITHUB_TAG=	v${PKGVERSION_NOREV:S/.rc/-rc/}

MAINTAINER=	INSERT_YOUR_MAIL_ADDRESS_HERE
HOMEPAGE=	https://github.com/eventql/eventql/
COMMENT=	distributed, column-oriented database for event collection and analytics
LICENSE=	gnu-agpl-v3

WRKSRC=			${WRKDIR}/eventql-0.3.0-rc0
USE_TOOLS+=		pkg-config autoconf automake autoconf perl
USE_PKGLOCALEDIR=	yes
USE_LANGUAGES=		c c++

HAS_CONFIGURE=		yes

PKGCONFIG_OVERRIDE+=	deps/3rdparty/pcre/libpcre.pc.in
PKGCONFIG_OVERRIDE+=	deps/3rdparty/pcre/libpcre16.pc.in
PKGCONFIG_OVERRIDE+=	deps/3rdparty/pcre/libpcre32.pc.in
PKGCONFIG_OVERRIDE+=	deps/3rdparty/pcre/libpcrecpp.pc.in
PKGCONFIG_OVERRIDE+=	deps/3rdparty/pcre/libpcreposix.pc.in
PKGCONFIG_OVERRIDE+=	deps/3rdparty/spidermonkey/mozjs/js/src/ctypes/libffi/libffi.pc.in
PKGCONFIG_OVERRIDE+=	deps/3rdparty/spidermonkey/mozjs/js/src/js.pc.in

pre-configure:
	${RUN} cd ${WRKSRC} && ./autogen.sh

.include "../../mk/bsd.pkg.mk"
