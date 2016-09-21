#include "../type/type.h"
#include "../const/const.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "../system/system.h"
#include "../filesys/cache.h"
#include "../filesys/block.h"
#include "ramdisk.h"

extern BlockDevice blockDeviceList[BLOCK_DEVICE_SIZE];

static void doRamdiskRequest();

void initRamdiskSetting() {
	int	i = 0;
	byte *data = (byte *)START_RAMDISK;

	blockDeviceList[DEVICE_RAMDISK].requestHandler = doRamdiskRequest;
	for (i=0;i<RAMDISK_SIZE;++i) {
		*data++ = 0x00;
	}	
}

static void doRamdiskRequest() {
	Request *request = &(blockDeviceList[DEVICE_RAMDISK].currentRequest);
	if (request!=NULL) {
		byte *address = (byte *)(START_RAMDISK + (request->startSector<<9));
		u32 length = (request->sectorCount<<9);

		if (MINOR(request->device)==1 && ((u32)(address+length))<RAMDISK_LIMIT) {
			if (request->command==READ) {
				memcopy(request->buffer, address, length);
			} else if (request->command==WRITE) {
				memcopy(address, request->buffer, length);
			} else {
				printk("unknown ramdisk-command\n");
			}
		}
	}
}
