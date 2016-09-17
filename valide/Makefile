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

REPLACE_PYTHON=	waf

WAF_REPLACE_EXECUTABLE=	no
WAF_HAS_MANDIR=		no

.include "../../lang/vala/buildlink3.mk"
.include "../../x11/gtksourceview2/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../devel/waf/waf.mk"
.include "../../mk/bsd.pkg.mk"
