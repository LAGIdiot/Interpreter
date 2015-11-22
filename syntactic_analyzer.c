#include "syntactic_analyzer.h"

void Test_parse()
{
#if DEBUG
	printf("Parsing\n");

	while(1)
	{
		tTokenPtr token = T_Init();

		T_Get(token);

		printf("%d, %s\n",token->typ, token->data);

		if(token->typ == TT_EOF)
		{
			T_Destroy(token);
			break;
		}
		else
			T_Destroy(token);
	}

#endif

	//Inicializace globalni tabulky symbolu
}

void Parse()
{
#if DEBUG
	printf("Parsing\n");
#endif

	Stack stack = S_Init();
	tTokenPtr tokenFirst = NULL;
	tTokenPtr stackTop = NULL;

	//Nahrani prvniho tokenu na stack aby oznacoval konec
	tokenFirst = T_Init();
	tokenFirst->typ = TT_SPECIAL_DOLLARS2;
	T_Finish(tokenFirst);

	S_Push(stack, tokenFirst);

	while(1)
	{
		tTokenPtr tokenLast = T_Init();
		stackTop = S_Top(stack);
		T_Get(tokenLast);

		if(stackTop->typ == TT_SPECIAL_DOLLARS2)
		{
			if(tokenLast->typ == TT_INT || tokenLast->typ == TT_DOUBLE || tokenLast->typ == TT_CHAR || tokenLast->typ == TT_STRING || tokenLast->typ == TT_VOID)
				S_Push(stack, tokenLast);
			else
#if DEBUG
				mistake(ERR_SYN, "There came some strange token after $$\n");
#else
				mistake(ERR_SYN);
#endif
		}

		if(stackTop->typ == TT_INT || stackTop->typ == TT_DOUBLE || stackTop->typ == TT_CHAR || stackTop->typ == TT_STRING || stackTop->typ == TT_VOID)
		{
			if(tokenLast->typ == TT_IDENTIFIER)
			{
				//TODO: Process TT_IDENTIFIER
			}
			else
#if DEBUG
				mistake(ERR_SYN, "Expecting TT_IDENTIFIER, but got something different\n");
#else
				mistake(ERR_SYN);
#endif
		}

//Podminak ukonceni cyklu
		if(tokenLast != NULL && tokenLast->typ == TT_EOF)
		{
			T_Destroy(tokenLast);
			break;
		}

#if DEBUG
		if(tokenLast == NULL)
			mistake(ERR_INTERN, "There was problem with uninitialized token");
#endif


		T_Destroy(tokenLast);
	}

	T_Destroy(tokenFirst);

	S_Terminate(stack);
#if DEBUG
	printf("Parsing done\n");
#endif
}
