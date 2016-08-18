#include "../type/type.h"
#include "../error/error.h"
#include "filesystem.h"

int sys_ustat() {
	return -ENOSYS;
}

int sys_utime() {
	return -ENOSYS;
}

int sys_access() {
	return -ENOSYS;
}

int sys_chdir(const char *filename) {
	return -ENOSYS;
}

int sys_chroot(const char *filename) {
	return -ENOSYS;
}

int sys_chmod(const char *filename, int mode) {
	return -ENOSYS;
}

int sys_mkdir() {
	return -ENOSYS;
}

int sys_umount() {
	return -ENOSYS;
}

int sys_mount() {
	return -ENOSYS;
}

int sys_chown(const char *filename, int uid, int gid) {
	return -ENOSYS;
}

int sys_open(char *filename, int flags, int mode) {
	char *buffer = (char *)0xb8000;

	*buffer = (char)flags;
	*(buffer+1) = 0x07;

	*(buffer+2) = (char)mode;
	*(buffer+3) = 0x09;

	*(buffer+4) = 's';
	*(buffer+5) = 0x0b;

	*(buffer+6) = 't';
	*(buffer+7) = 0x0d;

	*(buffer+8) = 'e';
	*(buffer+9) = 0x0f;

	*(buffer+10) = 'm';
	*(buffer+11) = 0x03;

	return '&';
}

int sys_creat(const char *pathname, int mode) {
	return -ENOSYS;
}

int sys_close(int fd) {
	char *buffer = (char *)0xb8000;

	*buffer = (char)fd;
	*(buffer+1) = 0x07;

	return 'Q';
}

int sys_ioctl(unsigned int fd, unsigned int cmd, unsigned long arg) {
	return -ENOSYS;
}

int sys_dup2(unsigned int oldfd, unsigned int newfd) {
	return -ENOSYS;
}

int sys_dup(unsigned int fildes) {
	return -ENOSYS;
}

int sys_fcntl(unsigned int fd, unsigned int cmd, unsigned long arg) {
	return -ENOSYS;
}