# $NetBSD$

DISTNAME=	amoebax-0.2.1
CATEGORIES=	games
# Original MASTER_SITE randomly truncates file on download
MASTER_SITES=	${MASTER_SITE_GENTOO:=distfiles/}
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.emma-soft.com/games/amoebax/
COMMENT=	Cute and addictive action-puzzle game
LICENSE=	gnu-gpl-v2 # AND free-art-1.2

GNU_CONFIGURE=	yes
USE_LANGUAGES=	c c++

.include "../../audio/SDL_mixer/buildlink3.mk"
.include "../../devel/SDL/buildlink3.mk"
.include "../../graphics/SDL_image/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
