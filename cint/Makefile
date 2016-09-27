# $NetBSD: Makefile,v 1.31 2015/12/11 23:32:53 joerg Exp $

DISTNAME=		cint-5.16.19-source
PKGNAME=		${DISTNAME:S/-source//}
CATEGORIES=		lang
MASTER_SITES=		https://root.cern.ch/download/

MAINTAINER=		drochner@NetBSD.org
HOMEPAGE=		http://www.hanno.jp/gotom/Cint.html
COMMENT=		C/C++ interpreter

#CONFLICTS=		man-pages-[0-9]*

USE_TOOLS+=		bash gmake
USE_LANGUAGES=		c c++

CONFIG_SHELL=		${BASH}

WRKSRC=			${WRKDIR}/${PKGNAME_NOREV}

#GCC_REQD+=		3.0
#PTHREAD_OPTS+=		native
#PLIST_VARS+=		threads
#.include "../../mk/pthread.buildlink3.mk"
#.if defined(PTHREAD_TYPE) && ${PTHREAD_TYPE} == "native"
#PLIST.threads=		yes
#.endif

MAKE_JOBS_SAFE=		no

#INSTALLATION_DIRS=	bin ${PKGMANDIR}/man1 ${PKGMANDIR}/man2
#INSTALLATION_DIRS+=	${PKGMANDIR}/man3

CONFIGURE_ARGS+=	--arch=netbsd
#CONFIGURE_ARGS+=	--readline=${BUILDLINK_PREFIX.readline}/lib/libreadline.a
#CONFIGURE_ARGS+=	--readline=${PREFIX}/lib/libreadline.so
CONFIGURE_ARGS+=	--readline=${BUILDLINK_PREFIX.readline}/lib/libreadline.so

USE_LANGUAGES=		c c++

HAS_CONFIGURE=			yes
BUILDLINK_TRANSFORM.NetBSD+=	rm:-ldl
CFLAGS+=			-Wno-write-strings
LDFLAGS.NetBSD+=		${COMPILER_RPATH_FLAG}${BUILDLINK_PREFIX.readline}/lib

BUILD_TARGET=			# empty string required

.include "../../mk/readline.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
