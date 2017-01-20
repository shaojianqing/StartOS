
#define BLOCK_DATA_SIZE					1024

#define NAME_LEN 						14

typedef struct CacheBlock {
	
	byte data[BLOCK_DATA_SIZE];	

} CacheBlock;

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

	CacheBlock *nodeMap[9];
	
	CacheBlock *zoneMap[9];	
	
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

} MInode;

typedef struct DirectoryEntry {

	u16 inode;

	byte name[NAME_LEN];

} DirEntry;

typedef struct File {

	u16 mode;

	u16 flags;

	u16 count;

	MInode *inode;

	u32 position;

} File;

void initFileSystem();
