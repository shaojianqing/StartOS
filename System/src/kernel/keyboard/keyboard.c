#include "../const/const.h"
#include "../type/type.h"
#include "../library/filesys.h"
#include "keyboard.h"

int i=0;

void intKeyboardHandler()
{
	outByte(PIC0_OCW2, 0x61);
	u8 data = inByte(PORT_KEYDATA);

	int fd = open("shaojianqing", 'R', '5');

	char *buffer = (char *)0xb8000;

	//*(buffer) = fd;
	//*(buffer+1) = 0x09; 

	int status = close('G');


}