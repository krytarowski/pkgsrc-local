# $NetBSD$

GITHUB_PROJECT=	valama
GITHUB_TAG=	a7539fa031f1888c4704d587112832a11f4949b4
DISTNAME=	valama-0
CATEGORIES=	editors
MASTER_SITES=	${MASTER_SITE_GITHUB:=Valama/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://valama.github.io/valama/
COMMENT=	Next generation Vala IDE
LICENSE=	gnu-gpl-v3

USE_TOOLS+=	pkg-config

USE_CMAKE=	yes

.include "../../devel/libglade/buildlink3.mk"
.include "../../devel/glade3/buildlink3.mk"
.include "../../devel/gdl/buildlink3.mk"
.include "../../x11/gtksourceview3/buildlink3.mk"
.include "../../x11/gtk3/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../devel/libgee/buildlink3.mk"
.include "../../lang/vala/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
