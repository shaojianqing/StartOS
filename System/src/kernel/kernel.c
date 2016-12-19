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

void initSystem(void)
{
	initBlockDevice();
	initSystemCache();
	initMemorySetting();
	initTimingFacility();
	initConsoleSetting();
	initRamdiskSetting();
	initHarddiskSetting();
	initSystemInterface();
	initInterruptHandler();
	setupInterrupt();

	console->print(console, "shaojianqing\n", 13);

	/*byte *area0 = (byte *)allocatePage();
	byte *area1 = (byte *)allocatePage();
	byte *area2 = (byte *)allocatePage();
	byte *area3 = (byte *)allocatePage();
	byte *area4 = (byte *)allocatePage();
	byte *area5 = (byte *)allocatePage();
	byte *area6 = (byte *)allocatePage();
	byte *area7 = (byte *)allocatePage();
	byte *area8 = (byte *)allocatePage();
	byte *area9 = (byte *)allocatePage();
	byte *area10 = (byte *)allocatePage();
	byte *area11 = (byte *)allocatePage();

	releasePage((u32)area4);
	releasePage((u32)area2);

	releasePage((u32)area9);

	releasePage((u32)area10);*/


	CacheData *cacheData = (CacheData *)START_CACHE;
	cacheData->device = 0x00;
	readLowLevelBlock(cacheData);

	while(true) {
		
	}
}
