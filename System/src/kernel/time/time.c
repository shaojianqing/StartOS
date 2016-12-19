#include "../const/const.h"
#include "../type/type.h"
#include "../charset/charset.h"
#include "time.h"

volatile long long systemTiming = 0;

volatile int systemClock = 40;

void initTimingFacility() {
	outByte(PIT_CTRL, 0x34);
	outByte(PIT_CNT0, 0x9c);
	outByte(PIT_CNT0, 0x2e);
}

void intTimeHandler() {
	outByte(PIC0_OCW2, 0x60);
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

long long getSystemTiming() {
	return systemTiming;
}


