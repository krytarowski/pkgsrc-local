# $NetBSD$

DISTNAME=	virtualbox-ose-5.0.16
PKGNAME=	${DISTNAME:C/-ose//}
CATEGORIES=	emulators
MASTER_SITES=	http://download.virtualbox.org/virtualbox/${PKGVERSION_NOREV}/ \
	http://tmp.chruetertee.ch/ \
	http://disasterarea.chruetertee.ch/ \
	http://download.virtualbox.org/virtualbox/${VBOX_GUEST_VER}/:guestadditions
DISTFILES= VirtualBox-${PKGVERSION_NOREV}${EXTRACT_SUFX} ${GADISTFILES}
EXTRACT_ONLY= VirtualBox-${PKGVERSION_NOREV}${EXTRACT_SUFX}
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	pkgsrc-users@NetBSD.org
COMMENT=	General-purpose full virtualizer for x86 hardware
LICENSE=	gnu-gpl-v2

DEPENDS+=	cdrtools-[0-9]*:../../sysutils/cdrtools

BUILD_DEPENDS+=	yasm-[0-9]*:../../devel/yasm
BUILD_DEPENDS+=	kBuild>=0.1.999:../../wip/kBuild-svn

USE_TOOLS+=	gtar pkg-config gmake

WRKSRC=		${WRKDIR}/VirtualBox-${PKGVERSION_NOREV}

HAS_CONFIGURE=		yes
#CONFIGURE_ARGS+= --disable-java --passive-mesa
#CONFIGURE_ARGS+= --with-gcc="${CC}" --with-g++="${CXX}"
#GNU_CONFIGURE=	yes
USE_LANGUAGES+=	c c++

#SUBST_CLASSES+=		prefix
#SUBST_FILES.prefix+=	configure
#SUBST_FILES.prefix+=	src/VBox/Additions/x11/Installer/98vboxadd-xclient
#SUBST_FILES.prefix+=	src/VBox/Installer/freebsd/VBox.sh
#SUBST_FILES.prefix+=	src/VBox/Additions/x11/Installer/vboxclient.desktop
#SUBST_FILES.prefix+=	kBuild/header.kmk
#SUBST_FILES.prefix+=	Config.kmk

.include "../../graphics/png/buildlink3.mk"
.include "../../multimedia/libvpx/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../textproc/libxslt/buildlink3.mk"
.include "../../devel/SDL/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.include "../../x11/libXext/buildlink3.mk"
.include "../../x11/qt4-libs/buildlink3.mk"
.include "../../lang/python/pyversion.mk"
.include "../../lang/python/application.mk"
.include "../../mk/bsd.pkg.mk"
