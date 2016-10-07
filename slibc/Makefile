# $NetBSD$

DISTNAME=	slibc_0.9.3.orig
CATEGORIES=	devel
MASTER_SITES=	ftp://ftp.pbone.net/vol2/ftp5.gwdg.de/pub/opensuse/repositories/home%3A/SecureBusinessAustria%3A/slibc/Debian_7.0/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	ftp://ftp.pbone.net/vol2/ftp5.gwdg.de/pub/opensuse/repositories/home%3A/SecureBusinessAustria%3A/slibc/Debian_7.0/
COMMENT=	Annex K
LICENSE=	gnu-lgpl-v2.1

WRKSRC=		${WRKDIR}/slibc-0.9.3
USE_TOOLS=	gmake
USE_LANGUAGES=	c c++

CPPFLAGS.NetBSD+=	-Derrno_t=int

.include "../../mk/bsd.pkg.mk"
