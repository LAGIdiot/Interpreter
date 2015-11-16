#ifndef MM_Header
#define MM_Header

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

//Structures
typedef struct MemoryBlockStruct{
	void * prevPtr;
	void * dataPtr;
}*MemoryBlockPtr;

//Function prototypes
void MM_Init();
void * MM_Malloc(size_t size);
void * MM_Realloc(void* oldPtr, size_t size);
void MM_Free(void* ptr);
void MM_FreeAll();

#endif //MM_Header
