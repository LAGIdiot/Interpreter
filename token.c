#include "token.h"

//Private variables
static size_t sizeMax;

static char *data;

#if DEBUG
//DEBUG variables
static int tokenCount;
#endif

//////////////////////////////////////////////////
// void T_SystemInit()
////////////////////
// Allocate internal buffer for T_Update
//////////////////////////////////////////////////
void T_SystemInit()
{
#if DEBUG
	tokenCount = 0;
	printf("Token static data buffer allocated\n");
#endif

	sizeMax = 2;

		if(data == NULL)
			data = MM_Malloc(sizeof(char) * sizeMax);
}

//////////////////////////////////////////////////
// void T_SystemTerminate()
////////////////////
// Free internal buffer used by T_Update
//////////////////////////////////////////////////
void T_SystemTerminate()
{
#if DEBUG
	tokenCount = 0;
	printf("Token static data buffer deallocated\n");
#endif
	MM_Free(data);
}

//////////////////////////////////////////////////
// tTokenPtr T_Init()
// return - tTokenPtr pointer
////////////////////
// Let allocate memory for token only, returning token pointer
//////////////////////////////////////////////////
tTokenPtr T_Init()
{
	tTokenPtr token = MM_Malloc(sizeof(struct TokenStruct));

	token->typ = 0;
	token->data = NULL;

#if DEBUG
	printf("Token initialized at: %d \n", token);
	tokenCount++;
#endif

	return token;
}

//////////////////////////////////////////////////
// void T_Destroy(tTokenPtr token)
// token - pointer to token that wants to by destroyed
////////////////////
// Let deallocate memory for token and its data
//////////////////////////////////////////////////
void T_Destroy(tTokenPtr token)
{
	if(token->data != NULL)
		MM_Free(token->data);

	MM_Free(token);

#if DEBUG
	printf("Token destroyed at: %d \n", token);
	tokenCount--;
#endif
}

//////////////////////////////////////////////////
// void T_Update(char c)
// c - char that will be add to token data
////////////////////
// Add char c to static buffer data
//////////////////////////////////////////////////
void T_Update(char c)
{
	size_t size = strlen(data) + 1;// + 1 is for \0

	if(size == sizeMax)
	{
		sizeMax *= 2; //Reallocating is done by 2x size of previous space - therefore there is no need to reallocate for every char
		data = MM_Realloc(data, sizeof(char) * sizeMax);
	}

	strcat(data, &c);
}

//////////////////////////////////////////////////
// void T_Finish(tTokenPtr token)
// token - pointer to token that wants to be finished
////////////////////
// Allocate memory in token for data
//////////////////////////////////////////////////
void T_Finish(tTokenPtr token)
{
	size_t size = strlen(data) + 1;// + 1 is for \0

	token->data = MM_Malloc(sizeof(char)*size);

	memcpy((void*)token->data,data,size);

	strcpy(data,""); //nahradi obsah dat za "" - priprava na dalsi token

#if DEBUG
	printf("Token finished at: %d \n", token);
#endif
}

//////////////////////////////////////////////////
// char * T_GetData()
// return pointer to data that are ready for T_Finish
////////////////////
// Return pointer to data
//////////////////////////////////////////////////
char * T_GetData()
{
	return data;
}
