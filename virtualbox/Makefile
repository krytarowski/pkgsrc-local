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
USE_LANGUAGES+=	c c++

SUBST_CLASSES+=		paths
SUBST_MESSAGE.paths+=	Adjust paths for pkgsrc
SUBST_STAGE.paths=	post-patch
SUBST_FILES.paths+=	configure
SUBST_SED.paths+=	-e 's!^INCCRYPTO=.*!INCCRYPTO="-I${BUILDLINK_PREFIX.openssl}/include"!g'
SUBST_SED.paths+=	-e 's!^LIBCRYPTO=.*!LIBCRYPTO="${COMPILER_RPATH_FLAG}${BUILDLINK_PREFIX.openssl}/lib -L${BUILDLINK_PREFIX.openssl}/lib -lssl -lcrypto"!g'
SUBST_SED.paths+=	-e 's!^INCX11=.*!INCX11="-I${X11BASE}/include"!g'
SUBST_SED.paths+=	-e 's!^LIBX11=.*!LIBX11="${COMPILER_RPATH_FLAG}${X11BASE}/lib -L${X11BASE}/lib -lXext -lX11"!g'
SUBST_SED.paths+=	-e 's!^INCZ=.*!INCZ="-I${BUILDLINK_PREFIX.zlib}/include"!g'
SUBST_SED.paths+=	-e 's!^LIBZ=.*!LIBZ="${COMPILER_RPATH_FLAG}${BUILDLINK_PREFIX.zlib}/lib -L${BUILDLINK_PREFIX.zlib}/lib -lz"!g'
SUBST_SED.paths+=	-e 's!^INCCURL=.*!INCCURL="-I${BUILDLINK_PREFIX.curl}/include"!g'
SUBST_SED.paths+=	-e 's!^LIBCURL=.*!LIBCURL="${COMPILER_RPATH_FLAG}${BUILDLINK_PREFIX.curl}/lib -L${BUILDLINK_PREFIX.curl}/lib -lcurl"!g'
SUBST_SED.paths+=	-e 's!^INCPULSE=.*!INCPULSE="-I${BUILDLINK_PREFIX.pulseaudio}/include"!g'
SUBST_SED.paths+=	-e 's!^LIBPULSE=.*!LIBPULSE="${COMPILER_RPATH_FLAG}${BUILDLINK_PREFIX.pulseaudio}/lib -L${BUILDLINK_PREFIX.pulseaudio}/lib"!g'
SUBST_SED.paths+=	-e 's!^INCPNG=.*!INCPNG="-I${BUILDLINK_PREFIX.png}/include"!g'
SUBST_SED.paths+=	-e 's!^LIBPNG=.*!LIBPNG="${COMPILER_RPATH_FLAG}${BUILDLINK_PREFIX.png}/lib -L${BUILDLINK_PREFIX.png}/lib"!g'
SUBST_SED.paths+=	-e 's!^INCVPX=.*!INCVPX="-I${BUILDLINK_PREFIX.libvpx}/include"!g'
SUBST_SED.paths+=	-e 's!^LIBVPX=.*!LIBVPX="${COMPILER_RPATH_FLAG}${BUILDLINK_PREFIX.libvpx}/lib -L${BUILDLINK_PREFIX.libvpx}/lib -lvpx"!g'

.include "../../audio/pulseaudio/buildlink3.mk"
.include "../../multimedia/libvpx/buildlink3.mk"
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
