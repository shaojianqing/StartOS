#include "../const/const.h"
#include "../type/type.h"
#include "harddisk.h"

void intHarddiskHandler()
{
	inByte(REG_STATUS);
	outByte(0x20, 0xA0);
	outByte(0x20, 0x20);
	return;
}