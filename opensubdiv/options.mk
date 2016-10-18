# $NetBSD: options.mk,v 1.9 2015/04/13 23:22:03 othyro Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.opensubdiv
PKG_SUPPORTED_OPTIONS=	glew ptex doc # cuda tbb opencl dx11
PKG_SUGGESTED_OPTIONS=	glew

.include 		"../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Mglew)
.include "../../security/openssl/buildlink3.mk"
PLIST_SRC+=		PLIST.openssl
CONFIGURE_ARGS+=	--enable-perl
USE_TOOLS+=		perl
.endif

.if !empty(PKG_OPTIONS:Mdoc)
.include "../../security/openssl/buildlink3.mk"
PLIST_SRC+=		PLIST.openssl
CONFIGURE_ARGS+=	--enable-perl
USE_TOOLS+=		perl
.endif

.if !empty(PKG_OPTIONS:Mglew)
.include "../../security/openssl/buildlink3.mk"
PLIST_SRC+=		PLIST.openssl
CONFIGURE_ARGS+=	--enable-perl
USE_TOOLS+=		perl
.endif
