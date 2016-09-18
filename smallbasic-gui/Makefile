# $NetBSD$

GITHUB_PROJECT=	SmallBASIC
DISTNAME=	SmallBASIC-0.12.6
PKGNAME=	${DISTNAME:tl}
CATEGORIES=	lang
MASTER_SITES=	${MASTER_SITE_GITHUB:=smallbasic/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://smallbasic.sourceforge.net/
COMMENT=	Fast and easy to learn BASIC language interpreter
LICENSE=	gnu-gpl-v3

USE_TOOLS+=	aclocal autoheader autoconf automake bash pkg-config

USE_LANGUAGES=	c c++

# for xxd
BUILD_DEPENDS+=	vim-[0-9]*:../../editors/vim

GNU_CONFIGURE=		YES
CONFIG_SHELL=		${BASH}

BUILDLINK_TRANSFORM+=	rm:-ldl

.include "options.mk"

pre-configure:
	${RUN} cd ${WRKSRC} && ${SH} ./autogen.sh

.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../devel/pcre/buildlink3.mk"
.include "../../fonts/fontconfig/buildlink3.mk"
.include "../../devel/SDL2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
# $NetBSD: options.mk,v 1.1 2015/02/27 12:11:20 gdt Exp $

PKG_OPTIONS_VAR=		PKG_OPTIONS.smallbasic
PLIST_VARS+=			sdl
PKG_SUPPORTED_OPTIONS=		sdl
PKG_SUGGESTED_OPTIONS=		sdl

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Msdl)
.include "../../devel/SDL2/buildlink3.mk"
CONFIGURE_ARGS+=        --enable-sdl
PLIST.sdl=		YES
.endif
