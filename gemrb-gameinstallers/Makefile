# $NetBSD$

DISTNAME=	gemrb-gameinstallers-0.1.2
CATEGORIES=	local
MASTER_SITES=	https://git.njw.name/cgit/cgit.cgi/gemrb-gameinstallers/snapshot/
EXTRACT_SUFX=	.zip

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.gemrb.org/
COMMENT=	GemRB Python installer
LICENSE=	gnu-gpl-v3

USE_TOOLS+=	bash pax:build

USE_LANGUAGES=	# none

REPLACE_BASH+=	*.sh */*.sh

NO_BUILD=	yes

INSTALLATION_DIRS+=	share/${PKGBASE}

DEPENDS+=	coreutils-[0-9]*:../../sysutils/coreutils

do-install:
	${RUN} cd ${WRKSRC} && ${PAX} -rw . ${DESTDIR}${PREFIX}/share/${PKGBASE}

.include "../../mk/bsd.pkg.mk"
