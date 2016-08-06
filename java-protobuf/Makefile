# $NetBSD: Makefile,v 1.7 2016/07/09 13:03:43 wiz Exp $

.include "../../local/protobuf/Makefile.common"

DISTNAME=	protobuf-java-${PROTOBUFVER}
PKGNAME=	java-${DISTNAME:S/-java//}
CATEGORIES+=	java

MAINTAINER=	pkgsrc-users@NetBSD.org
COMMENT=	Java bindings for protobuf

USE_JAVA=	yes
USE_JAVA2=	yes

.include "../../local/protobuf/buildlink3.mk"
.include "../../mk/java-vm.mk"
.include "../../mk/bsd.pkg.mk"
