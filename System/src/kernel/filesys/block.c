#include "../type/type.h"
#include "../const/const.h"
#include "../error/error.h"
#include "../system/system.h"
#include "../system/descriptor.h"
#include "../process/process.h"

#include "cache.h"
#include "block.h"

/*
 * The request-struct contains all necessary data
 * to load a nr of sectors into memory
 */
Request requests[REQUEST_SIZE];

/*
 * used to wait on when there are no free requests
 */
Process* waitRequestProcess = NULL;

BlockDevice blockDeviceList[BLOCK_DEVICE_SIZE] = {
	{ NULL, NULL },		/* no_dev */
	{ NULL, NULL },		/* dev mem */
	{ NULL, NULL },		/* dev fd */
	{ NULL, NULL },		/* dev hd */
	{ NULL, NULL },		/* dev ttyx */
	{ NULL, NULL },		/* dev tty */
	{ NULL, NULL }		/* dev lp */
};

void initBlockDevice() {
	int i;

	for (i=0;i<REQUEST_SIZE;i++) {
		requests[i].device = -1;
		requests[i].next = NULL;
	}
}

static void makeRequest(int major, int command, CacheData *cacheData) {
	BlockDevice blockDevice = blockDeviceList[major];

	Request request = requests[0];

	request.startSector = 0;
	request.sectorCount = 2;
	request.buffer = cacheData->data;
	request.command = command;
	
	blockDevice.currentRequest = request;
	blockDevice.requestHandler();
}

void readLowLevelBlock(CacheData *cacheData) {
	if (cacheData!=NULL) {
		u32 major = 0x03;//MAJOR(cacheData->device);
		if (major<BLOCK_DEVICE_SIZE && blockDeviceList[major].requestHandler!=NULL) {
			makeRequest(major, READ, cacheData);
		} else {
			printk("Trying to read nonexistent block-device\n\r");
		} 	
	}
}

void writeLowLevelBlock(CacheData *cacheData) {
	if (cacheData!=NULL) {
		u32 major = MAJOR(cacheData->device);
		if (major<BLOCK_DEVICE_SIZE && blockDeviceList[major].requestHandler!=NULL) {
			makeRequest(major, WRITE, cacheData);
		} else {
			printk("Trying to write nonexistent block-device\n\r");
		} 	
	}
}
