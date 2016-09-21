#include "../const/const.h"
#include "../type/type.h"
#include "../system/system.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "../filesys/cache.h"
#include "../filesys/block.h"
#include "harddisk.h"

#define readPort(port, buf, nr) asm ("cld;rep;insw"::"d" (port),"D" (buf),"c" (nr))

#define writePort(port, buf, nr) asm("cld;rep;outsw"::"d" (port),"S" (buf),"c" (nr))

static int reset = 1;

static int recalibrate = 1;

static void doHarddiskRequest();

static HarddiskHandler hdHandler;

extern BlockDevice blockDeviceList[BLOCK_DEVICE_SIZE];

HarddiskInfo harddiskInfo = {0, 0, 0, 0, 0, 0};

Harddisk harddisk[MAX_HD] = {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}};

void initHarddiskSetting() {

	blockDeviceList[DEVICE_HARD_DISK].requestHandler = doHarddiskRequest;
		
	outByte(inByte(0x21)&0xFB, 0x21);
	outByte(inByte(0xA1)&0xBF, 0xA1);

	sys_setup();
}

void intHarddiskHandler() {
	inByte(REG_STATUS);
	outByte(0x20, 0xA0);
	outByte(0x20, 0x20);
	if (hdHandler!=NULL) {
		hdHandler();
	}	
}

int sys_setup() {
	Object *BIOS = (Object *)BIOS_ADDRESS;
	static bool callable = true;
	if (callable) {
		harddiskInfo.cylinder = *(u16 *) BIOS;
		harddiskInfo.head = *(u8 *) (2+BIOS);
		harddiskInfo.wpcom = *(u16 *) (5+BIOS);
		harddiskInfo.ctl = *(u8 *) (8+BIOS);
		harddiskInfo.lzone = *(u16 *) (12+BIOS);
		harddiskInfo.sect = *(u8 *) (14+BIOS);


		printString(10, 8, "cyl:", 11);
		printString(10, 10, "head:", 11);
		printString(10, 12, "wpcom:", 11);
		printString(10, 14, "ctl:", 11);
		printString(10, 16, "lzone:", 11);
		printString(10, 18, "sect:", 11);
	
		printInteger(20, 8, harddiskInfo.cylinder, 5);
		printInteger(20, 10, harddiskInfo.head, 5);
		printInteger(20, 12, harddiskInfo.wpcom, 5);
		printInteger(20, 14, harddiskInfo.ctl, 5);
		printInteger(20, 16, harddiskInfo.lzone, 5);
		printInteger(20, 18, harddiskInfo.sect, 5);


		long sectorCount = harddiskInfo.head*harddiskInfo.sect*harddiskInfo.cylinder;

		harddisk[0].startSector = 0;
		harddisk[0].sectorCount = sectorCount;
		callable = false;
		return 0;
	} else {
		return -1;
	}
}

static bool isControllerReady()
{
	int retries = 10000;

	while (retries>0) {
		u8 status =(inByte(REG_STATUS)&0xc0);
		if (status==0x40) {
			return retries;
		}
		retries--;
	}
	return (retries>0);
}

static void sendCommand(u32 drive, u32 sectCount, u32 startSect, u32 head, u32 cylinder, u32 command, HarddiskHandler handler) {

	if (handler!=NULL) {
		hdHandler = handler;
	}

	if (isControllerReady) {
		outByte(REG_DEV_CTRL, harddiskInfo.ctl);
		outByte(REG_FEATURES, harddiskInfo.wpcom);
		outByte(REG_NSECTOR, sectCount);
		outByte(REG_LBA_LOW, startSect);
		outByte(REG_LBA_MID, cylinder);
		outByte(REG_LBA_HIGH, cylinder>>8);
		outByte(REG_DEVICE, 0xA0|(drive<<4)|head);
		outByte(REG_COMMAND, command);
	}
}

static bool isDriveBusy(void) {
	u32 i;
	for (i = 0; i < 10000; i++) {
		if (STATUS_DRDY == (inByte(REG_STATUS) & (STATUS_BSY|STATUS_DRDY)))
			break;
	}
	i = inByte(REG_STATUS);
	i &= STATUS_BSY | STATUS_DRDY | STATUS_DSC;
	if (i == (STATUS_DRDY | STATUS_DSC)) {
		return true;
	}
	printk("HD controller times out\n\r");
	return false;
}

static bool winResult() {
	int i = inByte(REG_STATUS);
	if ((i & (STATUS_BSY|STATUS_DRDY|STATUS_DFSE|STATUS_DSC|STATUS_ERR))==(STATUS_DRDY|STATUS_DSC)) {
		return false;
	}
	if (i&1) { 
		i=inByte(REG_ERROR);
	}
	return true;
}

static void resetController() {
	int	i;

	outByte(REG_DEV_CTRL, 4);
	for(i = 0; i < 100; i++) nop();
	outByte(REG_DEV_CTRL, (harddiskInfo.ctl & 0x0f));
	if (isDriveBusy()) {
		printk("HD-controller still busy\n\r");
	}
	if ((i = inByte(REG_ERROR)) != 1) {
		printk("HD-controller reset failed: %02x\n\r", i);
	}
}

static void recalibrateHandler() {
	
}

static void resetHarddisk() {
	resetController();
	sendCommand(0, harddiskInfo.sect, harddiskInfo.sect, harddiskInfo.head-1,
		harddiskInfo.cylinder, WIN_SPECIFY, recalibrateHandler);
}

static void readHarddisk() {
	printString(10, 21, "Harddisk Interrupt Occurs", 11);
}

static void writeHarddisk() {
	
}

void doHarddiskRequest() {
	Request *request = &(blockDeviceList[DEVICE_HARD_DISK].currentRequest);
	if (request!=NULL) {
		u32 sector, head, cylinder, sectorCount;
		u32 device = request->device;
		u32 block = request->startSector;

		printString(12, 24, "request->command", 11);

		if (device<MAX_HD && block+2<harddisk[device].sectorCount) {

			printInteger(12, 23, request->command, 11);

			block += harddisk[device].startSector;
			device = device/MAX_HD;
			asm ("divl %4":"=a" (block),"=d" (sector):"0" (block),"1" (0), "r" (harddiskInfo.sect));
			asm	("divl %4":"=a" (cylinder),"=d" (head):"0" (block),"1" (0), "r" (harddiskInfo.head));
		
			sector++;
			sectorCount = request->sectorCount;

			printString(12, 23, "sendCommand Read to Harddisk", 11);
			
				sendCommand(0, sectorCount, sector, head, cylinder, WIN_READ, readHarddisk);

			if (reset) {
				reset = 0;
				recalibrate = 1;
				resetHarddisk();	
			}

			if (recalibrate) {
				recalibrate = 0;
				sendCommand(0, harddiskInfo.sect, 0, 0, 0, WIN_RESTORE, recalibrateHandler);
				return;
			}	

			

			if (request->command==READ) {
				
				
			} else if (request->command==WRITE) {
							
			} else {
				
			}			
		}
	}
}
