#include "../const/const.h"
#include "../type/type.h"

void printString(int x, int y,char *value, char color) {
	if (value!=NULL && (*value)!='\0') {
		byte *buffer = (byte *)VRAM_ADDRESS;
		u32 i=0;
		while(*(value+i)!='\0') {
			*(buffer+(y*SCREEN_WIDTH+x+i)*2) = *(value+i);
			*(buffer+(y*SCREEN_WIDTH+x+i)*2+1) = color;
			++i;
		}
	}
}

void printInteger(int x, int y, int value, char color) {
	byte *buffer = (byte *)VRAM_ADDRESS;
	if (value>0) {
		u32 i=0;
		while(value>0) {
			*(buffer+(y*SCREEN_WIDTH+x-i)*2) = value%10+0x30;
			*(buffer+(y*SCREEN_WIDTH+x-i)*2+1) = color;
			++i;
			value /= 10;
		}
	} else {
		*(buffer+(y*SCREEN_WIDTH+x)*2) = (byte)value+0x30;
		*(buffer+(y*SCREEN_WIDTH+x)*2+1) = color;	
	}
}
