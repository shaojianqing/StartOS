#include "../type/type.h"
#include "../error/error.h"
#include "../system/descriptor.h"
#include "process.h"

void sleepProcess(Process **process) {
	
}

int sys_fork() {
	return -ENOSYS;
}

int sys_kill(int pid,int sig) {
	return -ENOSYS;
}

int sys_exit(int error_code) {
	return -ENOSYS;
}

int sys_waitpid(int pid, unsigned long *stat_addr, int options) {
	return -ENOSYS;
}

int sys_execve() {
	return -ENOSYS;
}

int sys_getpid() {
	return -ENOSYS;
}

int sys_pause() {
	return -ENOSYS;
}

int sys_nice() {
	return -ENOSYS;
}

int sys_getppid() {
	return -ENOSYS;
}