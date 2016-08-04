#include "const/const.h"

void initSystem(void)
{
	char *buffer = (char *)0xb8000;

	*buffer = 'K';
	*(buffer+1) = 0x09;


	while(TRUE)	{

	}
}