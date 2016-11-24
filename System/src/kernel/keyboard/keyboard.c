#include "../const/const.h"
#include "../type/type.h"
#include "../library/filesys.h"
#include "../charset/charset.h"
#include "../console/console.h"
#include "keyboard.h"

int i=0;

extern Console *console;

char charBuffer[3] = {0, 0, 0};

void intKeyboardHandler()
{
	outByte(PIC0_OCW2, 0x61);
	u8 data = inByte(PORT_KEYDATA);
	charBuffer[i%2] = data;

	//int fd = open("shaojianqing", 'R', '5');

	char *buffer = (char *)0xb8000;

	console->print(console, charBuffer, 9);
	//console->clear(console);

	//*(buffer) = fd;
	//*(buffer+1) = 0x09; 

	//int status = close('G');
	i++;
}
