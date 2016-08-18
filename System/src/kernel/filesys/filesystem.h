#define BLOCK_SIZE				1024

typedef struct MInode {

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

typedef struct File {

	u16 mode;

	u16 flags;

	u16 count;

	MInode *inode;

	u32 position;

} File;