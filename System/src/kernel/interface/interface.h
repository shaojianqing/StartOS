#define INT_SYSTEM_INTERFACE				0x80

void initSystemInterface();

typedef int (*SysCallFun)();

extern int sys_open();

extern int sys_close();
