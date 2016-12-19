#include "../type/type.h"
#include "../const/const.h"
#include "../error/error.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "../system/system.h"
#include "filesystem.h"
#include "cache.h"

int totalCacheSize = 0;

CacheData *startFreeEntry = NULL;

CacheData *cacheHashTable[CACHE_HASH_SIZE];

static inline void waitOnCache(CacheData *cacheData);

static inline u32 hashFunction(int device, int block);

static inline void removeFromQueue(CacheData *cacheData);

static CacheData* findCacheData(int device, int block);

static CacheData* getCacheInHashTable(int device, int block);

static CacheData *getCacheData(int dev, int block);

void initSystemCache() {
	CacheData *cacheData = (CacheData *)START_CACHE;
	u32 cacheLimit = CACHE_LIMIT;
	u32 i=0;

	while ((cacheLimit-BLOCK_DATA_SIZE)>=((u32)(cacheData+1))) {
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
		cacheLimit-=BLOCK_DATA_SIZE;
		totalCacheSize++;
	}
	cacheData--;
	startFreeEntry = (CacheData *)START_CACHE;
	startFreeEntry->prevFree = cacheData;
	cacheData->nextFree = startFreeEntry;

	for (i=0;i<CACHE_HASH_SIZE;++i) {
		cacheHashTable[i] = NULL;
	}
}

CacheData *readBlock(int dev, int block) {
	CacheData *cacheData = getCacheData(dev, block);
	if (cacheData->isUptoDate) {
		return cacheData;
	} else {
		readDataBlock(cacheData);
		cacheData->isUptoDate = true;
	}
	return cacheData;
}

void releaseBlock(CacheData *cacheData) {
	
}

static inline void removeFromQueue(CacheData *cacheData) {
	if (cacheData!=NULL) {
		if (cacheData->next!=NULL) {
			cacheData->next->prev = cacheData->prev; 		
		}
		if (cacheData->prev!=NULL) {
			cacheData->prev->next = cacheData->next;		
		}

		if (cacheData->prevFree!=NULL && cacheData->nextFree!=NULL) {
			cacheData->prevFree->nextFree = cacheData->nextFree;
			cacheData->nextFree->prevFree = cacheData->prevFree;
			if (startFreeEntry==cacheData) {
				startFreeEntry = cacheData->nextFree;
			}
		}
	}	
}

static inline void insertIntoQueue(CacheData *cacheData) {
	if (cacheData!=NULL) {		
		cacheData->prevFree = startFreeEntry->prevFree;
		startFreeEntry->prevFree->nextFree  = cacheData;
		
		cacheData->nextFree = startFreeEntry;
		startFreeEntry->prevFree = cacheData;

		cacheData->prev = NULL;
		cacheData->next = NULL;
		
		if (cacheData->device!=0) {
			cacheHashTable[hashFunction(cacheData->device, cacheData->block)] = cacheData;	
			CacheData *existCacheData = findCacheData(cacheData->device, cacheData->block);
			if (existCacheData!=NULL) {
				cacheData->next = existCacheData;
				existCacheData->prev = cacheData;
			}
		}
	}	
}

static CacheData *getCacheData(int device, int block) {
	CacheData *cacheData = findCacheData(device, block);
	if (cacheData==NULL) {
		CacheData *temp = startFreeEntry;	
		while (temp->nextFree!=startFreeEntry) {
			if (temp->count==0) {
				if (cacheData==NULL || BADNESS(temp)<BADNESS(cacheData)) {
					cacheData = temp;
					if (BADNESS(temp)==0) {
						break;
					}				
				}				
			}
			temp = temp->nextFree;
		}		
		cacheData->count = 1;
		cacheData->isDirty = false;
		cacheData->isUptoDate = false;
		removeFromQueue(cacheData);
		cacheData->device = device;
		cacheData->block = block;
		insertIntoQueue(cacheData);
	}
	return cacheData;	
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
