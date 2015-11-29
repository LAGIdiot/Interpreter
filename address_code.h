#ifndef AC_Header
#define AC_Header

#include <stdio.h>
#include "errors.h"
#include "memory_manager.h"
#include "symbol_table.h"
#include "deque.h"

enum operatinType{
	OT_OP_ADD,
	OT_OP_SUBB,
	OT_OP_DIV,
	OT_OP_MUL,

	OT_LABEL,
	OT_JUMP,
	OT_JUMP_GREATER,
	OT_JUMP_GREATER_EQUAL,
	OT_JUMP_LESS,
	OT_JUMP_LESS_EQUAL,
	OT_JUMP_EQUAL,
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
