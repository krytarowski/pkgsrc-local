# $NetBSD: Makefile,v 1.31 2015/12/11 23:32:53 joerg Exp $

DISTNAME=		cint-5.16.19-source
PKGNAME=		${DISTNAME:S/-source//}
CATEGORIES=		lang
MASTER_SITES=		https://root.cern.ch/download/

MAINTAINER=		drochner@NetBSD.org
HOMEPAGE=		http://www.hanno.jp/gotom/Cint.html
COMMENT=		C/C++ interpreter

#CONFLICTS=		man-pages-[0-9]*

USE_TOOLS+=		bash
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

#INSTALLATION_DIRS=	bin ${PKGMANDIR}/man1 ${PKGMANDIR}/man2
#INSTALLATION_DIRS+=	${PKGMANDIR}/man3

CONFIGURE_ARGS+=	--arch=netbsd

USE_LANGUAGES=		c c++

HAS_CONFIGURE=		yes

do-install:
	${INSTALL_DATA_DIR} ${DESTDIR}${PREFIX}/cint
	${INSTALL_PROGRAM} ${WRKDIR}/cint ${DESTDIR}${PREFIX}/cint
	${INSTALL_PROGRAM} ${WRKDIR}/makecint ${DESTDIR}${PREFIX}/cint
	${SED} "s;XXXPREFIXXXX;${PREFIX};g" <${FILESDIR}/cint.sh >${DESTDIR}${PREFIX}/bin/cint
	${CHMOD} +x ${DESTDIR}${PREFIX}/bin/cint
	rm -f ${DESTDIR}${PREFIX}/bin/makecint
	cd ${DESTDIR}${PREFIX}/bin && ${LN} cint makecint
	${INSTALL_DATA} ${WRKDIR}/MAKEINFO ${DESTDIR}${PREFIX}/cint
	${CP} -r ${WRKDIR}/include ${WRKDIR}/stl ${DESTDIR}${PREFIX}/cint
	${RM} ${DESTDIR}${PREFIX}/cint/include/Makeit \
		${DESTDIR}${PREFIX}/cint/include/make*
	${INSTALL_DATA_DIR} ${DESTDIR}${PREFIX}/cint/lib
	${CP} -r ${WRKDIR}/lib/prec_stl ${DESTDIR}${PREFIX}/cint/lib
	${INSTALL_DATA} ${WRKDIR}/G__ci.h ${DESTDIR}${PREFIX}/cint
	${INSTALL_DATA_DIR} ${DESTDIR}${PREFIX}/share/doc/cint
	${INSTALL_DATA} ${WRKSRC}/doc/bytecode.txt \
		${DESTDIR}${PREFIX}/share/doc/cint
	${INSTALL_DATA} ${WRKSRC}/doc/cint.txt \
		${DESTDIR}${PREFIX}/share/doc/cint
	${INSTALL_DATA} ${WRKSRC}/doc/cintapi.txt \
		${DESTDIR}${PREFIX}/share/doc/cint
	${INSTALL_DATA} ${WRKSRC}/doc/extlib.txt \
		${DESTDIR}${PREFIX}/share/doc/cint
	${INSTALL_DATA} ${WRKSRC}/doc/ifdef.txt \
		${DESTDIR}${PREFIX}/share/doc/cint
	${INSTALL_DATA} ${WRKSRC}/doc/limitati.txt \
		${DESTDIR}${PREFIX}/share/doc/cint
	${INSTALL_DATA} ${WRKSRC}/doc/limitnum.txt \
		${DESTDIR}${PREFIX}/share/doc/cint
	${INSTALL_DATA} ${WRKSRC}/doc/makecint.txt \
		${DESTDIR}${PREFIX}/share/doc/cint
	${INSTALL_DATA} ${WRKSRC}/doc/message.txt \
		${DESTDIR}${PREFIX}/share/doc/cint
	${INSTALL_DATA} ${WRKSRC}/doc/ref.txt \
		${DESTDIR}${PREFIX}/share/doc/cint
	${INSTALL_MAN} ${WRKSRC}/doc/man1/cint.1 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man1
	${INSTALL_MAN} ${WRKSRC}/doc/man1/makecint.1 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man1
	${INSTALL_MAN} ${WRKSRC}/doc/man2/garbage.2 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man2
	${INSTALL_MAN} ${WRKSRC}/doc/man2/security.2 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man2
	${INSTALL_MAN} ${WRKSRC}/doc/man2/unique.2 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man2
	${INSTALL_MAN} ${WRKSRC}/doc/man3/array.h.3 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man3
	${INSTALL_MAN} ${WRKSRC}/doc/man3/fft.h.3 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man3
	${INSTALL_MAN} ${WRKSRC}/doc/man3/statistics.h.3 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man3

# The library seems to want these but the pertinent parts still don't
# build, so I'm reluctant to bother.
#
#.include "../../graphics/glu/buildlink3.mk"
#.include "../../graphics/MesaLib/buildlink3.mk"
#.include "../../x11/xproto/buildlink3.mk"
#.include "../../x11/libX11/buildlink3.mk"

.include "../../mk/bsd.pkg.mk"
