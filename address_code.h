#ifndef AC_Header
#define AC_Header

#include <stdio.h>
#include "errors.h"
#include "memory_manager.h"
#include "symbol_table.h"
#include "deque.h"

static const char * DUMMY = "#dummy";

enum operatinType{
	AC_OP_ADD,
	AC_OP_SUBB,
	AC_OP_DIV,
	AC_OP_MUL,

	AC_LABEL,
	AC_JUMP,
	AC_JUMP_GREATER,
	AC_JUMP_GREATER_EQUAL,
	AC_JUMP_LESS,
	AC_JUMP_LESS_EQUAL,
	AC_JUMP_EQUAL,
	AC_JUMP_NOT_EQUAL,
};

typedef struct AC_ItemStruct{
	int operation;
	void *source1;
	void *source2;
	void *destination;
}*AC_itemPtr;

Deque AC_Init();
void AC_Terminate(Deque deque);

void AC_Add(Deque deque, AC_itemPtr item);
AC_itemPtr AC_I_Create(int op, void * source1, void * source2, void * destination);

#endif //AC_Header
