#include "../const/const.h"
#include "../type/type.h"
#include "console.h"

static void clear(Console *this);

static void print(Console *this, char *message, char color);

Console systemConsole;

Console *console;

void initConsoleSetting() {
	systemConsole.buffer = (byte *)VRAM_ADDRESS;
	systemConsole.width = SCREEN_WIDTH;
	systemConsole.height = SCREEN_HEIGHT;
	systemConsole.currentX = 0;
	systemConsole.currentY = 0;
	systemConsole.clear = clear;
	systemConsole.print = print;
	
	console = &systemConsole;
}

static void clear(Console *this) {
	if (this!=NULL) {
		int i=0;
		int size = this->width*this->height*2;
		for (i=0;i<size;++i) {
			*(this->buffer+i) = 0x00;
		}
	}
}

static void print(Console *this, char *message, char color) {
	if (this!=NULL && message!=NULL) {
		int i=0, start=this->currentY*SCREEN_WIDTH+this->currentX;
		byte *buffer = (byte *)(this->buffer+start*2);
		while(message[i]!='\0') {
			if (message[i]!='\n' && message[i]!='\r') {
				buffer[i*2] = message[i];
				buffer[i*2+1] = color;
				this->currentX++;
				if (this->currentX>=this->width) {
					this->currentX = 0;
					this->currentY++;			
				}
			} else {
				this->currentX = 0;
				this->currentY++;
				buffer = buffer + this->currentY*this->width*2;
			}
			i++;
		}
	}
}

