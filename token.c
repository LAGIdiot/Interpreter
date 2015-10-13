#include <stdlib.h>
#include <string.h>

#include "memory_manager.h"

#include "token.h"

static size_t sizeMax;

tTokenPtr T_Init()
{
	tTokenPtr token = MM_Malloc(sizeof(tTokenStruct));

	sizeMax = 2;

	token->data = MM_Malloc(sizeof(char) * sizeMax);
	token->data[0] = '\0';

	return token;
}

void T_Destroy(tTokenPtr token)
{
	MM_Free(token->data); //pokud by doslo k sahnuti na data v tuto chvili tak by nesedeli
	MM_Free(token);//proto tyto dve volani neposouvat
}

void T_Update(tTokenPtr token, char c)
{
	size_t size = strlen(token->data);
	if(size + 1 == sizeMax)
	{
		sizeMax *= 2;
		token->data = MM_Realloc(token->data, sizeof(char) * sizeMax);
	}

	//token->data = MM_Realloc(token->data, sizeof(char)*(size + 2));

	token->data[(int)size + 1] = c;
	token->data[(int)size + 2] = '\0';
}

void T_Finish(tTokenPtr token)
{
	size_t size = strlen(token->data);
	if(size + 1 != sizeMax)
	{
		token->data = MM_Realloc(token->data, sizeof(char) * (size + 1));
	}
}
