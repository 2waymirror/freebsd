# $FreeBSD: releng/11.0/lib/clang/liblldbPluginProcessElfCore/Makefile 288943 2015-10-06 17:53:29Z dim $

.include <bsd.own.mk>

LIB=	lldbPluginProcessElfCore

CFLAGS+=-I${.CURDIR}/../../../contrib/llvm/tools/lldb/source/Plugins/Process/POSIX
CFLAGS+=-I${.CURDIR}/../../../contrib/llvm/tools/lldb/source/Plugins/Process/Utility

SRCDIR=	tools/lldb/source/Plugins/Process/elf-core
SRCS=	ProcessElfCore.cpp \
	ThreadElfCore.cpp \
	RegisterContextPOSIXCore_arm.cpp \
	RegisterContextPOSIXCore_arm64.cpp \
	RegisterContextPOSIXCore_mips64.cpp \
	RegisterContextPOSIXCore_powerpc.cpp \
	RegisterContextPOSIXCore_x86_64.cpp

TGHDRS=	DiagnosticCommonKinds \
	DeclNodes \
	StmtNodes \
	CommentCommandList

.include "../lldb.lib.mk"
