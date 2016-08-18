#include "../type/type.h"
#include "../const/const.h"
#include "../error/error.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "../system/system.h"
#include "filesystem.h"
#include "cache.h"

int CACHE_SIZE = 0;

CacheData *startFreeEntry = NULL;

CacheData *cacheHashTable[CACHE_HASH_SIZE];

void initSystemCache() {
	CacheData *cacheData = (CacheData *)START_CACHE;
	u32 cacheLimit = CACHE_LIMIT;
	u32 i=0;

	while ((cacheLimit-BLOCK_SIZE)>=((u32)(cacheData+1))) {
		cacheData->data = (byte *)cacheLimit;
		cacheData->device = 0;
		cacheData->block = 0;
		cacheData->isUptoDate = false;
		cacheData->isDirty = false;
		cacheData->count = 0;
		cacheData->isLock = 0;
		cacheData->waitProcess = NULL;
		cacheData->prev = NULL;
		cacheData->next = NULL;
		cacheData->prevFree = cacheData-1;
		cacheData->nextFree = cacheData+1;
		cacheData++;
		cacheLimit-=BLOCK_SIZE;
		CACHE_SIZE++;
	}
	cacheData--;
	startFreeEntry = (CacheData *)START_CACHE;
	startFreeEntry->prevFree = cacheData;
	cacheData->nextFree = startFreeEntry;

	for (i=0;i<CACHE_HASH_SIZE;++i) {
		cacheHashTable[i] = NULL;
	}
}

static inline void waitOnCache(CacheData *cacheData) {
	cli();
	while (cacheData->isLock) {
		sleepProcess(&cacheData->waitProcess);
	}
	sti();
}

static inline u32 hashFunction(int device, int block) {
	return (((u32)(device^block))%CACHE_HASH_SIZE);
}

static CacheData* findCacheData(int device, int block) {		
	CacheData *cacheData = cacheHashTable[hashFunction(device, block)];
	while (cacheData!=NULL) {
		if (cacheData->device==device && cacheData->block==block) {
			return cacheData; 
		} else {
			 cacheData = cacheData->next;
		}
	}
	return NULL;
}

static CacheData* getCacheInHashTable(int device, int block) {
	CacheData *cacheData;
	while (true) {
		cacheData = findCacheData(device, block);
		if (cacheData==NULL) {
			return NULL;
		} else {
			cacheData->count++;
			waitOnCache(cacheData);
			if (cacheData->device==device && cacheData->block==block) {
				return cacheData;
			} else {
				cacheData->count--;
			}
		}
	}
}

int sys_sync(void) {
	return -ENOSYS;
}

int sync_dev(int dev) {
	return -ENOSYS;
}
