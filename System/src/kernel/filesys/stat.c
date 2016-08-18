#include "stat.h"
#include "../error/error.h"

int sys_stat(char *filename) {
	return -ENOSYS;
}

int sys_fstat(unsigned int fd) {
	return -ENOSYS;
}