# $NetBSD$

DISTNAME=	pinktrace-0.1.2
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=alip/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://dev.exherbo.org/~alip/pinktrace/
COMMENT=	Pink's Tracing Library
#LICENSE=	# TODO: (see mk/license.mk)

WRKSRC=		${WRKDIR}/pinktrace-0.1.2
USE_TOOLS+=	pkg-config aclocal autoheader autoconf automake
USE_LIBTOOL=	yes

PKGCONFIG_OVERRIDE+=	pkg-config/pinktrace.pc.in
PKGCONFIG_OVERRIDE+=	pkg-config/pinktrace_easy.pc.in

HAS_CONFIGURE=	yes

pre-configure:
	${RUN} cd ${WRKSRC} && ./autogen.sh

.include "../../mk/bsd.pkg.mk"
