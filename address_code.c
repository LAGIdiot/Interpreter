///////////////////////////////////////////////////////////////////////////////
/* ---------- IMPLEMENTACE INTERPRETU IMPERATIVNÍHO JAZYKA IFJ15 ----------- */
///////////////////////////////////////////////////////////////////////////////
//
//	AUTOŘI:
//
//	xbedna57 	ADAM BEDNÁRIK
//	xmacha63 	ERIK MACHÁČEK
//	xmalar02 	MARTIN MALÁRIK
//	xlengu00 	MANH LE NGUYEN
//
///////////////////////////////////////////////////////////////////////////////

#include "address_code.h"

//////////////////////////////////////////////////
// Deque AC_Init()
////////////////////
// initialization of address code
//////////////////////////////////////////////////
Deque AC_Init()
{
#if DEBUG
	printf("Initializing address code\n");
#endif
	Deque deque = D_Init();
	return deque;
}

//////////////////////////////////////////////////
// void AC_Terminate(Deque deque)
////////////////////
// terminates adress code
//////////////////////////////////////////////////
void AC_Terminate(Deque deque)
{
#if DEBUG
	printf("Terminating address code\n");
#endif
	D_Terminate(deque);
}

//////////////////////////////////////////////////
// AC_itemPtr AC_I_Create(int op, void * source1, void * source2, void * destination)
// op - operation which is in use
// *source1 - package of data
// *source2 - package of data
// *destination - package of data
////////////////////
// creates package of three address code
//////////////////////////////////////////////////
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
//////////////////////////////////////////////////
// void AC_Add(Deque deque, AC_itemPtr item)
// deque - deque of data
// item - package of three address code
////////////////////
// adds package of three address code to deque
//////////////////////////////////////////////////
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
