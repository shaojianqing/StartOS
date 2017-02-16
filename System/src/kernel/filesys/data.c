#include "../error/error.h"
#include "data.h"

int sys_lseek(unsigned int fd, int offset, int origin) {
	return -ENOSYS;
}

int sys_read(unsigned int fd, char *buf, int count) {
	return -ENOSYS;
}

int sys_write(unsigned int fd, char *buf, int count) {
	return -ENOSYS;
}
