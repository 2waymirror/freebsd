# $FreeBSD: releng/11.0/sbin/ipf/ipf/Makefile 298107 2016-04-16 07:45:30Z gjb $

PACKAGE=	ipf
PROG=		ipf
SRCS=		${GENHDRS} ipf.c ipfcomp.c ipf_y.c ipf_l.c bpf_filter.c
MAN=		ipfilter.4 ipfilter.5 ipf.8 ipf.4 ipf.5 ipl.4
MLINKS=		ipf.5 ipf.conf.5 ipf.5 ipf6.conf.5
CFLAGS+=	-I. -DIPFILTER_BPF -DHAS_SYS_MD5_H

GENHDRS=	ipf_l.h ipf_y.h
CLEANFILES+=	${GENHDRS} ipf_y.c ipf_l.c

ipf_y.c: ipf_y.y
	${YACC} -d ${.ALLSRC}
	sed -e 's/yy/ipf_yy/g' \
	    -e 's/"ipf_y.y"/"..\/tools\/ipf_y.y"/' \
	    y.tab.c > ${.TARGET}
	sed -e 's/yy/ipf_yy/g' \
	    y.tab.h > ${.TARGET:.c=.h}

ipf_y.h: ipf_y.c

ipf_l.c: lexer.c
	sed -e 's/yy/ipf_yy/g' \
	    -e 's/y.tab.h/ipf_y.h/' \
	    -e 's/lexer.h/ipf_l.h/' \
	    ${.ALLSRC} > ${.TARGET}

ipf_l.h: lexer.h
	sed -e 's/yy/ipf_yy/g' \
	    ${.ALLSRC} > ${.TARGET}

.if defined(RESCUE)
LIBIPF_SRCS!=	cd ${.CURDIR}/../libipf && ${MAKE} -V SRCS
SRCS+=	${LIBIPF_SRCS}
.else
LIBADD+=	pcap
.endif

.include <bsd.prog.mk>
