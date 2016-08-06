#include "const/const.h"
#include "time/time.h"
#include "system/interrupt.h"
#include "interface/interface.h"

void initSystem(void)
{
	initTimingFacility();
	initInterruptHandler();
	initSystemInterface();

	asm volatile ("hlt");
}