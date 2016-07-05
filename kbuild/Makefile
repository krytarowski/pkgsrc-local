# $NetBSD: Makefile,v 1.5 2013/02/01 22:22:16 thomasklausner Exp $
#

KBUILDVERMAJ=	0.1.9998
KBUILDVERMIN=	8
KBUILDVERSVN=	2814
KBUILDVERFDR=	25

DISTNAME=	kBuild-${KBUILDVERMAJ}-${KBUILDVERMIN}.r${KBUILDVERSVN}.fc${KBUILDVERFDR}
PKGNAME=	kbuild-${KBUILDVERMAJ}.${KBUILDVERMIN}.${KBUILDVERSVN}.${KBUILDVERFDR}
CATEGORIES=	devel
MASTER_SITES=	http://dl.fedoraproject.org/pub/fedora/linux/development/rawhide/Everything/source/tree/Packages/k/
EXTRACT_SUFX=	.src.rpm

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	ftp://ftp.netlabs.org/pub/kbuild/
COMMENT=	Framework for writing simple makefiles for complex tasks
LICENSE=	gnu-gpl-v3 # but also various other licenses in 3rd party code

NO_CONFIGURE=		yes
USE_PKGLOCALEDIR=	yes
WRKSRC=			${WRKDIR}/kBuild-0.1.5-p2

USE_TOOLS+=	pax gmake autoconf automake autoreconf perl flex bison

#.include "../../mk/bsd.prefs.mk"

#KBUILD_PLATFORM=	${LOWER_OPSYS}.${MACHINE_ARCH:S/x86_64/amd64/:S/i386/x86/}
#KBUILD_BIN_PATH=	${WRKSRC}/kBuild/bin/${KBUILD_PLATFORM}
#MAKE_ENV+=		WRKSRC=${WRKSRC}

#do-extract:
#	${RUN} 

#post-extract:
#.if ${OPSYS} == "NetBSD"
#	cp ${FILESDIR}/strtofflags.c ${WRKSRC}/src/kmk
#;2B#;2B.endif
#	rm -rf ${WRKSRC}/kBuild/bin
#	mkdir -p ${KBUILD_BIN_PATH}
#	ln -s ${SH} ${KBUILD_BIN_PATH}/kmk_ash
#
#pre-build:
#	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${SH} ${FILESDIR}/bootstrap.sh
#
#do-build:
##;2B#;2B	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} \
#	  `${SH} ${WRKSRC}/kBuild/env.sh --full --eval --set` kmk
#
#INSTALLATION_DIRS=	bin
#
#do-install:
#	for f in ${WRKSRC}/out/${KBUILD_PLATFORM}/release/kBuild/bin/${KBUILD_PLATFORM}/*; do	\
#	  ${INSTALL_PROGRAM} $${f} ${DESTDIR}${PREFIX}/bin;	\
#	done

.include "../../mk/bsd.pkg.mk"
