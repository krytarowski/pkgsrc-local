# $NetBSD$

DISTNAME=	djvu2pdf-0.9.2
CATEGORIES=	print
MASTER_SITES=	http://0x2a.at/site/projects/djvu2pdf/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://0x2a.at/s/projects/djvu2pdf/
COMMENT=	Small tool to convert Djvu files to PDF files
LICENSE=	generic-nonlicense

USE_LANGUAGES=	# none

NO_BUILD=	yes

DEPENDS+=	djvulibre-tools-[0-9]*:../../graphics/djvulibre-tools

INSTALLATION_DIRS=	bin ${PKGMANDIR}/man1

MANCOMPRESSED=	yes

do-install:
	cd ${WRKSRC} && ${INSTALL_SCRIPT} \
		djvu2pdf ${DESTDIR}${PREFIX}/bin
	cd ${WRKSRC} && ${INSTALL_DATA} \
		djvu2pdf.1.gz ${DESTDIR}${PREFIX}/${PKGMANDIR}/man1

.include "../../print/ghostscript/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
