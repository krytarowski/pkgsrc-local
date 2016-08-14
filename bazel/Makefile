# $NetBSD$

DISTNAME=	bazel-0.3.1
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=bazelbuild/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.bazel.io/
COMMENT=	Google's own build tool
LICENSE=	apache-2.0

USE_TOOLS+=	pkg-config bash
USE_LANGUAGES=	c c++

PKGCONFIG_OVERRIDE+=	third_party/zlib/contrib/minizip/minizip.pc.in
PKGCONFIG_OVERRIDE+=	third_party/zlib/zlib.pc.in

REPLACE_BASH=	compile.sh

USE_JAVA=	yes
USE_JAVA2=	yes

MAKE_ENV+=	JAVA_HOME=${PKG_JAVA_HOME}
MAKE_ENV+=	PROTOC=${PREFIX}/bin/protoc

do-build:
	${RUN} cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${BASH} -x ./compile.sh
#	${RUN} cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${BASH} ./compile.sh

.include "../../devel/protobuf/buildlink3.mk"
.include "../../mk/java-vm.mk"
.include "../../mk/bsd.pkg.mk"
