#include "address_code.h"

Deque AC_Init()
{
#if DEBUG
	printf("Initializing address code\n");
#endif
	Deque deque = D_Init();
	return deque;
}
//TODO: Test this: May have problem with leaving allocated memory - maybe not because symbol table will do it
void AC_Terminate(Deque deque)
{
#if DEBUG
	printf("Terminating address code\n");
#endif
	D_Terminate(deque);
}

AC_itemPtr AC_I_Create(int op, void * source1, void * source2, void * destination)
{
#if DEBUG
	printf("Creating address code item for operation %d\n",op);
#endif
	AC_itemPtr item = MM_Malloc(sizeof(struct AC_ItemStruct));
	item->operation = op;
	item->destination = destination;
	item->source1 = source1;
	item->source2 = source2;

	return item;
}

void AC_Add(Deque deque, AC_itemPtr item)
{
#if DEBUG
	printf("Adding AC_item %d to deque %d\n",item, deque);
#endif
	if(deque != NULL)
		D_PushBack(deque, item);
	else
		mistake(ERR_INTERN,"Problem with adding AC_item to deqeu\n");
}
