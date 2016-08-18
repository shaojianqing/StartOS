#include "../type/type.h"
#include "../system/descriptor.h"
#include "../error/error.h"
#include "interface.h"

void systemIntface();

SysCallFun systemCallTable[] = { sys_setup, sys_exit, sys_fork, sys_read,
								 sys_write, sys_open, sys_close, sys_waitpid, sys_creat, sys_link,
								 sys_unlink, sys_execve, sys_chdir, sys_time, sys_mknod, sys_chmod,
								 sys_chown, sys_break, sys_stat, sys_lseek, sys_getpid, sys_mount,
								 sys_umount, sys_setuid, sys_getuid, sys_stime, sys_ptrace, sys_alarm,
								 sys_fstat, sys_pause, sys_utime, sys_stty, sys_gtty, sys_access,
								 sys_nice, sys_ftime, sys_sync, sys_kill, sys_rename, sys_mkdir,
								 sys_rmdir, sys_dup, sys_pipe, sys_times, sys_prof, sys_brk, sys_setgid,
								 sys_getgid, sys_signal, sys_geteuid, sys_getegid, sys_acct, sys_phys,
								 sys_lock, sys_ioctl, sys_fcntl, sys_mpx, sys_setpgid, sys_ulimit,
								 sys_uname, sys_umask, sys_chroot, sys_ustat, sys_dup2, sys_getppid,
								 sys_getpgrp, sys_setsid, sys_sigaction, sys_sgetmask, sys_ssetmask,
								 sys_setreuid, sys_setregid };

void initSystemInterface() {

	setInterruptDescriptor(INT_SYSTEM_INTERFACE, (int)systemIntface, SYSTEM_CODE, AR_INTGATE32);
}

int sys_ftime()
{
	return -ENOSYS;
}

int sys_break()
{
	return -ENOSYS;
}

int sys_ptrace()
{
	return -ENOSYS;
}

int sys_stty()
{
	return -ENOSYS;
}

int sys_gtty()
{
	return -ENOSYS;
}

int sys_rename()
{
	return -ENOSYS;
}

int sys_prof()
{
	return -ENOSYS;
}

int sys_setregid(int rgid, int egid)
{
	return -ENOSYS;
}

int sys_setgid(int gid)
{
	return(sys_setregid(gid, gid));
}

int sys_acct()
{
	return -ENOSYS;
}

int sys_phys()
{
	return -ENOSYS;
}

int sys_lock()
{
	return -ENOSYS;
}

int sys_mpx()
{
	return -ENOSYS;
}

int sys_ulimit()
{
	return -ENOSYS;
}

int sys_time(long *tloc)
{
	return -ENOSYS;
}

int sys_setreuid(int ruid, int euid)
{
	return -ENOSYS;
}

int sys_setuid(int uid)
{
	return -ENOSYS;
}

int sys_stime(long * tptr)
{
	return -ENOSYS;
}

int sys_times()
{
	return -ENOSYS;
}

int sys_brk(unsigned long end_data_seg)
{
	return -ENOSYS;
}

int sys_setpgid(int pid, int pgid)
{
	return -ENOSYS;
}

int sys_getpgrp()
{
	return -ENOSYS;
}

int sys_setsid()
{
	return -ENOSYS;
}

int sys_uname()
{
	return -ENOSYS;
}

int sys_umask()
{
	return -ENOSYS;
}