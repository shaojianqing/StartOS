#include "../type/type.h"
#include "../const/const.h"
#include "../error/error.h"
#include "../system/descriptor.h"
#include "process.h"

Process *processList[PROCESS_LIST_NUM];

u32 processIndex = 1;

Process* createProcess(u32 entryAddress) {
	/*Process process* = (Process *)allocatePage();
	u32 index = findEmptyProcess();
	if (index<PROCESS_LIST_NUM) {
		processList[i] = process;
		process->pid = processIndex;
		process->tss.eip = entryAddress;
	
		return process;
	} else {
		return NULL;
	}*/
	return NULL;
} 

void startProcess(Process *process) {

}

void sleepProcess(Process **process) {
	
}

static u32 findEmptyProcess() {
	int i=0;
	while(processList[i]!=NULL && i<PROCESS_LIST_NUM) {
		i++;	
	}
	return i;
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
