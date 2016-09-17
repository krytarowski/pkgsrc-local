# $NetBSD$

DISTNAME=	valide-0.7.1
CATEGORIES=	editors
MASTER_SITES=	https://launchpad.net/valide/trunk/${PKGVERSION_NOREV}/+download/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://launchpad.net/valide
COMMENT=	IDE for the Vala programming language
LICENSE=	gnu-gpl-v3

USE_TOOLS+=	pkg-config

PKGCONFIG_OVERRIDE+=	libvalide/libyaml-glib/libyaml-glib-1.0.pc.in
PKGCONFIG_OVERRIDE+=	libvalide/libyaml-glib/libyaml/libyaml-1.0.pc.in

.include "../../mk/bsd.pkg.mk"
