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
	tTokenPtr token = NULL;

	while(1)
	{


//Podminak ukonceni cyklu
		if(token != NULL && token->typ == TT_EOF)
		{

			break;
		}

#if DEBUG
		if(token == NULL)
			mistake(ERR_INTERN, "There was problem with uninitialized token");
#endif
	}

	S_Terminate(stack);
#if DEBUG
	printf("Parsing done\n");
#endif
}
