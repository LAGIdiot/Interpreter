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
	uint member_counter;
#endif
}*Stack;

Stack Init();

void Push(Stack stack, void * data);
void *Pop(Stack stack);
void *Top(Stack stack);

int Empty(Stack stack);

#endif
