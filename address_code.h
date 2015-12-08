#ifndef AC_Header
#define AC_Header

#include <stdio.h>
#include "errors.h"
#include "memory_manager.h"
#include "symbol_table.h"
#include "deque.h"

enum operatinType{
	AC_OP_ADD,
	AC_OP_SUB,
	AC_OP_DIV,
	AC_OP_MUL,

	AC_OP_ASSIGN,

	AC_LABEL,
	AC_LABEL_END,	//label konce platnosti - mezi nim a LABEL se stajnym jmenem je platnost symbolu
	AC_JUMP,
	AC_JUMP_C_TRUE,
	AC_JUMP_C_FALSE,
	AC_JUMP_C_FALSE_E, //skace na label konce platnosti

	AC_GREATER,
	AC_GREATER_EQUAL,
	AC_LESS,
	AC_LESS_EQUAL,
	AC_EQUAL,
	AC_NOT_EQUAL,

	AC_CALL_CIN,
	AC_CALL_COUT,
	AC_CALL_CONCAT,
	AC_CALL_SUBSTR,
	AC_CALL_FIND,
	AC_CALL_LENGTH,
	AC_CALL_SORT,

	AC_CALL_DUMMY,	//slouzi k posilani parametru ktere by se nevesly
	AC_CALL,
	AC_RETURN,
};

/*	Priklady jednotlivych operaci:
 *
 */

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
