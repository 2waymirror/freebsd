#!/bin/sh
#
# $FreeBSD: releng/11.0/usr.bin/less/zless.sh 243834 2012-12-03 21:49:37Z delphij $
#

export LESSOPEN="||/usr/bin/lesspipe.sh %s"
exec /usr/bin/less "$@"
