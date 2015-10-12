#include <stdlib.h>
#include <string.h>

#include "memory_manager.h"

#include "ial.h"

tTokenPtr T_Init()
{
	tTokenPtr token = MM_Malloc(sizeof(tTokenStruct));

	token->data = MM_Malloc(sizeof(char));
	token->data = '\0';

	return token;
}

void T_Destroy(tTokenPtr token)
{
	MM_Free(token->data); //pokud by doslo k sahnuti na data v tuto chvili tak by nesedeli
	MM_Free(token);//proto tyto dve volani neposouvat
}

void T_Update(tTokenPtr token, char c)
{
	char *temp = token->data;
	size_t size = strlen(token->data);

	token->data = MM_Realloc(token->data, sizeof(char)*(size + 2));

	strcpy(token->data, temp);
	token->data[(int)size + 1] = c;
	token->data[(int)size + 2] = '\0';
}
