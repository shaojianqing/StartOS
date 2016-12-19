#include "../type/type.h"
#include "../console/console.h"
#include "memory.h"

extern Console *console;

static byte bitmap[MEMORY_PAGE_NUM];

void initMemorySetting() {
	int i=0;
	for (i=0;i<MEMORY_PAGE_NUM;++i) {
		bitmap[i] = 0;	
	}
}

u32 allocatePage() {
	int i = 0, h = 0, index = 0, pos = 1;
	while ((pos & bitmap[i])>0 && i<MEMORY_PAGE_NUM) {
		pos = pos<<1;	
		index++;
		h++;
		if (h>=8) {
			h = 0;
			pos = 1;
			i++;		
		}
	}
	if (i<MEMORY_PAGE_NUM) {
		bitmap[i] = bitmap[i] | pos;
		return START_MEMORY_ADDRESS + MEMORY_PAGE_SIZE*index;
 	} else {
		return 0;
	}	
}

void releasePage(u32 addr) {
	addr = (addr & 0xFFFFF000);
	addr = addr - START_MEMORY_ADDRESS;
	u32 index = addr/MEMORY_PAGE_SIZE;
	u32 position = index/8;
	u32 offset = index%8;
	
	byte data = 1;
	data = data<<offset;
	data = ~data;

	bitmap[position] = (bitmap[position] & data);	
}

