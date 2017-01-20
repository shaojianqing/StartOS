#include "../const/const.h"
#include "../type/type.h"
#include "console.h"

static void clear(Console *this);

static void scrollScreen(Console *this);

static void printByte(Console *this, byte value, char color);

static void putBinary(Console *this, byte data, char color);

static void print(Console *this, char *message, char color);

static void printInteger(Console *this, u32 data, char color);

static void putChar(Console *this, char c, char color);

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
	systemConsole.putBinary = putBinary;
	systemConsole.printInteger = printInteger;
	systemConsole.scrollScreen = scrollScreen;
	systemConsole.printByte = printByte;
	systemConsole.putChar = putChar;
	
	console = &systemConsole;
}

static void printByte(Console *this, byte value, char color) {
	if (this!=NULL) {
		int i=1, start = this->currentY*SCREEN_WIDTH+this->currentX;
		byte *buffer = (byte *)(this->buffer+start*2);
		while(i>=0) {

			byte digit = value%16;
			if (digit<10) {
				buffer[i*2] = '0'+ digit;
				buffer[i*2+1] = color;
			} else {
				buffer[i*2] = 'A'+ (digit-10);
				buffer[i*2+1] = color;
			}
			--i;
			value /= 16;
			this->currentX++;
			if (this->currentX>=this->width) {
				this->currentX = 0;
				if (this->currentY<this->height-1) {
					this->currentY++;		
				} else {
					this->scrollScreen(this);					
				}
			}
		}
	}
}

static void clear(Console *this) {
	if (this!=NULL) {
		int i=0;
		int size = this->width*this->height*2;
		for (i=0;i<size;++i) {
			*(this->buffer+i) = 0x00;
		}
		this->currentX = 0;
		this->currentY = 0;
		setCursor(0);
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
					if (this->currentY<this->height-1) {
						this->currentY++;		
					} else {
						this->scrollScreen(this);					
					}
				}
			} else {
				this->currentX = 0;
				if (this->currentY<this->height-1) {
					this->currentY++;		
				} else {
					this->scrollScreen(this);					
				}
				buffer = buffer + this->currentY*this->width*2;
			}
			i++;
		}
		start=this->currentY*SCREEN_WIDTH+this->currentX;
		setCursor(start);
	}
}

static void putChar(Console *this, char c, char color) {
	if (this!=NULL && c!=0) {
		int start=this->currentY*SCREEN_WIDTH+this->currentX;
		byte *buffer = (byte *)(this->buffer+start*2);
		if (c!='\n' && c!='\r') {
			buffer[0] = c;
			buffer[1] = color;
			this->currentX++;
			if (this->currentX>=this->width) {
				this->currentX = 0;
				if (this->currentY<this->height-1) {
					this->currentY++;		
				} else {
					this->scrollScreen(this);					
				}
			}
		} else {
			this->currentX = 0;
			if (this->currentY<this->height-1) {
				this->currentY++;		
			} else {
				this->scrollScreen(this);					
			}
		}
		setCursor(start);
	}
}

static void putBinary(Console *this, byte data, char color) {
	if (this!=NULL) {
		int i = 7, start=this->currentY*SCREEN_WIDTH+this->currentX;
		byte *buffer = (byte *)(this->buffer+start*2);
		if (data>0) {
			while(i>=0) {
				char c = '0';
				if (data%2==1) {
					c = '1';				
				} else {
					c = '0';
				}				
				
				data = data/2;
	
				buffer[i*2] = c;
				buffer[i*2+1] = color;
				i--;
			}
		} else {
			for (i=0;i<8;i++) {
				buffer[i*2] = '0';
				buffer[i*2+1] = color;
			}
		}
		this->currentX+=8;
		if (this->currentX>=this->width) {
			this->currentX = 0;
			if (this->currentY<this->height-1) {
				this->currentY++;		
			} else {
				this->scrollScreen(this);					
			}
		}
	}	
}

static void printInteger(Console *this, u32 data, char color) {
	if (this!=NULL) {
		int i = 7, start=this->currentY*SCREEN_WIDTH+this->currentX;
		byte *buffer = (byte *)(this->buffer+start*2);
		if (data>0) {
			while(i>=0) {
				char c = data%10 + '0';	
				data = data/10;
	
				buffer[i*2] = c;
				buffer[i*2+1] = color;
				i--;
			}
		} else {
			for (i=0;i<8;i++) {
				buffer[i*2] = '0';
				buffer[i*2+1] = color;
			}
		}
		this->currentX+=8;
		if (this->currentX>=this->width) {
			this->currentX = 0;
			if (this->currentY<this->height-1) {
				this->currentY++;		
			} else {
				this->scrollScreen(this);					
			}
		}		
	}
}

static void scrollScreen(Console *this) {
	if (this!=NULL) {
		int i=0, j=0;
		byte *buffer = this->buffer;
		for (i=0;i<this->height-1;++i) {
			for (j=0;j<this->width;++j) {
				buffer[(i*this->width+j)*2] = buffer[((i+1)*this->width+j)*2];
				buffer[(i*this->width+j)*2+1] = buffer[((i+1)*this->width+j)*2+1];		
			}	
		}

		for (j=0;j<this->width;++j) {
			buffer[(i*this->width+j)*2] = 0;
			buffer[(i*this->width+j)*2+1] = 0;	
		}
	}
}

