# $NetBSD$


GIT_REPOSITORIES=	wcc
GIT_REPO.wcc=	git@github.com:endrazine/wcc.git

.include "../../wip/mk/git-package.mk"

PKGNAME=	wcc-0
CATEGORIES=	devel

MAINTAINER=	pkgsrc-users@NetBSD.org
COMMENT=	The Witchcraft Compiler Collection
LICENSE=	mit

WRKSRC=		${WRKDIR}/wcc

MAKE_FLAGS=	CC=${CC:Q}

.include "../../devel/binutils/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
