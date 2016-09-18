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

USE_TOOLS+=	aclocal autoheader autoconf automake bash pkg-config

USE_LANGUAGES=	c c++

# for xxd
BUILD_DEPENDS+=	vim-[0-9]*:../../editors/vim

GNU_CONFIGURE=		YES
CONFIG_SHELL=	${BASH}
CONFIGURE_ARGS+=	--enable-sdl

BUILDLINK_TRANSFORM+=	rm:-ldl

pre-configure:
	${RUN} cd ${WRKSRC} && ${SH} ./autogen.sh

.include "../../devel/pcre/buildlink3.mk"
.include "../../fonts/fontconfig/buildlink3.mk"
.include "../../devel/SDL2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
