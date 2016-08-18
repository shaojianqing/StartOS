
#define BLOCK_DEVICE_SIZE				7

#define REQUEST_SIZE					32

#define READ 							0x00

#define WRITE 							0x01

#define READA 							0x02		

#define WRITEA 							0x03	

#define MAJOR(a) (((unsigned)(a))>>8)

#define MINOR(a) ((a)&0xff)

typedef struct Request Request;

typedef struct Request {

	int dev;	

	int cmd;	

	int errors;

	u64 sector;

	u64 sectorCount;

	byte *buffer;

	Process *waitProcess;

	CacheData *cacheData;

	Request *next;

} Request;

typedef struct BlockDevice {

	void (*requestHandler)();

	Request currentRequest;

} BlockDevice;