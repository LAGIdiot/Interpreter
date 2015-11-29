#ifndef SA_Header
#define SA_Header

#define LL_TABLE_ROWS 9
#define LL_TABLE_COLUMNS 17

#include <stdio.h>

#include "errors.h"
#include "str.h"
#include "symbol_table.h"
#include "token.h"
#include "deque.h"

void Test_parse();

void Parse();

const static int LL_TABLE[LL_TABLE_ROWS][LL_TABLE_COLUMNS] =
{/*				EOF,if,	else,	for,return,	cin,cout,	{,	},	),	',',;,	<<,	>>,	id,	typ,exp*/
/*$*/			{1,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	0,	0,	0,	0,	15,	0},
/*FUNKCE_LS*/	{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	0,	0,	0,	0,	16,	0},
/*FUNKCE*/		{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	0,	0,	0,	0,	17,	0},
/*FUNKCE_P*/	{0,	0,	0,		0,	0,		0,	0,		0,	0,	1,	10,	0,	0,	0,	0,	18,	0},
/*STAT_LS*/		{0,	5,	0,		5,	5,		5,	5,		0,	0,	0,	0,	5,	0,	0,	5,	5,	0},
/*STAT*/		{0,	2,	3,		4,	6,		7,	8,		9,	1,	0,	0,	11,	0,	0,	14,	20,	0},
/*COUT_LS*/		{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	1,	12,	0,	0,	0,	0},
/*CIN_LS*/		{0,	0,	0,		0,	0,		0,	0,		0,	0,	0,	0,	1,	0,	13,	0,	0,	0},
/*EXP*/			{0,	0,	0,		0,	0,		0,	0,		0,	0,	1,	0,	1,	0,	0,	0,	0,	19},
};

#endif //SA_Header
