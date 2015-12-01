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

#define LL_TABLE_ROWS 8
#define LL_TABLE_COLUMNS 18

const static int LL_TABLE[LL_TABLE_ROWS][LL_TABLE_COLUMNS] =
{/*				EOF,if,	else,	for,return,	cin,cout,	{,	},	),	',',;,	<<,	>>,	id,	typ,exp,=*/
/*$*/			{1,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0},
/*FUNKCE_LS*/	{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	0,	0,	0,	0,	3,	0,	0},
/*FUNKCE_HEAD*/	{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	0,	0,	0,	0,	4,	0,	0},
/*FUNKCE_P*/	{0,	0,	0,		0,	0,		0,	0,		0,	0,	6,	9,	0,	0,	0,	0,	5,	0,	0},
/*FUNKCE_H_END*/{0, 0,	0,		0,	0,		0,	0,		8,	0,	0,	0,	7,	0,	0,	0,	0,	0,	0},
/*STAT_LS*/		{0,	99,	0,		99,	99,		99,	99,		0,	0,	0,	0,	99,	0,	0,	99,	10,	0,	0},
/*STAT*/		{0,	99,	99,		99,	99,		99,	99,		99,	99,	0,	0,	99,	0,	0,	99,	11,	0,	0},
/*VAR_END*/		{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	12,	0,	0,	0,	0,	0,	13},
#if just_another_unused_code
/*COUT_LS*/		{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	1,	12,	0,	0,	0,	0},
/*CIN_LS*/		{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	1,	0,	13,	0,	0,	0},
/*EXP*/			{0,	0,	0,		0,	0,		0,	0,		0,	0,	1,	0,	1,	0,	0,	0,	0,	19},
#endif
};

/*
 *	RULE 1:		End of parsing everything OK
 *	RULE 2:		$ to FUNKCE_LS, $
 *	RULE 3:		FUNKCE_LS to FUNCKE_HEAD, FUNKCE_HEAD_END, FUNKCE_LS
 *	RULE 4:		FUNKCE_HEAD to TYP_UNIVERSAL, IDENTIFIER, PAR_L, FUNKCE_P, PAR_R,
 *	RULE 5:		FUNCKE_P to TYP_UNIVERSAL, IDENTIFIER, FUNKCE_P
 *	RULE 6:		FUNKCE_P to PAR_R
 *	RULE 7:		FUNKCE_HEAD_END to SEMICOLON
 *	RULE 8:		FUNKCE_HEAD_END to { , STAT_LS, }
 *	RULE 9:		FUNKCE_P to COMMA, FUNKCE_P
 *	RULE 10:	STAT_LS to STAT, STAT_LS
 *	RULE 11:	STAT to TYP_UNIVERSAL, IDENTIFIER, VAR_END
 *	RULE 12:	VAR_END to SEMICOLON
 *	RULE 13:	VAR_END to ASSIGN EXP SEMICOLON
 */

//Functions
Deque Parse(Deque tokens, nodePtr *symboltable);

#endif
