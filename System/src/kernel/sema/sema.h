
typedef struct Semaphore {
	
	u8 value;

	LinkedList waitProcessList;

} Semaphore;

typedef struct Lock {
	
	Process *holder;

	Semaphore *semaphore;

	u32 repeatTimes;

} Lock;
