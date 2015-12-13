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

#include "deque.h"

//////////////////////////////////////////////////
// void * S_Push(Stack stack)
// stack - pointer to stack
////////////////////
// Will put data on top of stack
//////////////////////////////////////////////////
void S_Push(Deque stack, void * data)
{
#if DEBUG2
	printf("Pushing data to stack: %d\n", stack);
#endif
	if(stack != NULL && stack->type == STACK)
	{
		DequeContainer container = MM_Malloc(sizeof(struct dequeContainerStruct));

		container->prevPtr = stack->last;
		container->dataPtr = data;

		stack->last = container;
		stack->member_counter++;
	}
	else
		mistake(ERR_INTERN, "You can't be serious about pushing thinks on uninitialized stack? OR Using wrongly initialized deque as stack\n");
}

//////////////////////////////////////////////////
// void * S_Pop(Stack stack)
// stack - pointer to stack
// return - pointer to data
////////////////////
// Return pointer to data or NULL and remove top data from stack
//////////////////////////////////////////////////
void *S_Pop(Deque stack)
{
#if DEBUG2
	printf("Popping data from stack: %d\n", stack);
#endif
	if(stack != NULL && stack->type == STACK)
	{
		if(stack->last != NULL)
		{
			DequeContainer container = stack->last;
			stack->member_counter--;

			stack->last = container->prevPtr;

			void * data = container->dataPtr;

			MM_Free(container);

			return data;
		}
	}
	else
		mistake(ERR_INTERN, "Did you just try pop something from uninitialized stack? OR Using wrongly initialized deque as stack\n");
	return NULL;
}

//////////////////////////////////////////////////
// void * S_Top(Stack stack)
// stack - pointer to stack
// return - pointer to data
////////////////////
// Return pointer to data on top of stack or NULL
//////////////////////////////////////////////////
void *S_Top(Deque stack)
{
#if DEBUG2
	printf("Looking at to of stack: %d\n", stack);
#endif
	if(stack != NULL && stack->type == STACK)
	{
		if(stack->last != NULL)
		{
			DequeContainer container = stack->last;
			return container->dataPtr;
		}
	}
	else
		mistake(ERR_INTERN, "Did you just try to look at top of from uninitialized stack? OR Using wrongly initialized deque as stack\n");
	return NULL;
}

//////////////////////////////////////////////////
// Stack S_Init()
// return - pointer to stack
////////////////////
// Initialize stack - set its top member to NULL
//////////////////////////////////////////////////
Deque S_Init()
{
	Deque stack = MM_Malloc(sizeof(struct dequeStruct));

	stack->type = STACK;

	stack->last = NULL;
	stack->active = NULL;
	stack->first = NULL;
	stack->member_counter = 0;

#if DEBUG
	printf("Stack initialized at: %d\n", stack);
#endif
	return stack;
}

//////////////////////////////////////////////////
// Stack S_Terminate()
// stack - pointer to stack
////////////////////
// Terminate stack and free all its data
//////////////////////////////////////////////////
void S_Terminate(Deque stack)
{
#if DEBUG
	printf("Terminating stack at: %d\n", stack);
#endif
	if(stack != NULL && stack->type == STACK)
	{
		DequeContainer container = NULL;

		while(stack->last != NULL)
		{
			container = stack->last;

			stack->last = container->prevPtr;

			MM_Free(container->dataPtr);
			MM_Free(container);
		}
		MM_Free(stack);
	}
	else
		mistake(ERR_INTERN, "Stack for terminating doesn't exist\n");

	stack->member_counter = 0;
}

//////////////////////////////////////////////////
// int S_Empty()
// stack - pointer to stack
// return - empty
////////////////////
// Return value 1 if stack is empty, 0 if is NOT empty and -1 if uninitialized
//////////////////////////////////////////////////
int S_Empty(Deque stack)
{
	if(stack != NULL && stack->type == STACK)
	{
#if DEBUG
		printf("Somebody asked if the stack at: %d is empty and there is quantity of members in it: %d\n", stack, (int)stack->member_counter);
#endif
		return stack->last == NULL ? 1 : 0;
	}
	return -1;
}

Deque D_Init()
{
	Deque deque = MM_Malloc(sizeof(struct dequeStruct));

	deque->type = DEQUE;

	deque->active = NULL;
	deque->first = NULL;
	deque->last = NULL;
	deque->member_counter = 0;

#if DEBUG
	printf("Initializing deque at %d\n", deque);
#endif

	return deque;
}

void D_Terminate(Deque deque)
{
#if DEBUG
	printf("Terminating deque at: %d\n", deque);
#endif
	if(deque != NULL && deque->type == DEQUE)
	{
		DequeContainer container = NULL;

		while(deque->last != NULL)
		{
			container = deque->last;

			deque->last = container->prevPtr;

			MM_Free(container->dataPtr);
			MM_Free(container);
		}
		MM_Free(deque);
	}
	else
		mistake(ERR_INTERN, "Deque for terminating doesn't exist\n");

	deque->member_counter = 0;

}

void D_PushBack(Deque deque, void * data)
{
#if DEBUG2
	printf("Pushing data to back of deque: %d\n", deque);
#endif
	if(deque != NULL && deque->type == DEQUE)
	{
		DequeContainer container = MM_Malloc(sizeof(struct dequeContainerStruct));
		deque->member_counter++;

		container->dataPtr = data;
		container->nextPtr = NULL;

		if(deque->last == NULL)
		{
			container->prevPtr = NULL;
			deque->last = container;
		}
		else
		{
			container->prevPtr = deque->last;
			deque->last->nextPtr = container;

			deque->last = container;
		}

		if(deque->first == NULL)
			deque->first = container;
	}
	else
		mistake(ERR_INTERN,"Pushing back to uninitialized deque\n");
}

void D_PushFront(Deque deque, void * data)
{
#if DEBUG2
	printf("Pushing data to front of deque: %d\n", deque);
#endif
	if(deque != NULL && deque->type == DEQUE)
	{
		DequeContainer container = MM_Malloc(sizeof(struct dequeContainerStruct));
		deque->member_counter++;


		container->dataPtr = data;
		container->prevPtr = NULL;

		if(deque->first == NULL)
		{
			container->nextPtr = NULL;
			deque->first = container;
		}
		else
		{
			container->nextPtr = deque->first;
			deque->first->prevPtr = container;

			deque->first = container;
		}

		if(deque->last == NULL)
			deque->last = container;
	}
	else
		mistake(ERR_INTERN,"Pushing back to uninitialized deque\n");
}

void * D_PopFront(Deque deque)
{
#if DEBUG2
	printf("Popping data from front of deque: %d\n", deque);
#endif
	if(deque != NULL && deque->type == DEQUE)
	{
		DequeContainer container = deque->first;
		deque->member_counter--;


		if(deque->active == deque->first)
			deque->active = NULL;

		if(deque->last == deque->first)
			deque->last = NULL;

		deque->first = container->nextPtr;

		void * data = container->dataPtr;

		MM_Free(container);

		return data;
	}
	else
		mistake(ERR_INTERN, "There was problem with toping deque\n");
	return NULL;
}

void * D_TopFront(Deque deque)
{
#if DEBUG2
	printf("Looking on data from front of deque: %d\n", deque);
#endif
	if(deque != NULL && deque->type == DEQUE)
		return deque->first->dataPtr;
	else
		mistake(ERR_INTERN, "There was problem with toping deque\n");
	return NULL;
}

void * D_PopBack(Deque deque)
{
#if DEBUG2
	printf("Popping data from back of deque: %d\n", deque);
#endif
	if(deque != NULL && deque->type == DEQUE)
	{
		DequeContainer container = deque->last;
		deque->member_counter--;


		if(deque->last == deque->first)
			deque->last = NULL;

		if(deque->active == deque->first)
			deque->active = NULL;

		deque->last = container->prevPtr;

		void * data = container->dataPtr;

		MM_Free(container);

		return data;
	}
	else
		mistake(ERR_INTERN, "There was problem with toping deque\n");
	return NULL;
}

void * D_TopBack(Deque deque)
{
#if DEBUG
	printf("Looking on data from back of deque: %d\n", deque);
#endif
	if(deque != NULL && deque->type == DEQUE)
		return deque->last->dataPtr;
	else
		mistake(ERR_INTERN, "There was problem with toping deque\n");
	return NULL;
}

int D_Empty(Deque deque)
{
	if(deque != NULL && deque->type == DEQUE)
	{
#if DEBUG
		printf("Somebody asked if the deque at: %d is empty and there is quantity of members in it: %d\n", deque, (int)deque->member_counter);
#endif
		return deque->last == NULL ? 1 : 0;
	}
	else
		mistake(ERR_INTERN, "Problem with size in deque\n");
	return -1;
}

int D_ActivateFront(Deque deque)
{
	if(deque == NULL)
		return -1;

#if DEBUG2
	printf("Activating front of deque: %d\n", deque);
#endif

	if(deque->first == NULL)
		return 0;
	else
	{
		deque->active = deque->first;
		return 1;
	}
}
int D_ActivateBack(Deque deque)
{
	if(deque == NULL)
		return -1;

#if DEBUG2
	printf("Activating back of deque: %d\n", deque);
#endif

	if(deque->last == NULL)
		return 0;
	else
	{
		deque->active = deque->last;
		return 1;
	}
}

int D_IsActive(Deque deque)
{
	if(deque == NULL)
		return -1;

#if DEBUG2
	printf("Is deque active: %s\n", deque->active == NULL ? "FALSE" : "TRUE");
#endif

	return deque->active == NULL ? 0 : 1;
}

int D_ActiveMoveToFront(Deque deque)
{
	if(deque == NULL)
		return -1;

#if DEBUG2
	printf("Moving activity of deque: %d to front\n", deque);
#endif

	if(deque->active == deque->first)
	{
		deque->active = NULL;
		return 0;
	}
	else
	{
		deque->active = deque->active->prevPtr;
		return 1;
	}
}

int D_ActiveMoveToBack(Deque deque)
{
	if(deque == NULL)
		return -1;

#if DEBUG2
	printf("Moving activity of deque: %d to back\n", deque);
#endif

	if(deque->active == deque->last)
	{
		deque->active = NULL;
		return 0;
	}
	else
	{
		deque->active = deque->active->nextPtr;
		return 1;
	}
}

void * D_TopActive(Deque deque)
{
	if(deque == NULL)
		return NULL;

#if DEBUG
	printf("Looking on data from active member of deque: %d\n", deque);
#endif

	return deque->active->dataPtr;
}

int D_MemberCountGet(Deque deque)
{
	if(deque == NULL)
		return -1;
#if DEBUG
	printf("Member count in deque: %d is \n", deque, deque->member_counter);
#endif
	return deque->member_counter;
}
