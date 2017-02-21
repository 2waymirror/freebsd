/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013-2016 Mellanox Technologies, Ltd.
 * Copyright (c) 2015 François Tigeot
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: releng/11.0/sys/compat/linuxkpi/common/include/linux/uaccess.h 299530 2016-05-12 11:38:28Z hselasky $
 */
#ifndef	_LINUX_UACCESS_H_
#define	_LINUX_UACCESS_H_

#include <linux/compiler.h>

#define	__get_user(_x, _p) ({					\
	int __err;						\
	__typeof(*(_p)) __x;					\
	__err = linux_copyin((_p), &(__x), sizeof(*(_p)));	\
	(_x) = __x;						\
	__err;							\
})

#define	__put_user(_x, _p) ({				\
	__typeof(*(_p)) __x = (_x);			\
	linux_copyout(&(__x), (_p), sizeof(*(_p)));	\
})
#define	get_user(_x, _p)	linux_copyin((_p), &(_x), sizeof(*(_p)))
#define	put_user(_x, _p)	linux_copyout(&(_x), (_p), sizeof(*(_p)))

extern int linux_copyin(const void *uaddr, void *kaddr, size_t len);
extern int linux_copyout(const void *kaddr, void *uaddr, size_t len);

/*
 * NOTE: The returned value from pagefault_disable() must be stored
 * and passed to pagefault_enable(). Else possible recursion on the
 * state can be lost.
 */
static inline int __must_check
pagefault_disable(void)
{
	return (vm_fault_disable_pagefaults());
}

static inline void
pagefault_enable(int save)
{
	vm_fault_enable_pagefaults(save);
}

#endif	/* _LINUX_UACCESS_H_ */
