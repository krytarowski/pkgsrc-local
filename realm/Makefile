# $NetBSD$

GITHUB_PROJECT=	realm-core
GITHUB_TAG=	v6.0.8
DISTNAME=	v6.0.8
PKGNAME=	${GITHUB_PROJECT}-${DISTNAME:S,^v,,}
CATEGORIES=	# TODO: add primary category
MASTER_SITES=	${MASTER_SITE_GITHUB:=realm/}
DIST_SUBDIR=	${GITHUB_PROJECT}

MAINTAINER=	INSERT_YOUR_MAIL_ADDRESS_HERE # or use pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/realm/realm-core/
COMMENT=	TODO: Short description of the package
#LICENSE=	# TODO: (see mk/license.mk)

WRKSRC=		${WRKDIR}/realm-core-6.0.8
USE_CMAKE=	yes
USE_LANGUAGES=	c c++
CMAKE_ARGS+=	-DPEGTL_SYSTEM=1

CONFIGURE_DIRS=	${WRKDIR}/build                                                                
CMAKE_ARG_PATH=	${WRKSRC}

post-extract:
	${MKDIR} ${WRKDIR}/build

.include "../../security/openssl/buildlink3.mk"
.include "../../wip/pegtl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
