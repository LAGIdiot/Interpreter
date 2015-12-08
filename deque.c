#include "deque.h"

//////////////////////////////////////////////////
// void * S_Push(Stack stack)
// stack - pointer to stack
////////////////////
// Will put data on top of stack
//////////////////////////////////////////////////
void S_Push(Deque stack, void * data)
{
#if DEBUG
	printf("Pushing data to stack: %d\n", stack);
#endif
	if(stack != NULL && stack->type == STACK)
	{
		DequeContainer container = MM_Malloc(sizeof(struct dequeContainerStruct));

		container->prevPtr = stack->last;
		container->dataPtr = data;

		stack->last = container;
#if DEBUG
		stack->member_counter++;
#endif
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
#if DEBUG
	printf("Popping data from stack: %d\n", stack);
#endif
	if(stack != NULL && stack->type == STACK)
	{
		if(stack->last != NULL)
		{
			DequeContainer container = stack->last;

			stack->last = container->prevPtr;

			void * data = container->dataPtr;

			MM_Free(container);

			return data;
#if DEBUG
		stack->member_counter--;
#endif
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
#if DEBUG
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

#if DEBUG
	printf("Stack initialized at: %d\n", stack);
	stack->member_counter = 0;
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
#if DEBUG
	stack->member_counter = 0;
#endif
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
	Deque deque = MM_Malloc(sizeof(struct dequeContainerStruct));

	deque->type = DEQUE;

	deque->active = NULL;
	deque->first = NULL;
	deque->last = NULL;

#if DEBUG
	printf("Initializing queue at %d\n", deque);
	deque->member_counter = 0;
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
#if DEBUG
	deque->member_counter = 0;
#endif
}

void D_PushBack(Deque deque, void * data)
{
#if DEBUG
	printf("Pushing data to back of deque: %d\n", deque);
#endif
	if(deque != NULL && deque->type == DEQUE)
	{
		DequeContainer container = MM_Malloc(sizeof(struct dequeContainerStruct));

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
#if DEBUG
	printf("Pushing data to front of deque: %d\n", deque);
#endif
	if(deque != NULL && deque->type == DEQUE)
	{
		DequeContainer container = MM_Malloc(sizeof(struct dequeContainerStruct));

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
#if DEBUG
	printf("Popping data from deque: %d\n", deque);
#endif
	if(deque != NULL && deque->type == DEQUE)
	{
		DequeContainer container = deque->first;

		if(deque->active == deque->first)
			deque->active = NULL;

		if(deque->last == deque->first)
			deque->last = NULL;

		deque->first = container->nextPtr;

		return container;
	}
	else
		mistake(ERR_INTERN, "There was problem with toping deque\n");
	return NULL;
}

void * D_TopFront(Deque deque)
{
#if DEBUG
	printf("Getting data from top front of deque: %d\n", deque);
#endif
	if(deque != NULL && deque->type == DEQUE)
		return deque->first;
	else
		mistake(ERR_INTERN, "There was problem with toping deque\n");
	return NULL;
}

void * D_PopBack(Deque deque)
{
#if DEBUG
	printf("Popping data from deque: %d\n", deque);
#endif
	if(deque != NULL && deque->type == DEQUE)
	{
		DequeContainer container = deque->last;

		if(deque->last == deque->first)
			deque->last = NULL;

		if(deque->active == deque->first)
			deque->active = NULL;

		deque->last = container->prevPtr;

		return container;
	}
	else
		mistake(ERR_INTERN, "There was problem with toping deque\n");
	return NULL;
}

void * D_TopBack(Deque deque)
{
#if DEBUG
	printf("Getting data from top front of deque: %d\n", deque);
#endif
	if(deque != NULL && deque->type == DEQUE)
		return deque->last;
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
