// NAPSAT KOMENTÁŘE, PROČ TAM NĚCO JE!!!

#ifndef LA_Header
#define LA_Header

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "token.h"

void T_Get(tTokenPtr tokenPtr);

extern FILE * file_p;

// ASCII hodnoty A-Z, a-z, 0-9
// Zavedení názvů pro znaky pro lepší orientaci
typedef enum
{
	CAPITAL_A = 65,
	CAPITAL_Z = 90,
	LETTER_A = 97,
	LETTER_Z = 122,
	ZERO = 48,
	NINE = 57
} ascii_borders;

// ASCII hodnoty, bílé znaky
// Zavedení názvů pro znaky pro lepší orientaci
typedef enum
{
	NEW_LINE = 10,
	TAB = 9,
	SPACE = 32
} white_chars;

// STAVY KONEČNÉHO AUTOMATU
// Popis stavů konečného automatu, mezi nimiž program přechází
typedef enum
{
	FM_START,
	FM_END,

	FM_SEMICOLN,
	FM_HASH,
	FM_STAR,
	FM_STAR_ASSIGN,
	FM_PLUS,
	FM_PLUS_ASSIGN,
	FM_MINUS,
	FM_MINUS_ASSIGN,
	FM_DIVIDE,
	FM_DIVIDE_ASSIGN,
	FM_ASSIGN,
	FM_EQUAL,

	FM_COMMENT_SINGLELINE,
	FM_COMMENT_MULTILINE,
	FM_COMMENT_MULTILINE_END,

	FM_UNRECOGNIZED,



	FM_KEYWORDS,
	FM_DOT,
	FM_VARIABLE,
	FM_STRING,
	FM_ESC_SQ,
	FM_GREATER,
	FM_LESS,
	FM_G_EQUAL,
	FM_L_EQUAL,
	FM_NOT_EQUAL,
	FM_PERC,
	FM_COMMA,
	FM_PIPE,

	FM_DECREMENT,
	FM_INCREMENT,

	FM_INTEGER,
	FM_DOUBLE,
	FM_DIVISION,
	/*, FM_BOOL_ ... && ||*/
} fm_states;

const static char *key_words[10] = {"auto", "cin", "cout", "double", "else", "for", "if", "int", "return", "string"};
//TODO: /*,"bool","do", "while", "true", "false"*/

#endif //LA_Header
