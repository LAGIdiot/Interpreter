#ifndef T_Header
#define T_Header

#if DEBUG
typedef struct Token{
	int typ;
	int row;
	int column;
	char *data;
}tTokenStruct, *tTokenPtr;
#else
typedef struct Token{
	int typ;
	char *data;
}tTokenStruct, *tTokenPtr;
#endif

/*Nutno dodefinovat další dle potřeby*/
enum TokenType{
	TT_IDENTIFIER,
	TT_KEYWORD,

	TT_END,

	TT_INT,
	TT_DOUBLE,
	TT_STRING,
	TT_CHAR,

	TT_OP_ADD,
	TT_OP_SUB,
	TT_OP_DIV,
	TT_OP_MUL
}Typ;

//Function prototypes
tTokenPtr T_Init();
void T_Update(tTokenPtr tokenPtr, char nextChar);
void T_Destroy(tTokenPtr tokenPtr);
void T_Finish(tTokenPtr);

extern void T_Get(tTokenPtr tokenPtr);

#endif //T_Header
