#include "parser.h"

//Variables static - private
static Deque P_tokenStack = NULL;
static Deque P_tokenQueue = NULL;
static nodePtr P_symbolTable = NULL;

static Deque code = NULL;

//Function prototypes - private
void ParseFunctionHead();
void ParseFunctionBody();

void ParseExp();


Deque Parse(Deque tokens, nodePtr *symbolTable)
{
#if DEBUG
	printf("Starting parsing tokens\n");
#endif

	Deque internCode = D_Init();
	code = internCode;

	Deque stack = S_Init();
	P_tokenStack = stack;

	P_tokenQueue = tokens;

	P_symbolTable = symbolTable;

//TODO: Parser automat



	return internCode;

#if DEBUG
	printf("Parsing done intern code was made\n");
#endif
}

void ParseFunctionHead()
{



	//bude zakoncena bude strednikem -> return to Parse || slozeny zavorky -> ParseFunctionBody
}

void ParseFunctionBody()
{

	//bue zakonceno slozenymi zavorkami
}
