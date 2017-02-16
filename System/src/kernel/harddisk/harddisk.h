
#define 	BIOS_ADDRESS				(4*0X41)					

#define 	PARTITION_TABLE				(0x7c00+446)

#define 	DEFAULT_PARTITION_COUNT		0x04
/* 
 * The constants of harddisk identity.The function can access the IDE harddisk
 * by using the constants listed below.
 */
#define 	ATA_IDENTIFY	0xEC
#define 	ATA_READ		0x20
#define 	ATA_WRITE		0x30
#define		SECTOR_SIZE		512
#define		HD_TIMEOUT		10000

/* 
 * The constants of harddisk port registers.The function can control and access
 * the harddisk by communicating with the port constants listed below.
 */
#define 	REG_DATA		0x1F0		
#define 	REG_FEATURES	0x1F1		
#define	 	REG_ERROR		REG_FEATURES
#define 	REG_NSECTOR		0x1F2		
#define 	REG_LBA_LOW		0x1F3		
#define 	REG_LBA_MID		0x1F4		
#define 	REG_LBA_HIGH	0x1F5
#define 	REG_DEVICE		0x1F6
#define 	REG_STATUS		0x1F7
#define 	REG_COMMAND		REG_STATUS
#define 	REG_DEV_CTRL	0x3F6
#define 	REG_ALT_STATUS	REG_DEV_CTRL
#define 	REG_DRV_ADDR	0x3F7

/* 
 * The constants of harddisk port status.The function can get the running infomation
 * of the harddisk by comparing with the status constants listed below.
 */
#define		STATUS_BSY		0x80
#define		STATUS_DRDY		0x40
#define		STATUS_DFSE		0x20
#define		STATUS_DSC		0x10
#define		STATUS_DRQ		0x08
#define		STATUS_CORR		0x04
#define		STATUS_IDX		0x02
#define		STATUS_ERR		0x01

#define 	BIT_DEV_MBS		0xa0	    // 第7位和第5位固定为1
#define 	BIT_DEV_LBA		0x40
#define 	BIT_DEV_DEV		0x10
#define 	BIT_STAT_BSY	0x80	    // 硬盘忙
#define 	BIT_STAT_DRDY	0x40	    // 驱动器准备好	 
#define 	BIT_STAT_DRQ	0x8	      	// 数据传输准备好了

typedef struct Partition {

	u32 startSector;			/* starting sector counting from 0 */

	u32 totalSectCount;			/* nr of sectors in partition */

} Partition;

typedef struct HarddiskInfo {

	int head;

	int sect;

	int cyl;

	int wpcom;

	int lzone;

	int ctl;

} HarddiskInfo;

typedef void (*HarddiskHandler)();

void initHarddiskSetting();

void readDataBlock(CacheData *cacheData);

void writeDataBlock(CacheData *cacheData);

