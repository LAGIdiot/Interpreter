#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

#include "memory_manager.h"

MemoryBlockPtr MM_Head;
MemoryBlockPtr MM_Last;

//Function prototypes - private
void MM_Add(void * ptr);
void MM_Remove(void * ptr, int invalid);

void MM_Init()
{
#if DEBUG
	printf("Initializing Memory Manager\n");
#endif

	MM_Head = NULL;
	MM_Last = NULL;
}

void * MM_Malloc(size_t size)
{
	void * ptr = malloc(size);

	if(ptr == NULL)
	{
#if DEBUG
		mistake(ERR_INTERN, "Memory allocation problem");
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

	//pokud je traba premapuje se
	if(ptr != ptrOld)
	{
		MM_Remove(ptrOld, 1);
		MM_Add(ptr);
	}

	return ptr;
}

void MM_Free(void * ptr)
{
#if DEBUG
	printf("Freeing memory from: %d\n", ptr);
#endif

	MM_Remove(ptr, 0);
}

void MM_FreeAll()
{
#if DEBUG
	printf("Freeing ALL memory\n");
#endif

	if(MM_Last != NULL && MM_Head != NULL) //Overi zda je vube co odstranovat
	{
		MemoryBlockPtr temp = MM_Last;
		MemoryBlockPtr tempPrev;

		while(temp != NULL)
		{
			tempPrev = temp->prevPtr; //uschovani predposledniho

			free(temp->dataPtr); //odstraneni dat z posledniho
			free(temp); //odstraneni blocku

			temp = tempPrev; //posunuti se na predchozi block
		}

		//reseting MM_Head & MM_Last
		MM_Head = NULL;
		MM_Last = NULL;
	}
}

void MM_Add(void * ptr)
{
	MemoryBlockPtr newBlock = malloc(sizeof(struct MemoryBlockStruct));
	if(newBlock == NULL)
		mistake(ERR_INTERN);

	newBlock->dataPtr = ptr; //vlozi pointer jako data
	newBlock->nextPtr = NULL;
	newBlock->prevPtr = NULL;

	if(MM_Head == NULL)
		MM_Head = newBlock; //novy block (pouze 1. vytvoreny) ulozi do hlavicky

	if(MM_Last != NULL)
	{
		MM_Last->nextPtr = newBlock; //do posledniho priradi pointer na novy block
		newBlock->prevPtr = MM_Last; //do nove vznikleho blocku ulozi pointer na posledni
	}
	MM_Last = newBlock; //novy block zpristupni jako posledni
}

void MM_Remove(void * ptr, int invalid) //invalid parametr slouzi k odstraneni zaznamu po realokaci (1)
{
	if(MM_Last != NULL && MM_Head != NULL) //Overi zda je vube co odstranovat
	{
		MemoryBlockPtr temp = MM_Last->prevPtr; //vytahnu si predposledni

		if(MM_Last->dataPtr == ptr)
		{
			if(invalid == 0)
				free(MM_Last->dataPtr); //odstraneni dat z posledniho

			free(MM_Last); //odstraneni posledniho

			MM_Last = temp; //nastaveni pointeru MM_Last predposledni prvek
			MM_Last->nextPtr = NULL; //zneplatneni pointeru na smazany prvek

		}
		else
		{
			while(temp->dataPtr != ptr) //prohledava MemoryBlocky od konce dokud nenarazy na ten se spravnymi daty
			{
				if(temp->prevPtr == NULL)
					mistake(ERR_INTERN);
				temp = temp->nextPtr;
			}

			/*Predratovani pointeru*/
			MemoryBlockPtr tempPrev = temp->prevPtr;
			MemoryBlockPtr tempNext = temp->nextPtr;

			tempPrev->nextPtr = tempNext;
			tempNext->prevPtr = tempPrev;

			if(invalid == 0)
				free(temp->dataPtr); //odstraneni dat z posledniho

			free(temp); //odstraneni blocku
		}
	}
}
