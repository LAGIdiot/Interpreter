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
	TT_UNDEFINED,	/* zatim vyuzito jen u komentaru - nikdy by nemelo byt vraceno*/
	TT_EOF,			/* EOF	*/
	TT_SEMICOLN,	/* ;	*/
	TT_HASH,		/* #	*/
	TT_STAR,		/* *	*/
	TT_PLUS,		/* +	*/
	TT_MINUS,		/* -	*/
	TT_DIVIDE,		/* /	*/

	TT_ASSIGN,		/* = */
	TT_ASSIGN_MUL,	/* *=	*/
	TT_ASSIGN_ADD,	/* +=	*/
	TT_ASSIGN_SUB,	/* -=	*/
	TT_ASSIGN_DIV,	/* /=	*/

	TT_EQUAL,		/* ==	*/

	TT_IDENTIFIER,
	TT_KEYWORD,

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

			/* == */
	TT_EQUAL_NOT,	/* != */
	TT_EQUAL_LESS,	/* <= */
	TT_EQUAL_GREATER,	/* >= */

	TT_LESS,		/* < */
	TT_GREATER,		/* > */

	TT_UNRECOGNIZED,
}Typ;

//Function prototypes
tTokenPtr T_Init();
void T_Update(char c);
void T_Destroy(tTokenPtr tokenPtr);
void T_Finish(tTokenPtr tokenPtr);

void T_SystemInit();
void T_SystemTerminate();

extern void T_Get(tTokenPtr tokenPtr);

#endif //T_Header
