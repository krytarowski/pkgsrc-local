# $NetBSD: Makefile,v 1.22 2014/10/09 14:06:01 wiz Exp $
#

DISTNAME=	covered-0.7.10
CATEGORIES=	cad
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=covered/}

MAINTAINER=	dmcmahill@NetBSD.org
HOMEPAGE=	http://covered.sourceforge.net/
COMMENT=	Verilog code coverage analyzer (stable release version)

GNU_CONFIGURE=	YES
USE_TOOLS+=	bison gmake lex autoheader

CONFIGURE_ARGS+=	--with-tcl-config=${BUILDLINK_PREFIX.tcl}/lib/tclConfig.sh
CONFIGURE_ARGS+=	--with-tk-config=${BUILDLINK_PREFIX.tk}/lib/tkConfig.sh

# This is required for TCL/TK dependency
CPPFLAGS+=	-DUSE_INTERP_RESULT

.include "../../local/iverilog/buildlink3.mk"
.include "../../devel/gperf/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../lang/tcl/buildlink3.mk"
.include "../../x11/tk/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
