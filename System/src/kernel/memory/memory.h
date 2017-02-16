
#define START_MEMORY_ADDRESS	(1*1024*1024)
#define END_MEMORY_ADDRESS		(32*1024*1024)
#define MEMORY_PAGE_SIZE		(4*1024)
#define MEMORY_PAGE_NUM			(1024)

void initMemorySetting();

u32 allocatePage();

void releasePage(u32 addr);

void* memset(void *src, byte data, u32 count);
