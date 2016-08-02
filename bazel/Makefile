# $NetBSD$

DISTNAME=	bazel-0.3.1
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=bazelbuild/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.bazel.io/
COMMENT=	Google's own build tool
LICENSE=	apache-2.0

USE_TOOLS+=	pkg-config
USE_LANGUAGES=	c c++

PKGCONFIG_OVERRIDE+=	third_party/zlib/contrib/minizip/minizip.pc.in
PKGCONFIG_OVERRIDE+=	third_party/zlib/zlib.pc.in

.include "../../mk/bsd.pkg.mk"
