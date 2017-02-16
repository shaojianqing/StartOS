#include "../type/type.h"
#include "../const/const.h"
#include "string.h"

char* strcpy(char* dest, const char* source) {
   if (dest!=NULL && source!=NULL) {
   		char* result = dest;		       
   		while((*dest++ = *source++));
   		return result;
	} else {
		return dest;	
	}
}

u32 strlen(const char* str) {
	if (str!=NULL) {
   		const char* p = str;
   		while(*p++);
   		return (p - str - 1);
	} else {
		return 0;	
	}
}

u8 strcmp(const char* a, const char* b) {
	if (a!=NULL && b!=NULL) {
		while (*a != 0 && *a == *b) {
			a++;
			b++;
		}
		return *a < *b ? -1 : *a > *b;
	} else {
		return 0;	
	}
}
