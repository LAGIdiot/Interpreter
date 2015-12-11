#include "memory_manager.h"

static MemoryManagerPtr MM = NULL;

//Function prototypes - private
void MM_Add(void * ptr);
void MM_Remove(void * ptr, int invalid);

//////////////////////////////////////////////////
// void MM_Init()
////////////////////
// Initialize memory manager - set its top member to NULL
//////////////////////////////////////////////////

void MM_Init()
{
#if DEBUG
	printf("Initializing Memory Manager\n");
#endif

	MM = malloc(sizeof(struct MemoryManagerStruct));
	if(MM == NULL)
		mistake(ERR_INTERN, "Problem with initializing memory manager\n");

	MM->last = NULL;
	MM->numberOfAllocatedBlocks = 0;
}

void MM_Terminate()
{
#if DEBUG
	printf("Terminating Memory Manager\n");
#endif
	if(MM == NULL)	//Only if problem with opening file
		return;
	if(MM->numberOfAllocatedBlocks != 0)
		MM_FreeAll();

	free(MM);

	MM = NULL;
}

//////////////////////////////////////////////////
// void * MM_Malloc(size_t size)
// return - pointer to memory block
// size - size in bites of memory block
////////////////////
// Allocate memory block of size size, return its pointer & add him to MM
//////////////////////////////////////////////////
void * MM_Malloc(size_t size)
{
	void * ptr = malloc(size);

	if(ptr == NULL)
		mistake(ERR_INTERN, "Not enough memory\n");

#if DEBUG2
	printf("Allocating memory at: %d with size: %d\n", ptr, size);
#endif

	MM_Add(ptr);

	return ptr;
}

//////////////////////////////////////////////////
// void * MM_Realloc(void * ptrOld, size_t size)
// return - pointer to memory block
// * ptrOld - pointer to old memory block
// size - size in bites of memory block
////////////////////
// Reallocate memory block from ptrOld to new size size, return its pointer & re-add him to MM
//////////////////////////////////////////////////
void * MM_Realloc(void * ptrOld, size_t size)
{
	void * ptr = realloc(ptrOld, size);

	if(ptr == NULL)
		mistake(ERR_INTERN, "Memory reallocation problem");

#if DEBUG2
	printf("Reallocating memory from: %d to: %d with size: %d\n", ptrOld, ptr, size);
#endif

	/*re-map member if needed*/
	//FIXME: Spatne rozpoznavani mrtvych bloku

	if(ptr != ptrOld)
	{
		//MM_Remove(ptrOld, 0);
		MM_Add(ptr);
	}

	return ptr;
}

//////////////////////////////////////////////////
// void MM_Free(void * ptr)
// * ptr - pointer to memory block
////////////////////
// Free memory block from ptr & remove him from MM
//////////////////////////////////////////////////
void MM_Free(void * ptr)
{
#if DEBUG2
	printf("Freeing memory from: %d\n", ptr);
#endif

	MM_Remove(ptr, 1);
}

//////////////////////////////////////////////////
// void MM_FreeAll()
////////////////////
// Free all memory blocks stored in MM
////////////////////
// note: memory must be deleted from last added block - otherwise there will be lost (e.g.: data in Token)
//////////////////////////////////////////////////
void MM_FreeAll()
{
#if DEBUG
	printf("Freeing ALL memory\n");
#endif

	MemoryBlockPtr temp = NULL;
	MemoryBlockPtr tempPrev = NULL;

	while(MM->numberOfAllocatedBlocks != 0)
	{
		temp = MM->last;

		if(temp->dataPtr != NULL)
			free(temp->dataPtr);

		MM->last = temp->prevPtr;

		free(temp);

		MM->numberOfAllocatedBlocks--;
	}

	MM->last = NULL;

#if DEBUG
	printf("Done\n");
#endif
}

//////////////////////////////////////////////////
// void MM_Add(void * ptr)
// * ptr - pointer to memory block
////////////////////
// Add memory block to MM
//////////////////////////////////////////////////
void MM_Add(void * ptr)
{
#if DEBUG2
	printf("Creating garbage block for pointer: %d\n", ptr);
#endif
	MemoryBlockPtr newBlock = malloc(sizeof(struct MemoryBlockStruct));
	if(newBlock == NULL)
		mistake(ERR_INTERN, "Not enough memory\n");

	newBlock->dataPtr = ptr; //ptr is data for MM container
	newBlock->prevPtr = NULL;

	if(MM->last != NULL)
		newBlock->prevPtr = MM->last; //in newBlock assign prevPtr to last block

	MM->last = newBlock; //newBlock make available as last block
	MM->numberOfAllocatedBlocks++;
}

//////////////////////////////////////////////////
// void MM_Remove(void * ptr, int invalid)
// * ptr - pointer to memory block
// invalid - information about validity - for data removing (1 - for remove)
////////////////////
// Remove memory block from MM
//////////////////////////////////////////////////
void MM_Remove(void * ptr, int valid)
{
#if DEBUG2
	printf("Removing garbage block for pointer: %d - block is valid: %s\n", ptr, valid == 1 ? "TRUE" : "FALSE");
#endif
	if(MM->numberOfAllocatedBlocks != 0) //Check if there is any memory to free
	{
		MemoryBlockPtr temp = MM->last;
		MemoryBlockPtr temp2 = NULL;	//vzdy o jeden memoryblock starsi

		while(temp->dataPtr != ptr)
		{
			temp2 = temp;
			temp = temp->prevPtr;
			if(temp == NULL)
				mistake(ERR_INTERN, "Memory block not found\n");
		}

		//block se nasel
		if(valid)
			free(temp->dataPtr);

		if(temp2 == NULL)	//pripad ze by se jednalo o nejvyssi
			MM->last = temp->prevPtr;
		else
			temp2->prevPtr = temp->prevPtr;

		free(temp);
		MM->numberOfAllocatedBlocks--;
	}
	else
		mistake(ERR_INTERN, "MM was not Initialized\n");
}
