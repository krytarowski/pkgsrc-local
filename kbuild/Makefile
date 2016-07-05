# $NetBSD: Makefile,v 1.5 2013/02/01 22:22:16 thomasklausner Exp $
#

KBUILDNAME=	kBuild
KBUILDVERMAJ=	0.1.9998
KBUILDVERMIN=	8
KBUILDVERSVN=	2814
KBUILDVERFDR=	25

DISTNAME=	${KBUILDNAME}-${KBUILDVERMAJ}-${KBUILDVERMIN}.r${KBUILDVERSVN}.fc${KBUILDVERFDR}
PKGNAME=	${KBUILDNAME:tl}-${KBUILDVERMAJ}.${KBUILDVERMIN}.${KBUILDVERSVN}.${KBUILDVERFDR}
CATEGORIES=	devel
MASTER_SITES=	http://dl.fedoraproject.org/pub/fedora/linux/development/rawhide/Everything/source/tree/Packages/k/
EXTRACT_SUFX=	.src.rpm

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	ftp://ftp.netlabs.org/pub/kbuild/
COMMENT=	Framework for writing simple makefiles for complex tasks
# but also various other licenses in 3rd party code
LICENSE=	gnu-gpl-v3

WRKSRC=		${WRKDIR}/${KBUILDNAME}

USE_TOOLS+=	pax lex

KBUILD_VERSION_PATCH=	${KBUILDVERMAJ:E}

post-extract:
	${RUN} cd ${WRKDIR} && ${EXTRACTOR} ${KBUILDNAME}-r${KBUILDVERSVN}.tar.gz

pre-build:
# Remove prebuilt files
	${RUN} cd ${WRKSRC} && rm -rf kBuild/bin/*

do-build:
	${RUN} cd ${WRKSRC} && \
	./kBuild/env.sh \
		--full-make -f bootstrap.gmk \
		KBUILD_VERBOSE=2 \
		KBUILD_VERSION_PATCH=${KBUILD_VERSION_PATCH} && \
	./kBuild/env.sh kmk \
		BUILD_TYPE=release \
		MY_INST_MODE=0644 \
		MY_INST_BIN_MODE=0755 \
		rebuild

do-install:
	${RUN} cd ${WRKSRC} && \
	KBUILD_VERBOSE=2 \
		./kBuild/env.sh kmk \
		BUILD_TYPE=release \
		MY_INST_MODE=0644 \
		MY_INST_BIN_MODE=0755 \
		PATH_INS=${DESTDIR} \
		install

.include "../../mk/bsd.pkg.mk"
