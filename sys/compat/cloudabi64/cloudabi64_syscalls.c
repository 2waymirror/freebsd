/*
 * System call names.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $FreeBSD: releng/11.0/sys/compat/cloudabi64/cloudabi64_syscalls.c 297469 2016-03-31 18:50:52Z ed $
 * created from FreeBSD: head/sys/contrib/cloudabi/syscalls.master 297468 2016-03-31 18:50:06Z ed 
 */

const char *cloudabi64_syscallnames[] = {
	"cloudabi_sys_clock_res_get",			/* 0 = cloudabi_sys_clock_res_get */
	"cloudabi_sys_clock_time_get",			/* 1 = cloudabi_sys_clock_time_get */
	"cloudabi_sys_condvar_signal",			/* 2 = cloudabi_sys_condvar_signal */
	"cloudabi_sys_fd_close",			/* 3 = cloudabi_sys_fd_close */
	"cloudabi_sys_fd_create1",			/* 4 = cloudabi_sys_fd_create1 */
	"cloudabi_sys_fd_create2",			/* 5 = cloudabi_sys_fd_create2 */
	"cloudabi_sys_fd_datasync",			/* 6 = cloudabi_sys_fd_datasync */
	"cloudabi_sys_fd_dup",			/* 7 = cloudabi_sys_fd_dup */
	"cloudabi64_sys_fd_pread",			/* 8 = cloudabi64_sys_fd_pread */
	"cloudabi64_sys_fd_pwrite",			/* 9 = cloudabi64_sys_fd_pwrite */
	"cloudabi64_sys_fd_read",			/* 10 = cloudabi64_sys_fd_read */
	"cloudabi_sys_fd_replace",			/* 11 = cloudabi_sys_fd_replace */
	"cloudabi_sys_fd_seek",			/* 12 = cloudabi_sys_fd_seek */
	"cloudabi_sys_fd_stat_get",			/* 13 = cloudabi_sys_fd_stat_get */
	"cloudabi_sys_fd_stat_put",			/* 14 = cloudabi_sys_fd_stat_put */
	"cloudabi_sys_fd_sync",			/* 15 = cloudabi_sys_fd_sync */
	"cloudabi64_sys_fd_write",			/* 16 = cloudabi64_sys_fd_write */
	"cloudabi_sys_file_advise",			/* 17 = cloudabi_sys_file_advise */
	"cloudabi_sys_file_allocate",			/* 18 = cloudabi_sys_file_allocate */
	"cloudabi_sys_file_create",			/* 19 = cloudabi_sys_file_create */
	"cloudabi_sys_file_link",			/* 20 = cloudabi_sys_file_link */
	"cloudabi_sys_file_open",			/* 21 = cloudabi_sys_file_open */
	"cloudabi_sys_file_readdir",			/* 22 = cloudabi_sys_file_readdir */
	"cloudabi_sys_file_readlink",			/* 23 = cloudabi_sys_file_readlink */
	"cloudabi_sys_file_rename",			/* 24 = cloudabi_sys_file_rename */
	"cloudabi_sys_file_stat_fget",			/* 25 = cloudabi_sys_file_stat_fget */
	"cloudabi_sys_file_stat_fput",			/* 26 = cloudabi_sys_file_stat_fput */
	"cloudabi_sys_file_stat_get",			/* 27 = cloudabi_sys_file_stat_get */
	"cloudabi_sys_file_stat_put",			/* 28 = cloudabi_sys_file_stat_put */
	"cloudabi_sys_file_symlink",			/* 29 = cloudabi_sys_file_symlink */
	"cloudabi_sys_file_unlink",			/* 30 = cloudabi_sys_file_unlink */
	"cloudabi_sys_lock_unlock",			/* 31 = cloudabi_sys_lock_unlock */
	"cloudabi_sys_mem_advise",			/* 32 = cloudabi_sys_mem_advise */
	"cloudabi_sys_mem_lock",			/* 33 = cloudabi_sys_mem_lock */
	"cloudabi_sys_mem_map",			/* 34 = cloudabi_sys_mem_map */
	"cloudabi_sys_mem_protect",			/* 35 = cloudabi_sys_mem_protect */
	"cloudabi_sys_mem_sync",			/* 36 = cloudabi_sys_mem_sync */
	"cloudabi_sys_mem_unlock",			/* 37 = cloudabi_sys_mem_unlock */
	"cloudabi_sys_mem_unmap",			/* 38 = cloudabi_sys_mem_unmap */
	"cloudabi64_sys_poll",			/* 39 = cloudabi64_sys_poll */
	"cloudabi_sys_proc_exec",			/* 40 = cloudabi_sys_proc_exec */
	"cloudabi_sys_proc_exit",			/* 41 = cloudabi_sys_proc_exit */
	"cloudabi_sys_proc_fork",			/* 42 = cloudabi_sys_proc_fork */
	"cloudabi_sys_proc_raise",			/* 43 = cloudabi_sys_proc_raise */
	"cloudabi_sys_random_get",			/* 44 = cloudabi_sys_random_get */
	"cloudabi_sys_sock_accept",			/* 45 = cloudabi_sys_sock_accept */
	"cloudabi_sys_sock_bind",			/* 46 = cloudabi_sys_sock_bind */
	"cloudabi_sys_sock_connect",			/* 47 = cloudabi_sys_sock_connect */
	"cloudabi_sys_sock_listen",			/* 48 = cloudabi_sys_sock_listen */
	"cloudabi64_sys_sock_recv",			/* 49 = cloudabi64_sys_sock_recv */
	"cloudabi64_sys_sock_send",			/* 50 = cloudabi64_sys_sock_send */
	"cloudabi_sys_sock_shutdown",			/* 51 = cloudabi_sys_sock_shutdown */
	"cloudabi_sys_sock_stat_get",			/* 52 = cloudabi_sys_sock_stat_get */
	"cloudabi64_sys_thread_create",			/* 53 = cloudabi64_sys_thread_create */
	"cloudabi_sys_thread_exit",			/* 54 = cloudabi_sys_thread_exit */
	"cloudabi_sys_thread_tcb_set",			/* 55 = cloudabi_sys_thread_tcb_set */
	"cloudabi_sys_thread_yield",			/* 56 = cloudabi_sys_thread_yield */
	"cloudabi64_sys_poll_fd",			/* 57 = cloudabi64_sys_poll_fd */
};
