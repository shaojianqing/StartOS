#include "../type/type.h"
#include "../const/const.h"
#include "../error/error.h"
#include "../system/system.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "../memory/memory.h"
#include "cache.h"
#include "../harddisk/harddisk.h"
#include "../console/console.h"

#include "filesys.h"
#include "namei.h"

SuperBlock superBlock;

Inode nodeTable[NUM_INDEX_NODE];

Inode *rootNode;

u32 rootBlock = 0;

extern Console *console;

extern Partition partitionTable[];

Inode* getEmptyNode();

void readInode(Inode* inode);

Inode *getInode(int dev, int num);

void printDataFormat(Inode* fileNode);

void initFileSystem() {

	int i = 0;
	u32 block = 0;
	
	Partition rootPartition = partitionTable[ROOT_PARTITION];
	rootBlock = (rootPartition.startSector>>1);
	block = rootBlock + 1;
	CacheData *cacheData = readBlock(ROOT_DEVICE, block);
	SuperBlockDisk *superBlockDisk = (SuperBlockDisk *)(cacheData->data);

	superBlock.ninodes = superBlockDisk->ninodes;
	superBlock.nzones = superBlockDisk->nzones;
	superBlock.imapBlocks = superBlockDisk->imapBlocks;
	superBlock.zmapBlocks = superBlockDisk->zmapBlocks;
	superBlock.firstDatazone = superBlockDisk->firstDatazone;
	superBlock.logZoneSize = superBlockDisk->logZoneSize;
	superBlock.maxSize = superBlockDisk->maxSize;
	superBlock.magic = superBlockDisk->magic;

	releaseBlock(cacheData);
	
	for (i=0;i<I_MAP_SLOTS;++i) {
		superBlock.nodeMap[i] = NULL;
	}

	for (i=0;i<Z_MAP_SLOTS;++i) {
		superBlock.zoneMap[i] = NULL;
	}
	
	block+=1;
	for (i=0;i<superBlock.imapBlocks;++i) {
		superBlock.nodeMap[i] = readBlock(ROOT_DEVICE, block+i);
	}

	block+=superBlock.imapBlocks;
	for (i=0;i<superBlock.zmapBlocks;++i) {
		superBlock.zoneMap[i] = readBlock(ROOT_DEVICE, block+i);
	}	

	(superBlock.nodeMap[0]->data[0]) |= 1;
	(superBlock.zoneMap[0]->data[0]) |= 1;

	rootNode = getInode(ROOT_DEVICE, ROOT_INDEX_NODE);
	rootNode->count = 1;

	Inode *fileNode = getFileNode("/etc/info.txt", rootNode);

	if (fileNode!=NULL) {
		printDataFormat(fileNode);
	} else {
		console->printString(console, "Can not find the file!+!", 13);	
	}
}

Inode* getEmptyNode() {
	
	u32 i = 0;
	Inode *inode = nodeTable;
	for (i=0;i<NUM_INDEX_NODE;++i) {
		if ((*(inode+i)).count==0) {
			inode = inode+i;
			break;	
		}		
	}
	memset(inode, 0, sizeof(Inode));
	return inode;
}

void readInode(Inode* inode) {
	if (inode!=NULL) {
		u32 block = rootBlock + 2 + superBlock.imapBlocks + superBlock.zmapBlocks + 
					(inode->num - 1)/INODE_NUM_PER_BLOCK;
		CacheData *cacheData = readBlock(inode->dev, block);
		InodeDisk *inodeDisk = (InodeDisk *)(cacheData->data);
		inodeDisk = inodeDisk + (inode->num-1)%INODE_NUM_PER_BLOCK;
		*((InodeDisk *)inode) = *inodeDisk;
		releaseBlock(cacheData);
	}
}

Inode *getInode(int dev, int num) {
	Inode *inode = getEmptyNode();
	inode->dev = dev;
	inode->num = num;

	readInode(inode);
	return inode;	
}

void printDataFormat(Inode* fileNode) {
	if (fileNode!=NULL) {
		CacheData *cacheData = readBlock(ROOT_DEVICE, rootBlock + fileNode->zone[0]);
		if (cacheData!=NULL) {
			console->printString(console, cacheData->data, 11);	
		}	
	}	
}

int sys_ustat() {
	return -ENOSYS;
}

int sys_utime() {
	return -ENOSYS;
}

int sys_access() {
	return -ENOSYS;
}

int sys_chdir(const char *filename) {
	return -ENOSYS;
}

int sys_chroot(const char *filename) {
	return -ENOSYS;
}

int sys_chmod(const char *filename, int mode) {
	return -ENOSYS;
}

int sys_mkdir() {
	return -ENOSYS;
}

int sys_umount() {
	return -ENOSYS;
}

int sys_mount() {
	return -ENOSYS;
}

int sys_chown(const char *filename, int uid, int gid) {
	return -ENOSYS;
}

int sys_open(char *filename, int flags, int mode) {
	char *buffer = (char *)0xb8000;

	*buffer = (char)flags;
	*(buffer+1) = 0x07;

	*(buffer+2) = (char)mode;
	*(buffer+3) = 0x09;

	*(buffer+4) = 's';
	*(buffer+5) = 0x0b;

	*(buffer+6) = 't';
	*(buffer+7) = 0x0d;

	*(buffer+8) = 'e';
	*(buffer+9) = 0x0f;

	*(buffer+10) = 'm';
	*(buffer+11) = 0x03;

	return '&';
}

int sys_create(const char *pathname, int mode) {
	return -ENOSYS;
}

int sys_close(int fd) {
	char *buffer = (char *)0xb8000;

	*buffer = (char)fd;
	*(buffer+1) = 0x07;

	return 'Q';
}

int sys_ioctl(unsigned int fd, unsigned int cmd, unsigned long arg) {
	return -ENOSYS;
}

int sys_dup2(unsigned int oldfd, unsigned int newfd) {
	return -ENOSYS;
}

int sys_dup(unsigned int fildes) {
	return -ENOSYS;
}

int sys_fcntl(unsigned int fd, unsigned int cmd, unsigned long arg) {
	return -ENOSYS;
}
