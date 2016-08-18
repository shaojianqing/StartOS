#include "../type/type.h"
#include "../error/error.h"
#include "system.h"

int printk(const char *fmt, ...) {
	
}

int sys_alarm() {
	return -ENOSYS;
}

int sys_signal () {
	return -ENOSYS;
}

int sys_getuid() {
	return -ENOSYS;
}

int sys_getgid() {
	return -ENOSYS;
}

int sys_geteuid() {
	return -ENOSYS;
}

int sys_getegid() {
	return -ENOSYS;
}

int sys_sigaction() {
	return -ENOSYS;
}

int sys_sgetmask() {
	return -ENOSYS;
}

int sys_ssetmask() {
	return -ENOSYS;
}