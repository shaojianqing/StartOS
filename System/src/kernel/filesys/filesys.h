
#define BLOCK_DATA_SIZE					1024

#define NUM_INDEX_NODE					256

#define NAME_LENGTH 					14

#define I_MAP_SLOTS 					8

#define Z_MAP_SLOTS 					8

#define INODE_NUM_PER_BLOCK 			32		//INODES_PER_BLOCK = 1024/32

#define ROOT_PARTITION					1

#define ROOT_DEVICE						1

#define ROOT_INDEX_NODE					1

typedef struct SuperBlockDisk {

	u16 ninodes;

	u16 nzones;

	u16 imapBlocks;

	u16 zmapBlocks;

	u16 firstDatazone;

	u16 logZoneSize;

	u64 maxSize;

	u16 magic;

} SuperBlockDisk;

typedef struct SuperBlock {

	u16 ninodes;

	u16 nzones;

	u16 imapBlocks;

	u16 zmapBlocks;

	u16 firstDatazone;

	u16 logZoneSize;

	u64 maxSize;

	u16 magic;

	CacheData *nodeMap[I_MAP_SLOTS];
	
	CacheData *zoneMap[Z_MAP_SLOTS];	
	
} SuperBlock;

typedef struct IndexNodeDisk {

	u16 mode;

	u16 uid;

	u64 size;

	u64 mtime;

	u8 gid;

	u8 nlinks;

	u16 zone[9];

} InodeDisk;

typedef struct IndexNode {

	u16 mode;

	u16 uid;

	u64 size;

	u64 mtime;

	u8 gid;

	u8 nlinks;

	u16 zone[9];

	u64 atime;

	u64 ctime;

	u16 dev;

	u16 num;

	u16 count;

	u8 lock;

	u8 dirt;

	u8 pipe;

	u8 mount;

	u8 seek;

	u8 update;

} Inode;

typedef struct DirectoryEntry {

	u16 inode;

	byte name[NAME_LENGTH];

} DirEntry;

typedef struct File {

	u16 mode;

	u16 flags;

	u16 count;

	Inode *inode;

	u32 position;

} File;

void initFileSystem();

Inode *getInode(int dev, int num);
