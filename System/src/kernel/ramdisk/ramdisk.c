#include "../type/type.h"
#include "../const/const.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "../system/system.h"
#include "../filesys/cache.h"
#include "../filesys/block.h"
#include "ramdisk.h"

extern BlockDevice blockDevice[BLOCK_DEVICE_SIZE];

static void doRamdiskRequest();

void initRamdiskSetting() {
	int	i = 0;
	byte *data = (byte *)START_RAMDISK;

	blockDevice[RAMDISK_DEV].requestHandler = doRamdiskRequest;
	for (i=0;i<RAMDISK_SIZE;++i) {
		*data++ = 0x00;
	}	
}

static void doRamdiskRequest() {
	Request *request = &(blockDevice[RAMDISK_DEV].currentRequest);
	if (request!=NULL) {
		byte *address = (byte *)(START_RAMDISK + (request->sector<<9));
		u32 length = (request->sectorCount<<9);

		if (MINOR(request->dev)==1 && ((u32)(address+length))<RAMDISK_LIMIT) {
			if (request->cmd==READ) {
				memcopy(request->buffer, address, length);
			} else if (request->cmd==WRITE) {
				memcopy(address, request->buffer, length);
			} else {
				printk("unknown ramdisk-command\n");
			}
		}
	}
}