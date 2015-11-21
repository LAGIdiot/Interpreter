#ifndef STACK_Header
#define STACK_Header

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "memory_manager.h"

typedef struct stackContainerStruct{
	void * prevPtr;
	void * dataPtr;
}*StackContainer;

typedef struct stackStruct{
	void * last;
#if DEBUG
	int member_counter;
#endif
}*Stack;

Stack S_Init();
void S_Terminate(Stack stack);

void S_Push(Stack stack, void * data);
void S_PushSecond(Stack stack, void * data);
void *S_Pop(Stack stack);
void *S_Top(Stack stack);

int S_Empty(Stack stack);

#endif
