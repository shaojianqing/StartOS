#include "../const/const.h"
#include "../type/type.h"
#include "../time/time.h"
#include "../system/system.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "../console/console.h"
#include "../filesys/cache.h"
#include "../filesys/block.h"
#include "harddisk.h"

extern Console *console;

HarddiskInfo hardDiskInfo;

u32 partitionCount = DEFAULT_PARTITION_COUNT;

Partition partitionTable[DEFAULT_PARTITION_COUNT];

static inline void insw(u16 port, byte* buffer, u32 dataCount) {
   asm volatile ("cld; rep insw" : "+D" (buffer), "+c" (dataCount) : "d" (port) : "memory");
}

static inline void outsw(u16 port, const byte* buffer, u32 dataCount) {
   asm volatile ("cld; rep outsw" : "+S" (buffer), "+c" (dataCount) : "d" (port));
}

static void resetController();

static void doHarddiskRequest();

void initHarddiskSetting() {
	int i=0;

	Partition *partition = (Partition *)PARTITION_TABLE;
	while((partition+i)->totalSectCount!=0) {
		(partitionTable+i)->startSector = (partition+i)->startSector;
		(partitionTable+i)->totalSectCount = (partition+i)->totalSectCount;
		++i;
	}
	partitionCount = i;

	byte *BIOS = (byte *)BIOS_ADDRESS;
	hardDiskInfo.cyl = *(u16 *) BIOS;
	hardDiskInfo.head = *(u8 *) (2+BIOS);
	hardDiskInfo.wpcom = *(u16 *) (5+BIOS);
	hardDiskInfo.ctl = *(u8 *) (8+BIOS);
	hardDiskInfo.lzone = *(u16 *) (12+BIOS);
	hardDiskInfo.sect = *(u8 *) (14+BIOS);

	outByte(0x21, inByte(0x21)&0xfb);
	outByte(0xA1, inByte(0xA1)&0xbf);
}

int sys_setup() {
	return 0;
}

void intHarddiskHandler() {
	outByte(0x20, 0xA0);
	outByte(0x20, 0x20);
	inByte(REG_STATUS);
}

static void selectHardDisk() {
   outByte(REG_DEVICE, (BIT_DEV_MBS|BIT_DEV_LBA));
}

static void selectSector(u32 sectorLba, u32 sectorCount) {
	outByte(REG_NSECTOR, sectorCount);
	outByte(REG_LBA_LOW, (sectorLba & 0xFF));
	outByte(REG_LBA_MID, ((sectorLba >>  8) & 0xFF));
	outByte(REG_LBA_HIGH, ((sectorLba >> 16) & 0xFF));
	outByte(REG_DEVICE, (BIT_DEV_MBS | BIT_DEV_LBA | sectorLba>>24));
}

static void sendCommand(u8 command) {
	outByte(REG_COMMAND, command);
}

static void readFromSector(byte* buffer, u8 sectCount) {
	u32 size = 0;
	if (sectCount==0) {
		size = 256*512;	
	} else {
		size = sectCount*512;
	}
	insw(REG_DATA, buffer, size/2);	
}

static bool waitStatus(int timeout) {
	long long time = getSystemTiming();
	while(getSystemTiming() - time<timeout) {
		if (!(inByte(REG_STATUS) & BIT_STAT_BSY))	{
			return (inByte(REG_STATUS) & BIT_STAT_DRQ);
		}
	}
	return false;
}

void readHardDisk(u32 lba, byte* buffer, u32 sectorCount) {   

   selectHardDisk();

   u32 sectorOperate;
   u32 sectorDone = 0;
   while(sectorDone < sectorCount) {
      if ((sectorDone + 256) <= sectorCount) {
	        sectorOperate = 256;
      } else {
	        sectorOperate = sectorCount - sectorDone;
      }
      selectSector(lba + sectorDone, sectorOperate);
      sendCommand(ATA_READ);

      if (waitStatus(10000)) {
		 readFromSector(buffer+sectorDone*512, sectorOperate);
		 sectorDone += sectorOperate;
      }
   }
}

void readDataBlock(CacheData *cacheData) {	
	readHardDisk(cacheData->block*2, cacheData->data, 2);
}

static void writeToSector(byte *buffer, u8 sectCount) {
   u32 size = 0;
   if (sectCount == 0) {
      size = 256*512;
   } else { 
      size = sectCount*512; 
   }
   outsw(REG_DATA, buffer, size/2);
}

void writeHardDisk(u32 lba, byte* buffer, u32 sectorCount) {
	
	selectHardDisk();

	u32 sectorOperate;
	u32 sectorDone = 0;
	while(sectorDone < sectorCount) {
		if ((sectorDone + 256) <= sectorCount) {
			sectorOperate = 256;
		} else {
			sectorOperate = sectorCount - sectorDone;
		}
		selectSector(lba + sectorDone, sectorOperate);
		sendCommand(ATA_WRITE);
		
		if (waitStatus(10000)) {
			writeToSector(buffer+sectorDone*512, sectorOperate);
			sectorDone += sectorOperate;
		}
	}
}

void writeDataBlock(CacheData *cacheData) {
	writeHardDisk(cacheData->block*2, cacheData->data, 2);
}
