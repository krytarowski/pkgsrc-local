# $NetBSD: options.mk,v 1.9 2015/04/13 23:22:03 othyro Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.opensubdiv
PKG_SUPPORTED_OPTIONS=	opengl ptex doc # cuda tbb opencl dx11
PKG_SUGGESTED_OPTIONS=	opengl
PLIST_VARS+=		opengl

.include 		"../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Mopengl)
.include "../../graphics/glew/buildlink3.mk"
CMAKE_ARGS+=	-DGLEW_LOCATION:PATH=${PREFIX}
PLIST.opengl=	yes
.else
CMAKE_ARGS+=	-DNO_OPENGL
.endif

.if !empty(PKG_OPTIONS:Mptex)
.include "../../graphics/glew/buildlink3.mk"
CMAKE_ARGS+=	-DPTEX_LOCATION:PATH=${PREFIX}
#PLIST_SRC+=		PLIST.openssl
#CONFIGURE_ARGS+=	--enable-perl
#USE_TOOLS+=		perl
.else
CMAKE_ARGS+=	-DNO_PTEX:BOOL=ON
.endif

.if !empty(PKG_OPTIONS:Mdoc)
#.include "../../security/openssl/buildlink3.mk"
#PLIST_SRC+=		PLIST.openssl
#CONFIGURE_ARGS+=	--enable-perl
#USE_TOOLS+=		perl
.endif
