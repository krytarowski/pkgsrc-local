# $NetBSD$

DISTNAME=	atanks-6.4
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=atanks/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://atanks.sourceforge.net/
COMMENT=	Multi-platform Scorched Earth clone similar to Worms
LICENSE=	gnu-gpl-v2

USE_LANGUAGES=	c c++

USE_TOOLS+=	gmake

do-build:
	${RUN} cd ${WRKSRC}/src && \
		${CXX} -std=c++11 *.cpp \
		-DVERSION=\"${PKGVERSION_NOREV}\" \
		-DDATA_DIR=\"${PREFIX}/share/atanks\" \
		`allegro-config --libs` \
		`allegro-config --cflags`

.include "../../devel/allegro/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
