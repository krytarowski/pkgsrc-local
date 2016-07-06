# $NetBSD$

GITHUB_PROJECT=	jack2
DISTNAME=	v1.9.10
PKGNAME=	${GITHUB_PROJECT}-${DISTNAME}
CATEGORIES=	local
MASTER_SITES=	${MASTER_SITE_GITHUB:=jackaudio/}
EXTRACT_SUFX=	.zip
DIST_SUBDIR=	${GITHUB_PROJECT}

MAINTAINER=	INSERT_YOUR_MAIL_ADDRESS_HERE
HOMEPAGE=	https://github.com/jackaudio/jack2/
COMMENT=	TODO: Short description of the package
#LICENSE=	# TODO: (see mk/license.mk)

WRKSRC=		${WRKDIR}/jack2-1.9.10
USE_TOOLS+=	pkg-config bash
USE_LANGUAGES=	c c++

PKGCONFIG_OVERRIDE+=	jack.pc.in

REPLACE_BASH+=	svnversion_regenerate.sh

WAF_REPLACE_EXECUTABLE=	no

REPLACE_PYTHON+=	waf
REPLACE_PYTHON+=	wscript
REPLACE_PYTHON+=	*/wscript

.include "../../audio/libsamplerate/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../devel/waf/waf.mk"
.include "../../mk/bsd.pkg.mk"
