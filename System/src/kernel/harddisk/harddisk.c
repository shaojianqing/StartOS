#include "../const/const.h"
#include "../type/type.h"
#include "../system/system.h"
#include "harddisk.h"

#define readPort(port, buf, nr) asm ("cld;rep;insw"::"d" (port),"D" (buf),"c" (nr))

#define writePort(port, buf, nr) asm("cld;rep;outsw"::"d" (port),"S" (buf),"c" (nr))

HarddiskInfo harddiskInfo = {0, 0, 0, 0, 0, 0};

Harddisk harddisk[5*MAX_HD] = {{0,0}};

void initHarddiskSetting() {
	outByte(inByte(0x21)&0xfb, 0x21);
	outByte(inByte(0xA1)&0xbf, 0xA1);
}

void intHarddiskHandler() {
	inByte(REG_STATUS);
	outByte(0x20, 0xA0);
	outByte(0x20, 0x20);
	return;
}

int sys_setup() {
	Object *BIOS = (Object *)BIOS_ADDRESS;
	static bool callable = true;
	if (callable) {
		harddiskInfo.cyl = *(u16 *) BIOS;
		harddiskInfo.head = *(u8 *) (2+BIOS);
		harddiskInfo.wpcom = *(u16 *) (5+BIOS);
		harddiskInfo.ctl = *(u8 *) (8+BIOS);
		harddiskInfo.lzone = *(u16 *) (12+BIOS);
		harddiskInfo.sect = *(u8 *) (14+BIOS);

		long sectorCount = harddiskInfo.head*harddiskInfo.sect*harddiskInfo.cyl;

		harddisk[0].startSector = 0;
		harddisk[0].sectorCount = sectorCount;
		callable = false;
	} else {
		return -1;
	}
}

static int isHdReady()
{
	int retries = 10000;

	while (retries>0) {
		u8 status =(inByte(REG_STATUS)&0xc0);
		if (status==0x40) {
			return retries;
		}
		retries--;
	}
	return retries;
}

static void sendHdCommand(u32 drive, u32 nsect, u32 sect,
		u32 head,u32 cyl,u32 cmd,
		void (*intr_addr)(void))
{
	/*int port;

	if (drive>1 || head>15)
		panic("Trying to write bad sector");
	if (!controller_ready())
		panic("HD controller not ready");
	do_hd = intr_addr;
	outb_p(hd_info[drive].ctl,HD_CMD);
	port=HD_DATA;
	outb_p(hd_info[drive].wpcom>>2,++port);
	outb_p(nsect,++port);
	outb_p(sect,++port);
	outb_p(cyl,++port);
	outb_p(cyl>>8,++port);
	outb_p(0xA0|(drive<<4)|head,++port);
	outb(cmd,++port);*/
}