# $NetBSD$

GITHUB_PROJECT=	SmallBASIC
DISTNAME=	SmallBASIC-0.12.6
PKGNAME=	${DISTNAME:tl}
CATEGORIES=	lang
MASTER_SITES=	${MASTER_SITE_GITHUB:=smallbasic/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://smallbasic.sourceforge.net/
COMMENT=	TODO: Short description of the package
LICENSE=	gnu-gpl-v3

USE_TOOLS+=	aclocal autoheader autoconf automake

USE_LANGUAGES+=	c c++

GNU_CONFIGURE=		YES

CONFIGURE_ARGS+=	--enable-sdl

pre-configure:
	${RUN} cd ${WRKSRC} && ${SH} ./autogen.sh

.include "../../mk/bsd.pkg.mk"
