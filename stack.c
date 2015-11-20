#include "stack.h"

//////////////////////////////////////////////////
// void * Top(Stack stack)
// stack - pointer to stack
////////////////////
// Will put data on top of stack
//////////////////////////////////////////////////
void Push(Stack stack, void * data)
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
// void * Pop(Stack stack)
// stack - pointer to stack
// return - pointer to data
////////////////////
// Return pointer to data or NULL and remove top data from stack
//////////////////////////////////////////////////
void *Pop(Stack stack)
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
// void * Top(Stack stack)
// stack - pointer to stack
// return - pointer to data
////////////////////
// Return pointer to data on top of stack or NULL
//////////////////////////////////////////////////
void *Top(Stack stack)
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
// Stack Init()
// return - pointer to stack
////////////////////
// Initialize stack - set its top member to NULL
//////////////////////////////////////////////////
Stack Init()
{
	Stack stack = MM_Malloc(sizeof(struct stackStruct));

	stack->last = NULL;

#if DEBUG
	printf("Stack initialized at: %d\n", stack);
#endif
	return stack;
}

//////////////////////////////////////////////////
// int Empty()
// stack - pointer to stack
// return - empty
////////////////////
// Return value 1 if stack is empty, 0 if is NOT empty and -1 if uninitialized
//////////////////////////////////////////////////
int Empty(Stack stack)
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
