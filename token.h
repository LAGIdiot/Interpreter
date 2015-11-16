#ifndef T_Header
#define T_Header

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "memory_manager.h"

//Structures
#if DEBUG
typedef struct TokenStruct{
	int typ;
	int row;
	int column;
	char *data;
}*tTokenPtr;
#else
typedef struct TokenStruct{
	int typ;
	char *data;
}*tTokenPtr;
#endif

//Enums
/*Nutno dodefinovat další dle potřeby*/
enum TokenType{
	TT_IDENTIFIER,
	TT_KEYWORD,

	TT_EOF,

	TT_PAR_L, 		/* ( */
	TT_PAR_R, 		/* ) */
	TT_BRACE_L, 	/* { */
	TT_BRACE_R,		/* { */
	TT_BRACKET_L,	/* [ */
	TT_BRACKET_R,	/* ] */

	TT_INT,
	TT_DOUBLE,
	TT_STRING,
	TT_CHAR,

	TT_OP_ADD,		/* + */
	TT_OP_SUB,		/* - */
	TT_OP_DIV,		/* / */
	TT_OP_MUL,		/* * */

	TT_ASSIGN,		/* = */
	TT_ASSIGN_ADD,	/* += */
	TT_ASSIGN_SUB,	/* -= */
	TT_ASSIGN_DIV,	/* /= */
	TT_ASSIGN_MUL,	/* *= */

	TT_EQUALS,		/* == */
	TT_EQUALS_NOT,	/* != */
	TT_EQUALS_LESS,	/* <= */
	TT_EQUALS_GREATER,	/* >= */

	TT_LESS,		/* < */
	TT_GREATER,		/* > */
}Typ;

//Function prototypes
tTokenPtr T_Init();
void T_Update(tTokenPtr tokenPtr, char nextChar);
void T_Destroy(tTokenPtr tokenPtr);
void T_Finish(tTokenPtr tokenPtr);

extern void T_Get(tTokenPtr tokenPtr);

#endif //T_Header
