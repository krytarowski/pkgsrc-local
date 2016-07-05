# $NetBSD$

DISTNAME=	silan-0.3.2
CATEGORIES=	audio
MASTER_SITES=	${MASTER_SITE_GITHUB:=x42/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/x42/silan/
COMMENT=	audio file [silence] analyzer
LICENSE=	gnu-gpl-v2

USE_TOOLS+=	autoconf automake autoreconf pkg-config

HAS_CONFIGURE=	yes

pre-configure:
	${RUN} cd ${WRKSRC} && autoreconf -fiv

.include "../../audio/libsndfile/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
