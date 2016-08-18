#include "namei.h"
#include "../error/error.h"

int sys_mknod(const char * filename, int mode, int dev) {
	return -ENOSYS;
}

int sys_rmdir(const char * name) {
	return -ENOSYS;
}

int sys_unlink(const char *name) {
	return -ENOSYS;
}

int sys_link(const char *oldname, const char *newname) {
	return -ENOSYS;
}