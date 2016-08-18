#include "../type/type.h"
#include "../const/const.h"
#include "../error/error.h"
#include "../system/system.h"
#include "../system/descriptor.h"
#include "../process/process.h"

#include "cache.h"
#include "block.h"

/*
 * The request-struct contains all necessary data
 * to load a nr of sectors into memory
 */
Request requests[REQUEST_SIZE];

/*
 * used to wait on when there are no free requests
 */
Process* waitRequestProcess = NULL;

BlockDevice blockDevice[BLOCK_DEVICE_SIZE] = {
	{ NULL, NULL },		/* no_dev */
	{ NULL, NULL },		/* dev mem */
	{ NULL, NULL },		/* dev fd */
	{ NULL, NULL },		/* dev hd */
	{ NULL, NULL },		/* dev ttyx */
	{ NULL, NULL },		/* dev tty */
	{ NULL, NULL }		/* dev lp */
};

void initBlockDevice() {
	int i;

	for (i=0;i<REQUEST_SIZE;i++) {
		requests[i].dev = -1;
		requests[i].next = NULL;
	}
}