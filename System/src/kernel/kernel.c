#include "type/type.h"
#include "const/const.h"
#include "time/time.h"
#include "system/descriptor.h"
#include "process/process.h"
#include "filesys/cache.h"
#include "console/console.h"
#include "system/interrupt.h"
#include "ramdisk/ramdisk.h"
#include "harddisk/harddisk.h"
#include "interface/interface.h"

extern Console *console;

int video_port_reg	= 0x3d4;

int	video_port_val	= 0x3d5; 

int video_mem_start = 0xb8000;

int pos = 0xb8020;


static void set_cursor(void)
{
    clearInterrupt();
    outByte(14, video_port_reg);
    outByte(0xff&((pos-video_mem_start)>>9), video_port_val);
    outByte(15, video_port_reg);
    outByte(0xff&((pos-video_mem_start)>>1), video_port_val);
    setupInterrupt();
}

void initSystem(void)
{
	initBlockDevice();
	initSystemCache();
	initTimingFacility();
	initConsoleSetting();
	initRamdiskSetting();
	initHarddiskSetting();
	initSystemInterface();
	initInterruptHandler();

	console->print(console, "shaojian\nqing", 13);

	CacheData *cacheData = (CacheData *)START_CACHE;
	cacheData->device = 0x00;
	readLowLevelBlock(cacheData);

	while(true) {
		
	}
}
