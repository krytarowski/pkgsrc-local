# $NetBSD$

DISTNAME=	llvmlite-0.14.0.dev
GITHUB_PROJECT=	llvmlite
PKGNAME=	${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=	devel python
MASTER_SITES=	${MASTER_SITE_GITHUB:=numba/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://llvmlite.pydata.org/
COMMENT=	Lightweight LLVM python binding for JIT compilers
LICENSE=	bsd-2-clause

USE_LANGUAGES=	c++

#DEPENDS+=	${PYPKGPREFIX}-enum-[0-9]*:../../wip/py-enum

.include "../../lang/python/application.mk"
.include "../../lang/python/egg.mk"
.include "../../mk/bsd.pkg.mk"
