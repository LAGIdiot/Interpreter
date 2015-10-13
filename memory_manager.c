#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

#include "memory_manager.h"

MemoryBlockPtr MM_Head;
MemoryBlockPtr MM_Last;

//Function prototypes - private
void MM_Add(void * ptr);
void MM_Remove(void * ptr, int invalid);

//////////////////////////////////////////////////
// void MM_Init()
////////////////////
// Initialize memory manager - set its head and last member to NULL
//////////////////////////////////////////////////
void MM_Init()
{
#if DEBUG
	printf("Initializing Memory Manager\n");
#endif

	MM_Head = NULL;
	MM_Last = NULL;
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
// note: memory must be deleted from last added block - otherwise there will be loses (e. g.: data in Token)
//////////////////////////////////////////////////
void MM_FreeAll()
{
#if DEBUG
	printf("Freeing ALL memory\n");
#endif

	if(MM_Last != NULL && MM_Head != NULL) //Check if there is any memory to free
	{
		MemoryBlockPtr temp = MM_Last;
		MemoryBlockPtr tempPrev;

		/*Store penultimate member, delete data from last one, delete last one, penultimate == last one*/
		while(temp != NULL)
		{
			tempPrev = temp->prevPtr;

			free(temp->dataPtr);
			free(temp);

			temp = tempPrev;
		}

		//reseting MM_Head & MM_Last
		MM_Head = NULL;
		MM_Last = NULL;
	}
#if DEBUG
	else
	{
		printf("No need\n");
	}
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
#if DEBUG
	printf("Adding pointer: %d to MM\n", ptr);
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
	newBlock->nextPtr = NULL;
	newBlock->prevPtr = NULL;

	if(MM_Head == NULL) //only for first run
		MM_Head = newBlock;

	if(MM_Last != NULL)
	{
		MM_Last->nextPtr = newBlock; //in last block assign nextPtr to newBlock
		newBlock->prevPtr = MM_Last; //in newBlock assign prevPtr to last block
	}
	MM_Last = newBlock; //newBlock make available as last block
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
	printf("Removing pointer: %d from MM - block is invalid: %s\n", ptr, invalid == 1 ? "TRUE" : "ELSE");
#endif
	if(MM_Last != NULL && MM_Head != NULL) //Check if there is any memory to free
	{
		MemoryBlockPtr temp = MM_Last->prevPtr; //get penultimate block

		/*There is big chance that we will be removing last added block first*/
		if(MM_Last->dataPtr == ptr)
		{
			if(invalid == 1)
				free(MM_Last->dataPtr);

			free(MM_Last); //remove last block

			MM_Last = temp; //last block  = penultimate
			MM_Last->nextPtr = NULL; //invalidation of nextPtr in last block

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
				temp = temp->nextPtr;
			}

			/*Pointer re-wiring*/
			MemoryBlockPtr tempPrev = temp->prevPtr;
			MemoryBlockPtr tempNext = temp->nextPtr;
			tempPrev->nextPtr = tempNext;
			tempNext->prevPtr = tempPrev;

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
}
