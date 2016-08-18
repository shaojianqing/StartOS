#include "signal.c"
#include "../error/error.h"

int sys_sgetmask() {
	return -ENOSYS;
}

int sys_ssetmask(int newmask) {
	return -ENOSYS;
}