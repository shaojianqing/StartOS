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

typedef struct Command
{
    u8 features;
	
	u8 count;

	u8 lbaLow;

	u8 lbaMid;

	u8 lbaHigh;

	u8 device;

	u8 command;

} Command;

Command command;

static void doHarddiskRequest();

void initHarddiskSetting() {


	//blockDeviceList[DEVICE_HARD_DISK].requestHandler = doHarddiskRequest;
}

int sys_setup() {
	return 0;
}

void intHarddiskHandler() {
	inByte(REG_STATUS);
	outByte(0x20, 0xA0);
	outByte(0x20, 0x20);

	console->putChar(console, 'M', 15);

	return;
}

bool waitForStatus(int mask, int val, int timeout) 
{
	long long time = getSystemTiming();
	while((getSystemTiming() - time)<timeout) {
		if ((inByte(REG_STATUS) & mask) == val)	{
			return true;	
		}
	}
	return false;
}

bool sendCommand(Command *command)
{
	if (waitForStatus(STATUS_BSY, 0, HD_TIMEOUT) == true) {
		outByte(REG_DEV_CTRL, 0);
		outByte(REG_FEATURES, command->features);
		outByte(REG_NSECTOR, command->count);
		outByte(REG_LBA_LOW, command->lbaLow);
		outByte(REG_LBA_MID, command->lbaMid);
		outByte(REG_LBA_HIGH, command->lbaHigh);
		outByte(REG_DEVICE, command->device);
		outByte(REG_CMD, command->command);

		return true;
	} else {
		return false;	
	}
}

void readHardSector(u32 sector, u8 *buffer, int sectorCount, int size)
{
  	command.features = 0;
	command.count = sectorCount;
	command.lbaLow	= sector & 0xFF;
	command.lbaMid	= (sector >>  8) & 0xFF;
	command.lbaHigh	= (sector >> 16) & 0xFF;

	command.device = MAKE_DEVICE_REG(1, 0, (sector >> 24) & 0xF);
	command.command = ATA_READ;
	
	sendCommand(&command);
	int sectorLeft = command.count;
	while (sectorLeft>0 && size>0) {
		u32 sectorSize = (size<512?size:512);	
		waitForStatus(STATUS_BSY, 0, HD_TIMEOUT);
		readPort(REG_DATA, buffer, sectorSize);
		buffer+=512;
		sectorLeft--;
	}
}

void readHardDisk(u32 sector, u8 *buffer, int size)
{
	while (size>0) {
		int sectorCount = (size/512)>255?255:(size/512+1);
		readHardSector(sector, buffer, sectorCount, size);
		sector += sectorCount;
		buffer += sectorCount*512;
		size -= sectorCount*512;
	}
}

void readDataBlock(CacheData *cacheData) {

	console->putChar(console, 'A', 11);	

	u8 *buffer = (u8 *)(5*1024*1024);
	
	readHardDisk(2, buffer, 1024*4);

	buffer = (u8 *)(5*1024*1024);
	
	char c = buffer[0];

	console->putChar(console, c, 9);	
}

void writeDataBlock(CacheData *cacheData) {
	
}

void doHarddiskRequest() {
	
}


