# $FreeBSD: releng/11.0/etc/mtree/Makefile 293068 2016-01-03 04:32:05Z imp $

.include <src.opts.mk>

FILES=	${_BSD.debug.dist} \
	BSD.include.dist \
	BSD.root.dist \
	${_BSD.lib32.dist} \
	${_BSD.libsoft.dist} \
	${_BSD.sendmail.dist} \
	${_BSD.tests.dist} \
	BSD.usr.dist \
	BSD.var.dist

.if ${MK_DEBUG_FILES} != "no"
_BSD.debug.dist=	BSD.debug.dist
.endif
.if ${MK_GROFF} != "no"
_BSD.groff.dist=	BSD.groff.dist
.endif
.if ${MK_LIB32} != "no"
_BSD.lib32.dist=	BSD.lib32.dist
.endif
.if ${MK_LIBSOFT} != "no"
_BSD.libsoft.dist=	BSD.libsoft.dist
.endif
.if ${MK_SENDMAIL} != "no"
_BSD.sendmail.dist=	BSD.sendmail.dist
.endif
.if ${MK_TESTS} != "no"
_BSD.tests.dist=	BSD.tests.dist
.endif

NO_OBJ=
FILESDIR= /etc/mtree

.include <bsd.prog.mk>
