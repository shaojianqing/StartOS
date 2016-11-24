#include "../const/const.h"
#include "../type/type.h"
#include "../charset/charset.h"
#include "time.h"

int systemTiming = 0;

int systemClock = 40;

void initTimingFacility() {
	outByte(PIT_CTRL, 0x34);
	outByte(PIT_CNT0, 0x9c);
	outByte(PIT_CNT0, 0x2e);
}

void intTimeHandler() {
	outByte(PIC0_OCW2, 0x60);

	byte *buffer = (byte *)0xb8008;
	systemTiming++;

	//printInteger(10, 4, systemTiming, 0x07);

	/*if (systemClock>0) {
		
		*(buffer) = 124;
		*(buffer+1) = 0x05;
	} else if (systemClock<=0) {
		*(buffer) = 0x00;
		*(buffer+1) = 0x00;
		if (systemClock==-40) {
			systemClock=40;
		}
	}
	systemClock--;*/
}
