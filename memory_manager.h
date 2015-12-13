///////////////////////////////////////////////////////////////////////////////
/* ---------- IMPLEMENTACE INTERPRETU IMPERATIVNÍHO JAZYKA IFJ15 ----------- */
///////////////////////////////////////////////////////////////////////////////

AUTOŘI:

xbedna57 	ADAM BEDNÁRIK 	()
xmacha63 	ERIK MACHÁČEK 	()
xmalar02 	MARTIN MALÁRIK 	()
xklaci00 	MICHAL KLACIK 	()
xlengu00 	MANH LE NGUYEN 	()

///////////////////////////////////////////////////////////////////////////////

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

typedef struct MemoryManagerStruct{
	void * last;
	int numberOfAllocatedBlocks;
}*MemoryManagerPtr;

//Function prototypes
void MM_Init();
void MM_Terminate();
void * MM_Malloc(size_t size);
void * MM_Realloc(void* oldPtr, size_t size);
void MM_Free(void* ptr);
void MM_FreeAll();

#endif //MM_Header
