// NAPSAT KOMENTÁŘE, PROČ TAM NĚCO JE!!!

#ifndef LA_H
#define LA_H

typedef struct{
	int atribute;
	char *value;
} Ttoken;

// ASCII hodnoty A-Z, a-z, 0-9
typedef enum
{
	CAPITAL_A = 65,
	CAPITAL_Z = 90,
	LETTER_A = 97,
	LETTER_Z = 122,
	ZERO = 48,
	NINE = 57
} ascii_borders;

//ASCII hodnoty, bílé znaky
typedef enum
{
	NEW_LINE = 10,
	TAB = 9,
	SPACE = 32
} white_chars;

//STAVY KONEČNÉHO AUTOMATU
typedef enum
{
	FM_START, FM_STAR, FM_END, FM_COMMENT, FM_PLUS, FM_MINUS, FM_DIVIDE, 
	FM_KEYWORDS, FM_EQUAL, FM_SEMICON, FM_DOT, FM_VARIABLE, FM_STRING, FM_ESC_SQ, 
	FM_ASSIGN, FM_GREATER, FM_LESS, FM_G_EQUAL, FM_L_EQUAL, FM_NOT_EQUAL,
	FM_PERC, FM_COMMA, FM_PIPE, FM_HASH /*,FM_PLUS2, FM_MINUS2, FM_BOOL_ ... && ||*/
} fm_states;

void getToken(Ttoken *token);

#endif
