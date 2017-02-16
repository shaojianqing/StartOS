#include "../type/type.h"
#include "../const/const.h"
#include "../error/error.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "../console/console.h"

#include "cache.h"
#include "filesys.h"
#include "namei.h"

extern u32 rootBlock;

extern Inode *rootNode;

extern Console *console;

static u32 getPathLength(char *filepath);

static bool match(char *name, int length, DirEntry *entry);

Inode* getFileNode(char *filepath, Inode *parent) {
	if (filepath!=NULL) {
		if (filepath[0]=='/') {
			filepath++;
			parent = rootNode;	
		}

		if (parent==NULL) {
			return NULL;		
		}
	
		Inode *childNode = NULL;
		u32 length = getPathLength(filepath);

		if (length>0) {		
			u32 block = rootBlock + parent->zone[0];
			CacheData *cacheData = readBlock(ROOT_DEVICE, block);
			DirEntry *entry = (DirEntry *)(cacheData->data);
			while (entry->inode!=0) {
				if (match(filepath, length, entry)) {
					childNode = getInode(ROOT_DEVICE, entry->inode);
					break;		
				} else {
					entry++;				
				}
			}
			
			char c = *(filepath+length);
			if (c!='\0') {
				filepath += length+1;		
			} else {
				filepath += length;			
			}
			
			if (*filepath=='\0') {
				return childNode;		
			} else {
				return getFileNode(filepath, childNode);	
			}
		}
	}
	return NULL;
}

static u32 getPathLength(char *filepath) {
	char *pathname = filepath;
	char c = *pathname;
	u32 length = 0;

	while(c!='/' && c!='\0') {
		pathname++;
		length++;

		c = *pathname;		
	}
	return length;
}

static bool match(char *name, int length, DirEntry *entry) {
	int i=0;
	while (i<length) {
		char c = entry->name[i];
		char e = name[i];
		if (c == e) {
			i++;		
		} else {
			return false;		
		}
	}

	
	console->putChar(console, '\n', 11);

	if (entry->name[length]=='\0') {
		return true;	
	} else {
		return false;	
	}
}

int sys_mknod(const char * filename, int mode, int dev) {
	return -ENOSYS;
}

int sys_rmdir(const char * name) {
	return -ENOSYS;
}

int sys_unlink(const char *name) {
	return -ENOSYS;
}

int sys_link(const char *oldname, const char *newname) {
	return -ENOSYS;
}
