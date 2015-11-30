#ifndef T_Header
#define T_Header

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "memory_manager.h"

//Structures
typedef struct TokenStruct{
	int typ;
	char *data;
}*tTokenPtr;

//Enums
/*Nutno dodefinovat další dle potřeby*/
enum TokenType{
	TT_UNDEFINED,	/* nikdy by nemelo byt vraceno*/
	TT_EOF,			/* EOF	*/
	TT_SEMICOLN,	/* ;	*/
	TT_HASH,		/* #	*/
	TT_STAR,		/* *	*/
	TT_PLUS,		/* +	*/
	TT_MINUS,		/* -	*/
	TT_DIVIDE,		/* /	*/

	TT_ASSIGN,		/* = 	*/
	TT_ASSIGN_MUL,	/* *=	*/
	TT_ASSIGN_ADD,	/* +=	*/
	TT_ASSIGN_SUB,	/* -=	*/
	TT_ASSIGN_DIV,	/* /=	*/

	TT_EQUAL,		/* ==	*/
	TT_EQUAL_LESS,	/* <=	*/
	TT_EQUAL_GREATER,	/* >=	*/

	TT_LESS,		/* <	*/
	TT_GREATER,		/* >	*/

	TT_DOT,			/* .	*/
	TT_PIPE,		/* |	*/
	TT_COMMA,		/* ,	*/



	TT_IDENTIFIER,
	TT_KEYWORLD_IF,
	TT_KEYWORLD_ELSE,
	TT_KEYWORLD_FOR,
	TT_KEYWORLD_COUT,
	TT_KEYWORLD_CIN,
	TT_KEYWORLD_RETURN,

	TT_KEYWORLD_INT,
	TT_KEYWORLD_DOUBLE,
	TT_KEYWORLD_STRING,
	TT_KEYWORLD_CHAR,
	TT_KEYWORLD_VOID,


	TT_PAR_L, 		/* ( */
	TT_PAR_R, 		/* ) */
	TT_BRACE_L, 	/* { */
	TT_BRACE_R,		/* { */


	TT_BRACKET_L,	/* [ */
	TT_BRACKET_R,	/* ] */ //o polich nebylo nic receno


	TT_INT,
	TT_DOUBLE,
	TT_STRING,
	TT_CHAR,
	TT_VOID,

	TT_EQUAL_NOT,	/* != */
	TT_EXTRACTION,	/* >>	*/
	TT_INSERTION,	/* <<	*/


/* Zde si budu uchovavat specialni tokeny pro SYN*/
	TT_SPECIAL_DOLLAR,

	TT_SPECIAL_FUNKCE_LS,
	TT_SPECIAL_FUNKCE,
	TT_SPECIAL_FUNKCE_P,
	TT_SPECIAL_STAT_LS,
	TT_SPECIAL_STAT,
	TT_SPECIAL_CIN_LS,
	TT_SPECIAL_COUT_LS,
	TT_SPECIAL_EXP,

	TT_UNRECOGNIZED,
}Typ;

//Function prototypes
tTokenPtr T_Init();
void T_Update(char c);
void T_Destroy(tTokenPtr tokenPtr);
void T_Finish(tTokenPtr tokenPtr);

char * T_GetData();

void T_SystemInit();
void T_SystemTerminate();

extern void T_Get(tTokenPtr tokenPtr);

#endif //T_Header
