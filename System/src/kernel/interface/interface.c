#include "../type/type.h"
#include "../system/descriptor.h"
#include "interface.h"

void systemIntface();

SysCallFun systemCallTable[] = {sys_open, sys_close};

void initSystemInterface() {

	setInterruptDescriptor(INT_SYSTEM_INTERFACE, (int)systemIntface, SYSTEM_CODE, AR_INTGATE32);
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

int sys_close(int fd) {
	char *buffer = (char *)0xb8000;

	*buffer = (char)fd;
	*(buffer+1) = 0x07;

	return 'Q';
}