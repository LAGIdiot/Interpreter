#ifndef PARSER_Header
#define PARSER_Header

#include <stdio.h>

#include "deque.h"
#include "ial.h"
#include "token.h"
#include "errors.h"
#include "address_code.h"
#include "symbol_table.h"
#include "str.h"

#define LL_TABLE_ROWS 10
#define LL_TABLE_COLUMNS 18

const static int LL_TABLE[LL_TABLE_ROWS][LL_TABLE_COLUMNS] =
{/*				EOF,if,	else,	for,return,	cin,cout,	{,	},	),	',',;,	<<,	>>,	id,	typ,exp,=*/
/*$*/			{1,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0},
/*FUNKCE_LS*/	{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	0,	0,	0,	0,	3,	0,	0},
/*FUNKCE_HEAD*/	{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	0,	0,	0,	0,	4,	0,	0},
/*FUNKCE_P*/	{0,	0,	0,		0,	0,		0,	0,		0,	0,	6,	9,	0,	0,	0,	0,	5,	0,	0},
/*FUNKCE_H_END*/{0, 0,	0,		0,	0,		0,	0,		8,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0},
/*STAT_LS*/		{0,	10,	0,		10,	10,		10,	10,		0,	0,	0,	0,	10,	0,	0,	10,	10,	0,	0},
/*STAT*/		{0,	23,	0,		25,	21,		15,	18,		24,	0,	0,	0,	99,	0,	0,	14,	11,	0,	0},
/*VAR_END*/		{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	12,	0,	0,	0,	0,	0,	13},
/*CIN_LS*/		{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	17,	0,	16,	0,	0,	0,	0},
/*COUT_LS*/		{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	19,	20,	0,	0,	0,	0,	0},

};

/*
 *	RULE 1:		End of parsing everything OK
 *	RULE 2:		$ to FUNKCE_LS, $
 *	RULE 3:		FUNKCE_LS		to	FUNCKE_HEAD, FUNKCE_HEAD_END, FUNKCE_LS
 *	RULE 4:		FUNKCE_HEAD		to	TYP_UNIVERSAL, IDENTIFIER, PAR_L, FUNKCE_P, PAR_R,
 *	RULE 5:		FUNCKE_P		to	TYP_UNIVERSAL, IDENTIFIER, FUNKCE_P
 *	RULE 6:		FUNKCE_P		to	PAR_R
 *	RULE 7:		FUNKCE_HEAD_END	to	SEMICOLON
 *	RULE 8:		FUNKCE_HEAD_END	to	{ , STAT_LS, }
 *	RULE 9:		FUNKCE_P		to	COMMA, FUNKCE_P
 *	RULE 10:	STAT_LS			to	STAT, STAT_LS
 *	RULE 11:	STAT			to	TYP_UNIVERSAL, IDENTIFIER, VAR_END
 *	RULE 12:	VAR_END			to	SEMICOLON
 *	RULE 13:	VAR_END			to	ASSIGN, EXP, SEMICOLON
 *	RULE 14:	STAT			to	IDENTIFIER, ASSIGN, EXP, SEMICOLON
 *	RULE 15:	STAT			to	CIN, >>, IDENTIFIER, CIN_LS
 *	RULE 16:	CIN_LS			to	>>, IDENTIFIER, CIN_LS
 *	RULE 17:	CIN_LS			to	SEMICOLON
 *	RULE 18:	STAT			to	COUT, <<, IDENTIFIER, COUT_LS
 *	RULE 19:	COUT_LS			to	SEMICOLON
 *	RULE 20:	COUT_LS			to	<<, IDENTIFIER, COUT_LS
 *	RULE 21:	STAT			to	RETURN, EXP, SEMICOLN
 *	RULE XX:	STAT			to	SEMICOLON
 *	RULE 23:	STAT			to	IF, (, EXP, ), {, STAT_LS, }, ELSE, {, STAT_LS, }
 *	RULE 24:	STAT			to	{, STAT_LS, }
 *	RULE 25:	STAT			to	FOR, (, TYP_UNIVERSAL, IDENTIFIER, ASSIGN, EXP, SEMICOLON, EXP, SEMICOLON, IDENTIFIER, ASSIGN, EXP, ), {, STAT_LS, }
 */

//Functions
Deque Parse(Deque tokens, nodePtr *symboltable);

#endif
