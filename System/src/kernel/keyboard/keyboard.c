#include "../const/const.h"
#include "../type/type.h"
#include "../library/filesys.h"
#include "../charset/charset.h"
#include "../console/console.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "../filesys/cache.h"
#include "keyboard.h"

#define esc			'\x1b'	 // 八进制表示字符,也可以用十六进制'\x1b'
#define backSpace	'\b'
#define tab			'\t'
#define enter		'\n'
#define delete		'\177'	 // 八进制表示字符,十六进制为'\x7f'

/* 以上不可见字符一律定义为0 */
#define charInvisible		0x00
#define ctrlLeft			0x00
#define ctrlRight			0x00
#define shiftLeft			0x00
#define shiftRight			0x00
#define altLeft				0x00
#define altRight			0x00
#define capsLock			0x00

/* 定义控制字符的通码和断码 */
#define shift_l_make	0x2a
#define shift_r_make 	0x36 
#define alt_l_make   	0x38
#define alt_r_make   	0xe038
#define alt_r_break   	0xe0b8
#define ctrl_l_make  	0x1d
#define ctrl_r_make  	0xe01d
#define ctrl_r_break 	0xe09d
#define caps_lock_make 	0x3a

extern Console *console;

static bool ctrlStatus;

static bool shiftStatus;

static bool altStatus;

static bool capsLockStatus;

static bool extScancode;

static char keymap[][2] = {
/* 0x00 */	{0,		0},		
/* 0x01 */	{esc,	esc},		
/* 0x02 */	{'1',	'!'},		
/* 0x03 */	{'2',	'@'},		
/* 0x04 */	{'3',	'#'},		
/* 0x05 */	{'4',	'$'},		
/* 0x06 */	{'5',	'%'},		
/* 0x07 */	{'6',	'^'},		
/* 0x08 */	{'7',	'&'},		
/* 0x09 */	{'8',	'*'},		
/* 0x0A */	{'9',	'('},		
/* 0x0B */	{'0',	')'},		
/* 0x0C */	{'-',	'_'},		
/* 0x0D */	{'=',	'+'},		
/* 0x0E */	{backSpace, backSpace},	
/* 0x0F */	{tab,	tab},		
/* 0x10 */	{'q',	'Q'},		
/* 0x11 */	{'w',	'W'},		
/* 0x12 */	{'e',	'E'},		
/* 0x13 */	{'r',	'R'},		
/* 0x14 */	{'t',	'T'},		
/* 0x15 */	{'y',	'Y'},		
/* 0x16 */	{'u',	'U'},		
/* 0x17 */	{'i',	'I'},		
/* 0x18 */	{'o',	'O'},		
/* 0x19 */	{'p',	'P'},		
/* 0x1A */	{'[',	'{'},		
/* 0x1B */	{']',	'}'},		
/* 0x1C */	{enter,  enter},
/* 0x1D */	{ctrlLeft, ctrlLeft},
/* 0x1E */	{'a',	'A'},		
/* 0x1F */	{'s',	'S'},		
/* 0x20 */	{'d',	'D'},		
/* 0x21 */	{'f',	'F'},		
/* 0x22 */	{'g',	'G'},		
/* 0x23 */	{'h',	'H'},		
/* 0x24 */	{'j',	'J'},		
/* 0x25 */	{'k',	'K'},		
/* 0x26 */	{'l',	'L'},		
/* 0x27 */	{';',	':'},		
/* 0x28 */	{'\'',	'"'},		
/* 0x29 */	{'`',	'~'},		
/* 0x2A */	{shiftLeft, shiftLeft},	
/* 0x2B */	{'\\',	'|'},		
/* 0x2C */	{'z',	'Z'},		
/* 0x2D */	{'x',	'X'},		
/* 0x2E */	{'c',	'C'},		
/* 0x2F */	{'v',	'V'},		
/* 0x30 */	{'b',	'B'},		
/* 0x31 */	{'n',	'N'},		
/* 0x32 */	{'m',	'M'},		
/* 0x33 */	{',',	'<'},		
/* 0x34 */	{'.',	'>'},		
/* 0x35 */	{'/',	'?'},
/* 0x36	*/	{shiftRight, shiftRight},	
/* 0x37 */	{'*',	'*'},    	
/* 0x38 */	{altLeft, altLeft},
/* 0x39 */	{' ',	' '},		
/* 0x3A */	{capsLock, capsLock}
};

int block = 0;

void intKeyboardHandler()
{

	bool ctrl_down_last = ctrlStatus;	  
   	bool shift_down_last = shiftStatus;
   	bool caps_lock_last = capsLockStatus;
	
	outByte(PIC0_OCW2, 0x61);
	u16 data = inByte(PORT_KEYDATA);

	if (block<2) {

		CacheData *cacheData = readBlock(1, block);


		//cacheData->data[0] = 'A';
		//cacheData->data[4] = 'G';
		//cacheData->data[10] = 0;

		//console->print(console, cacheData->data, 15);
		block++;
	}

		
	/*if (data==0xe0) {
		extScancode = true;
	}

	if (extScancode) {
		data = ((0xe000) | data);
      	extScancode = false;	
	}

	bool isBreakCode = false;
	if ((data & 0x0080)!=0)  {
		isBreakCode = true;
	}

	if (isBreakCode) {
		u16 makeCode = (data &= 0xff7f);   // 得到其make_code(按键按下时产生的扫描码)
	  	if (makeCode == ctrl_l_make || makeCode == ctrl_r_make) {
		 	ctrlStatus = false;
	  	} else if (makeCode == shift_l_make || makeCode == shift_r_make) {
		 	shiftStatus = false;
	  	} else if (makeCode == alt_l_make || makeCode == alt_r_make) {
		 	altStatus = false;
	  	}
      	return;

	} else if ((data > 0x00 && data < 0x3b) || (data == alt_r_make) || (data == ctrl_r_make)) {
		  bool shift = false;  // 判断是否与shift组合,用来在一维数组中索引对应的字符
		  if ((data < 0x0e) || (data == 0x29) || (data == 0x1a) || (data == 0x1b) || (data == 0x2b) || 
			  (data == 0x27) || (data == 0x28) || (data == 0x33) ||  (data == 0x34) || (data == 0x35)) { 
	    
			 if (shift_down_last) {
				shift = true;
			 }
		  } else {
			 if (shift_down_last && caps_lock_last) {
				shift = false;
			 } else if (shift_down_last || caps_lock_last) {
				shift = true;
			 } else {
				shift = false;
			 }
		  }

      u8 index = (data &= 0x00ff);
      char currentData = keymap[index][shift];
   
      if (currentData) {
		 console->putChar(console, currentData, 11);
		 return;
      }

      if (data == ctrl_l_make || data == ctrl_r_make) {
	 	ctrlStatus = true;
      } else if (data == shift_l_make || data == shift_r_make) {
	 	shiftStatus = true;
      } else if (data == alt_l_make || data == alt_r_make) {
	 	altStatus = true;
      } else if (data == caps_lock_make) {
	 	capsLockStatus = !capsLockStatus;
      }
   }*/
}
