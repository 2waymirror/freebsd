# $FreeBSD: releng/11.0/lib/libc/tests/hash/Makefile 299094 2016-05-04 23:20:53Z ngie $

PACKAGE=	tests

.include <src.opts.mk>

NETBSD_ATF_TESTS_C=

.if ${MK_OPENSSL} != "no"
NETBSD_ATF_TESTS_C+=	sha2_test
.endif

NETBSD_ATF_TESTS_SH=	hash_test

BINDIR=		${TESTSDIR}

PROGS+=		h_hash

FILESGROUPS+=	${PACKAGE}DATA_FILES
${PACKAGE}DATA_FILESPACKAGE=	tests

${PACKAGE}DATA_FILESDIR=	${TESTSDIR}/data

${PACKAGE}DATA_FILES+=	data/md5test-in
${PACKAGE}DATA_FILES+=	data/md5test-out
${PACKAGE}DATA_FILES+=	data/sha1test-in
${PACKAGE}DATA_FILES+=	data/sha1test-out
${PACKAGE}DATA_FILES+=	data/sha1test2-out

LIBADD+=		md
LIBADD.sha2_test+=	crypto

CFLAGS.sha2_test+=	-I${SRCTOP}/crypto/openssh/openbsd-compat
CFLAGS.sha2_test+=	-I${SRCTOP}/crypto/openssh

.include "../Makefile.netbsd-tests"

.include <bsd.test.mk>
