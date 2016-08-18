#include "type/type.h"
#include "const/const.h"
#include "time/time.h"
#include "system/interrupt.h"
#include "ramdisk/ramdisk.h"
#include "harddisk/harddisk.h"
#include "interface/interface.h"

void initSystem(void)
{
	initBlockDevice();
	initSystemCache();
	initTimingFacility();
	initInterruptHandler();
	initRamdiskSetting();
	initHarddiskSetting();
	initSystemInterface();

	while(true) {
		
	}
}