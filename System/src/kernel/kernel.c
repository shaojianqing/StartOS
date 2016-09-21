#include "type/type.h"
#include "const/const.h"
#include "time/time.h"
#include "system/descriptor.h"
#include "process/process.h"
#include "filesys/cache.h"
#include "system/interrupt.h"
#include "ramdisk/ramdisk.h"
#include "harddisk/harddisk.h"
#include "interface/interface.h"

void initSystem(void)
{
	initBlockDevice();
	initSystemCache();
	initTimingFacility();
	initRamdiskSetting();
	initHarddiskSetting();
	initSystemInterface();
	initInterruptHandler();

	CacheData *cacheData = (CacheData *)START_CACHE;
	cacheData->device = 0x00;
	readLowLevelBlock(cacheData);

	while(true) {
		
	}
}
