#ifndef T_Header
#define T_Header

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "memory_manager.h"

#define KEYWORD_SHIFT 26
#define TOKEN_COUNT 52

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

	TT_SEMICOLON,	/* ;	*/

	TT_STAR,		/* *	*/
	TT_PLUS,		/* +	*/
	TT_MINUS,		/* -	*/
	TT_DIVIDE,		/* /	*/

	TT_ASSIGN,		/* = 	*/
	TT_EQUAL,		/* ==	*/
	TT_EQUAL_LESS,	/* <=	*/
	TT_EQUAL_GREATER,	/* >=	*/
	TT_NOT_EQUAL,	/* !=	*/

	TT_LESS,		/* <	*/
	TT_GREATER,		/* >	*/

	TT_COMMA,		/* ,	*/

	TT_EXTRACTION,	/* >>	*/
	TT_INSERTION,	/* <<	*/

	TT_AND,			/* &&	*/
	TT_OR,			/* ||	*/
	TT_INCREMENT,	/* ++	*/
	TT_DECREMENT,	/* --	*/

	TT_PAR_L, 		/* (	*/
	TT_PAR_R, 		/* )	*/
	TT_BRACE_L, 	/* {	*/
	TT_BRACE_R,		/* {	*/

	TT_IDENTIFIER,

//S timhle dolu se nesmi pohybovat
	TT_KEYWORD_AUTO,
	TT_KEYWORD_CIN,
	TT_KEYWORD_COUT,
	TT_KEYWORD_DOUBLE,
	TT_KEYWORD_ELSE,
	TT_KEYWORD_FOR,
	TT_KEYWORD_IF,
	TT_KEYWORD_INT,
	TT_KEYWORD_RETURN,
	TT_KEYWORD_STRING,
	TT_KEYWORD_BOOL,
	TT_KEYWORD_DO,
	TT_KEYWORD_WHILE,
	TT_KEYWORD_TRUE,
	TT_KEYWORD_FALSE,
	TT_KEYWORD_LENGHT,
	TT_KEYWORD_SUBSTRING,
	TT_KEYWORD_CONCAT,
	TT_KEYWORD_FIND,
	TT_KEYWORD_SORT,
//Konec problemove casti

	TT_INT,
	TT_DOUBLE,
	TT_STRING,

	TT_HEX_NUM,
	TT_OCT_NUM,
	TT_BIN_NUM,

/* Zde si budu uchovavat specialni tokeny pro parser*/
	TT_S_DOLLAR,
	TT_S_FUNKCE_LS,
	TT_S_FUNKCE_HEAD,
	TT_S_FUNKCE_HEAD_END,
	TT_S_FUNKCE_P,
	TT_S_STAT_LS,
	TT_S_STAT,
	TT_S_VAR_END,


	TT_S_EXP,
	TT_S_TYP_UNIVERSAL,


	TT_SPECIAL_CIN_LS,
	TT_SPECIAL_COUT_LS,
}Typ;

//Function prototypes
tTokenPtr T_Init();
void T_Update(char c);
void T_Destroy(tTokenPtr tokenPtr);
void T_Finish(tTokenPtr tokenPtr);

char * T_GetData();

void T_SystemInit();
void T_SystemTerminate();

#if DEBUG
static const char *tokenNames[TOKEN_COUNT] =
	{"UNDEFINED", "EOF", "SEMICOLON", "STAR", "PLUS", "MINUS", "DEVIDE", "ASSIGN", "EQUEAL", "EQUAL_LESS",
		"EQUAL_GREATER","NOT_EQUEAL", "LESS", "GREATER", "COMMA", "EXTRACTION", "INSERTION", "AND", "OR", "INCREMENT",
		"DECREMENT", "PAR_L", "PAR_R", "BRACE_L", "BRACE_R", "IDENTIFIER","AUTO","CIN","COUT","DOUBLE",
		"ELSE", "FOR", "IF", "INT", "RETURN", "STRING", "BOOL", "DO", "WHILE", "TRUE",
		"FALSE", "LENGHT", "SUBSTR", "CONCAT", "FIND", "SORT", "INT_NUM", "DOUBLE_NUM", "STRING", "HEX_NUM",
		"OCT_NUM", "BIN_NUM",
	};
#endif

#endif //T_Header
