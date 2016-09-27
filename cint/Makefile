# $NetBSD: Makefile,v 1.31 2015/12/11 23:32:53 joerg Exp $

DISTNAME=		cint-5.16.19-source
PKGNAME=		${DISTNAME:S/-source//}
CATEGORIES=		lang
MASTER_SITES=		https://root.cern.ch/download/

MAINTAINER=		drochner@NetBSD.org
HOMEPAGE=		http://www.hanno.jp/gotom/Cint.html
COMMENT=		C/C++ interpreter

USE_TOOLS+=		bash gmake
USE_LANGUAGES=		c c++

CONFIG_SHELL=		${BASH}

WRKSRC=			${WRKDIR}/${PKGNAME_NOREV}

MAKE_JOBS_SAFE=		no

CONFIGURE_ARGS+=	--arch=netbsd
CONFIGURE_ARGS+=	--readline=${PREFIX}/lib/libreadline.so

USE_LANGUAGES=		c c++

HAS_CONFIGURE=			yes
BUILDLINK_TRANSFORM.NetBSD+=	rm:-ldl
CPPFLAGS+=			-Wno-write-strings
LDFLAGS+=			${COMPILER_RPATH_FLAG}${PREFIX}/lib

BUILD_TARGET=			# empty string required

.include "../../mk/readline.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
