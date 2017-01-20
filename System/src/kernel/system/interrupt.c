#include "../type/type.h"
#include "descriptor.h"
#include "interrupt.h"

void initInterruptHandler()
{
	setInterruptDescriptor(INTERRUPT_TIMING, (int)asmIntHandler20, SYSTEM_CODE, AR_INTGATE32);
	setInterruptDescriptor(INTERRUPT_KEYBOARD, (int)asmIntHandler21, SYSTEM_CODE, AR_INTGATE32);
	setInterruptDescriptor(INTERRUPT_HARDDISK, (int)asmIntHandler2e, SYSTEM_CODE, AR_INTGATE32);
	loadIdtr(LIMIT_IDT, ADDRESS_IDT);	
}