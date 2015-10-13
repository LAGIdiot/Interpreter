#ifndef MM_Header
#define MM_Header

//Structures
typedef struct MemoryBlockStruct{
	void * dataPtr;
	void * nextPtr;
	void * prevPtr;
}MemoryBlock, *MemoryBlockPtr;

//Function prototypes
void MM_Init();
void * MM_Malloc(size_t size);
void * MM_Realloc(void* oldPtr, size_t size);
void MM_Free(void* ptr);
void MM_FreeAll();

#endif //MM_Header
