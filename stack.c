#include "stack.h"

//////////////////////////////////////////////////
// void * S_Push(Stack stack)
// stack - pointer to stack
////////////////////
// Will put data on top of stack
//////////////////////////////////////////////////
void S_Push(Stack stack, void * data)
{
#if DEBUG
	printf("Pushing data to stack: %d\n", stack);
#endif
	if(stack != NULL)
	{
		StackContainer container= MM_Malloc(sizeof(struct stackContainerStruct));

		container->prevPtr = stack->last;
		container->dataPtr = data;

		stack->last = container;
#if DEBUG
		stack->member_counter++;
#endif
	}
	else
	{
#if DEBUG
		mistake(ERR_INTERN, "You can't be serious about pushing thinks on uninitialized stack?\n");
#endif
	}
}

//////////////////////////////////////////////////
// void * S_PushSecond(Stack stack)
// stack - pointer to stack
////////////////////
// Will put data on second place from top on stack
//////////////////////////////////////////////////
void S_PushSecond(Stack stack, void * data)
{
#if DEBUG
	printf("Pushing SECOND data on stack: %d\n", stack);
#endif
	if(stack != NULL)
	{
		StackContainer container = MM_Malloc(sizeof(struct stackContainerStruct));

		StackContainer temp = stack->last;

		container->prevPtr = temp->prevPtr;
		container->dataPtr = data;

		temp->prevPtr = container;
#if DEBUG
		stack->member_counter++;
#endif
	}
	else
	{
#if DEBUG
		mistake(ERR_INTERN, "You can't be serious about pushing thinks on uninitialized stack?\n");
#endif
	}
}

//////////////////////////////////////////////////
// void * S_Pop(Stack stack)
// stack - pointer to stack
// return - pointer to data
////////////////////
// Return pointer to data or NULL and remove top data from stack
//////////////////////////////////////////////////
void *S_Pop(Stack stack)
{
#if DEBUG
	printf("Popping data from stack: %d\n", stack);
#endif
	if(stack != NULL)
	{
		if(stack->last != NULL)
		{
			StackContainer container = stack->last;

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
	{
#if DEBUG
		mistake(ERR_INTERN, "Did you just try pop something from uninitialized stack? Really\n");
#endif
	}
	return NULL;
}

//////////////////////////////////////////////////
// void * S_Top(Stack stack)
// stack - pointer to stack
// return - pointer to data
////////////////////
// Return pointer to data on top of stack or NULL
//////////////////////////////////////////////////
void *S_Top(Stack stack)
{
#if DEBUG
	printf("Looking at to of stack: %d\n", stack);
#endif
	if(stack != NULL)
	{
		if(stack->last != NULL)
		{
			StackContainer container = stack->last;
			return container->dataPtr;
		}
	}
	else
	{
#if DEBUG
		mistake(ERR_INTERN, "Did you just try to look at top of from uninitialized stack?\n");
#endif
	}
	return NULL;
}

//////////////////////////////////////////////////
// Stack S_Init()
// return - pointer to stack
////////////////////
// Initialize stack - set its top member to NULL
//////////////////////////////////////////////////
Stack S_Init()
{
	Stack stack = MM_Malloc(sizeof(struct stackStruct));

	stack->last = NULL;

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
void S_Terminate(Stack stack)
{
#if DEBUG
	printf("Terminating stack at: %d\n", stack);
#endif
	if(stack != NULL)
	{
		StackContainer container = NULL;

		while(stack->last != NULL)
		{
			container = stack->last;

			stack->last = container->prevPtr;

			MM_Free(container->dataPtr);
			MM_Free(container);
		}
		MM_Free(stack);
	}
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
int S_Empty(Stack stack)
{
	if(stack != NULL)
	{
#if DEBUG
		printf("Somebody asked if the stack at: %d is empty and there is quantity of members in it: %d\n", stack, (int)stack->member_counter);
#endif
		return stack->last == NULL ? 1 : 0;
	}
	return -1;
}
