///////////////////////////////////////////////////////////////////////////////
/* ---------- IMPLEMENTACE INTERPRETU IMPERATIVNÍHO JAZYKA IFJ15 ----------- */
///////////////////////////////////////////////////////////////////////////////
//
//	AUTOŘI:
//
//	xbedna57 	ADAM BEDNÁRIK 	()
//	xmacha63 	ERIK MACHÁČEK 	()
//	xmalar02 	MARTIN MALÁRIK 	()
//	xklaci00 	MICHAL KLACIK 	()
//	xlengu00 	MANH LE NGUYEN 	()
//
///////////////////////////////////////////////////////////////////////////////

#ifndef DEQUE_Header
#define DEQUE_Header

#include <stdio.h>

#include "errors.h"

//Enumes
enum dequeueTypes{
	DEQUE,
	QUEUE,
	STACK,
}type;

//Structures
typedef struct dequeContainerStruct{
	void * prevPtr;
	void * nextPtr;
	void * dataPtr;
}*DequeContainer;

typedef struct dequeStruct{
	int type;
	DequeContainer last;
	DequeContainer first;
	DequeContainer active;
	int member_counter;
}*Deque;

//Functions
Deque S_Init();
void S_Terminate(Deque stack);

void S_Push(Deque stack, void * data);
void * S_Pop(Deque stack);
void * S_Top(Deque stack);

int S_Empty(Deque stack);

Deque D_Init();
void D_Terminate(Deque deque);

void D_PushBack(Deque deque, void * data);
void D_PushFront(Deque deque, void * data);

void * D_PopFront(Deque deque);
void * D_TopFront(Deque deque);

void * D_PopBack(Deque deque);
void * D_TopBack(Deque deque);

int D_Empty(Deque deque);
int D_MemberCountGet(Deque deque);

int D_ActivateFront(Deque deque);
int D_ActivateBack(Deque deque);

int D_IsActive(Deque deque);

int D_ActiveMoveToFront(Deque deque);
int D_ActiveMoveToBack(Deque deque);

void * D_TopActive(Deque deque);

#endif //DEQUE_Header
