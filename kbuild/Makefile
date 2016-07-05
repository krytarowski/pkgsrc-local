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

USE_TOOLS+=	pax gmake autoconf automake autoreconf perl flex bison

post-extract:
	${RUN}cd ${WRKDIR} && ${EXTRACTOR} ${KBUILDNAME}-r${KBUILDVERSVN}.tar.gz

.include "../../mk/bsd.pkg.mk"
