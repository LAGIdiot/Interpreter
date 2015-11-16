#include "syntactic_analyzer.h"

void parse()
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
