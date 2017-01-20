#define MAX_LDT_NUM						4

#define PROCESS_NAME_LENGTH				32

#define PROCESS_LIST_NUM				256

typedef struct Tss
{
	int backlink, esp0, ss0, esp1, ss1, esp2, ss2, cr3;

	int eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;

	int es, cs, ss, ds, fs, gs;

	int ldtr, iomap;
	
} Tss;

/* 
 * The Local Descriptor Table data structure.Representing the
 * local descriptor table of one particiular process.In this OS,
 * I set that every process has at most 4 local segments.
 */
typedef struct Ldt
{
	LocalDescriptor descriptor[MAX_LDT_NUM];
	
} Ldt;

/* 
 * The Process data structure in this OS.It just represents the process
 * running in this OS and contains all kinds of resources that one 
 * process needs to possess, including Tss, Ldt and relative selector, 
 * status, priority and so on.
 */
typedef struct Process
{
	Tss tss;

	Ldt ldt;

	short tssSelector;

	short ldtSelector;

	short status;

	int priority;

	int counter;

	u32 pid;

	char *name;

} Process;

Process* createProcess(u32 entryAddress);

void startProcess(Process *process);

void sleepProcess(Process **process);
