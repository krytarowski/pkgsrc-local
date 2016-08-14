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

SUBST_CLASSES+=		exe
SUBST_STAGE.exe=	pre-configure
SUBST_MESSAGE.clustalx=	Adjusting paths for pkgsrc
SUBST_FILES.exe=	gemrb-gameinstallers
SUBST_VARS.exe=		PREFIX
SUBST_VARS.exe=		BASH


INSTALLATION_DIRS+=	bin share/${PKGBASE}

DEPENDS+=	coreutils-[0-9]*:../../sysutils/coreutils

post-extract:
	${CP} ${FILESDIR}/gemrb-gameinstallers ${WRKSRC}

do-install:
	${RUN} cd ${WRKSRC} && ${PAX} -rw . ${DESTDIR}${PREFIX}/share/${PKGBASE}
	${LN} -sf ${PREFIX}/share/${PKGBASE}/gemrb-gameinstallers \
		${DESTDIR}${PREFIX}/bin/gemrb-gameinstallers

.include "../../mk/bsd.pkg.mk"
