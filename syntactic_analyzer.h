#ifndef SA_Header
#define SA_Header

#include <stdio.h>

#include "errors.h"
#include "str.h"
#include "symbol_table.h"
#include "token.h"
#include "stack.h"


void Test_parse();

void Parse();

const static int LL_TABLE[9][18] =
{/*				typ,if,	for,{,	},	),	else,	return,	;,	id,	>>,	<<,	exp,',',string,	$,	cin,cout*/
/*$*/			{20,0,	0,	0,	0,	0,	0,		0,		0,	0,	0,	0,	0,	0,	0,		0,	0,	0},
/*FUNKCE_LS*/	{1,	0,	0,	0,	0,	0,	0,		0,		0,	0,	0,	0,	0,	0,	0,		3,	0,	0},
/*FUNKCE*/		{2,	0,	0,	0,	0,	0,	0,		0,		0,	0,	0,	0,	0,	0,	0,		0,	0,	0},
/*FUNKCE_P*/	{4,	0,	0,	0,	0,	5,	0,		0,		0,	0,	0,	0,	0,	21,	0,		0,	0,	0},
/*STAT*/		{0,	6,	7,	8,	0,	0,	14,		9,		10,	11,	0,	0,	0,	0,	0,		0,	12,	13},
/*CIN_LS*/		{0,	0,	0,	0,	0,	0,	0,		0,		31,	0,	30,	0,	0,	0,	0,		0,	0,	0},
/*COUT_LS*/		{0,	0,	0,	0,	0,	0,	0,		0,		33,	0,	0,	32,	0,	0,	0,		0,	0,	0},
/*EXP*/			{0,	0,	0,	0,	0,	16,	0,		0,		16,	0,	0,	0,	15,	0,	19,		0,	0,	0},
/*STAT_LS*/		{0,	22,	23,	0,	29,	0,	0,		24,		25,	26,	27,	28,	0,	0,	0,		29,	0,	0},
};

#endif //SA_Header
