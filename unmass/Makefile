# $NetBSD$

DISTNAME=	unmass-0.92
CATEGORIES=	archivers
MASTER_SITES=	http://mirex.mypage.sk/FILES/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://mirex.mypage.sk/index.php?selected=1#Unmass
COMMENT=	Extractor of files from those big game files
LICENSE=	gnu-gpl-v2

GNU_CONFIGURE=	yes

USE_LANGUAGES=	c++
USE_TOOLS=	gmake

CONFIGURE_DIRS=	kdev_cmd

CPPFLAGS+= -DUNIX

post-extract:
	${RUN} cd ${WRKSRC} && ${CP} -r src kdev_cmd

.include "../../mk/bsd.pkg.mk"
