#include "../const/const.h"
#include "../type/type.h"
#include "time.h"

void initTimingFacility() {
	outByte(PIT_CTRL, 0x34);
	outByte(PIT_CNT0, 0x9c);
	outByte(PIT_CNT0, 0x2e);
}

void intTimeHandler() {
	outByte(PIC0_OCW2, 0x60);
}