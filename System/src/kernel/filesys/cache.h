#define START_CACHE			(1*1024*1024)

#define CACHE_LIMIT			(4*1024*1024)

#define CACHE_HASH_SIZE		307

#define READ 				0x00

#define WRITE 				0x01

#define READA 				0x02

#define WRITEA 				0x03

#define BADNESS(cacheData) (((cacheData)->isDirty<<1)+(cacheData)->isLock)

typedef struct CacheData CacheData;

struct CacheData {

	byte *data;				/* pointer to data block (1024 bytes) */

	u64 block;				/* block number */

	u16 device;				/* device (0 = free) */

	bool isUptoDate;

	bool isDirty;			/* 0-clean,1-dirty */

	u8 count;				/* users using this block */

	bool isLock;			/* 0 - ok, 1 -locked */

	Process *waitProcess;

	CacheData *prev;

	CacheData *next;

	CacheData *prevFree;

	CacheData *nextFree;
};

void initSystemCache();

CacheData *readBlock(int dev, int block);

void releaseBlock(CacheData *cacheData);
