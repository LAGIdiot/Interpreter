#include "memory_manager.h"

MemoryBlockPtr MM_Top;

//Function prototypes - private
void MM_Add(void * ptr);
void MM_Remove(void * ptr, int invalid);

#if DEBUG
//DEBUG variables
static int memoryBlocksCount;
#endif

//////////////////////////////////////////////////
// void MM_Init()
////////////////////
// Initialize memory manager - set its top member to NULL
//////////////////////////////////////////////////

void MM_Init()
{
#if DEBUG
	printf("Initializing Memory Manager\n");
	memoryBlocksCount = 0;
#endif

	MM_Top = NULL;
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
	{
#if DEBUG
		mistake(ERR_INTERN, "Not enough memory\n");
#else
		mistake(ERR_INTERN);
#endif
	}

#if DEBUG
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
	{
#if DEBUG
		mistake(ERR_INTERN, "Memory reallocation problem");
#else
		mistake(ERR_INTERN);
#endif
	}

#if DEBUG
	printf("Reallocating memory from: %d to: %d with size: %d\n", ptrOld, ptr, size);
#endif

	/*re-map member if needed*/
	if(ptr != ptrOld)
	{
		MM_Remove(ptrOld, 1);
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
#if DEBUG
	printf("Freeing memory from: %d\n", ptr);
#endif

	MM_Remove(ptr, 0);
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

	if(MM_Top != NULL) //Check if there is any memory to free
	{
		MemoryBlockPtr temp = MM_Top;
		MemoryBlockPtr tempPrev;

		/*Store penultimate member, delete data from last one, delete last one, penultimate == last one*/
		while(temp != NULL)
		{
			tempPrev = temp->prevPtr;

			free(temp->dataPtr);
			free(temp);

			temp = tempPrev;
		}

		//reseting MM_Top
		MM_Top = NULL;
	}
#if DEBUG
	else
	{
		printf("No need\n");
	}
	printf("Done\n");

	memoryBlocksCount = 0;
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
#if DEBUG
	printf("Creating garbage block for pointer: %d\n", ptr);
#endif
	MemoryBlockPtr newBlock = malloc(sizeof(struct MemoryBlockStruct));
	if(newBlock == NULL)
	{
#if DEBUG
		mistake(ERR_INTERN, "Not enough memory\n");
#else
		mistake(ERR_INTERN);
#endif
	}

	newBlock->dataPtr = ptr; //ptr is data for MM container
	newBlock->prevPtr = NULL;

	if(MM_Top != NULL)
	{
		newBlock->prevPtr = MM_Top; //in newBlock assign prevPtr to last block
	}
	MM_Top = newBlock; //newBlock make available as last block

#if DEBUG
	memoryBlocksCount++;
#endif
}

//////////////////////////////////////////////////
// void MM_Remove(void * ptr, int invalid)
// * ptr - pointer to memory block
// invalid - information about validity - for data removing (1 - for remove)
////////////////////
// Remove memory block from MM
//////////////////////////////////////////////////
void MM_Remove(void * ptr, int invalid)
{
#if DEBUG
	printf("Removing garbage block with pointer: %d - block is invalid: %s\n", ptr, invalid == 1 ? "TRUE" : "ELSE");
#endif
	if(MM_Top != NULL) //Check if there is any memory to free
	{
		MemoryBlockPtr temp = MM_Top->prevPtr; //get penultimate block
		MemoryBlockPtr afterData = NULL;	//block that is on top of wanted block

		/*There is big chance that we will be removing last added block first*/
		if(MM_Top->dataPtr == ptr)
		{
			if(invalid == 1)
				free(MM_Top->dataPtr);

			free(MM_Top); //remove top block

			MM_Top = temp; //top block  = penultimate
		}
		else
		{
			/*Searching for memory block with right data - search from end is faster */
			while(temp->dataPtr != ptr)
			{
				if(temp->prevPtr == NULL)
				{
#if DEBUG
					mistake(ERR_INTERN, "Memory block not found\n");
#else
					mistake(ERR_INTERN);
#endif
				}
				afterData = temp;
				temp = temp->prevPtr;
			}

			/*Pointer re-wiring*/
			afterData->prevPtr = temp->prevPtr;

			if(invalid == 1)
				free(temp->dataPtr);

			free(temp);
		}
	}
	else
	{
#if DEBUG
		mistake(ERR_INTERN, "MM was not Initialized\n");
#else
		mistake(ERR_INTERN);
#endif
	}
#if DEBUG
	memoryBlocksCount--;
#endif
}
