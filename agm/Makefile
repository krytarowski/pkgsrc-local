# $NetBSD$

DISTNAME=	agm-1.3.1
CATEGORIES=	local
MASTER_SITES=	ftp://ftp.ibiblio.org/pub/linux/games/amusements/

MAINTAINER=	INSERT_YOUR_MAIL_ADDRESS_HERE
HOMEPAGE=	ftp://ftp.ibiblio.org/pub/linux/games/amusements/
COMMENT=	TODO: Short description of the package
#LICENSE=	# TODO: (see mk/license.mk)

SUBST_CLASSES+=		rcsids
SUBST_MESSAGE.rcsids=	Strip RCS IDs as they cause problems when patching.
SUBST_STAGE.rcsids=	pre-patch
SUBST_FILES.rcsids+=	gobble.c
SUBST_FILES.rcsids+=	listfuncs.c
SUBST_FILES.rcsids+=	main.c
SUBST_FILES.rcsids+=	output.c
SUBST_FILES.rcsids+=	process.c
SUBST_FILES.rcsids+=	progress.c
SUBST_FILES.rcsids+=	sort.c
SUBST_FILES.rcsids+=	wordfuncs.c
SUBST_SED.rcsids=	-e "s!$Revision!Revision!"


.include "../../mk/bsd.pkg.mk"
