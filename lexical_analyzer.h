// NAPSAT KOMENTÁŘE, PROČ TAM NĚCO JE!!!

#ifndef LA_Header
#define LA_Header

tTokenPtr getToken(void);

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
	FM_STAR,
	FM_END,
	FM_COMMENT_SINGLELINE,
	FM_COMMENT_MULTILINE,
	FM_PLUS,
	FM_MINUS,
	FM_DIVIDE,
	FM_KEYWORDS,
	FM_EQUAL,
	FM_SEMICON,
	FM_DOT,
	FM_VARIABLE,
	FM_STRING,
	FM_ESC_SQ,
	FM_ASSIGN,
	FM_GREATER,
	FM_LESS,
	FM_G_EQUAL,
	FM_L_EQUAL,
	FM_NOT_EQUAL,
	FM_PERC,
	FM_COMMA,
	FM_PIPE,
	FM_HASH, 
	FM_DECREMENT,
	FM_INCREMENT
	/*, FM_BOOL_ ... && ||*/
} fm_states;

const static char *key_words = {"auto", "cin", "cout", "double",
	"else", "for", "if", "int", "return", "string" /*,"bool",
	"do", "while", "true", "false"*/}

#endif //LA_Header
