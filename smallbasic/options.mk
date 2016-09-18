# $NetBSD: options.mk,v 1.1 2015/02/27 12:11:20 gdt Exp $

PKG_OPTIONS_VAR=		PKG_OPTIONS.smallbasic
PKG_SUPPORTED_OPTIONS=		sdl
PKG_SUGGESTED_OPTIONS=		sdl

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Msdl)
.include "../../devel/SDL2/buildlink3.mk"
CONFIGURE_ARGS+=        --enable-sdl
.endif
