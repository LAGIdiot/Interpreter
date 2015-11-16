#include "token.h"

//Private variables
static size_t sizeMax;

#if DEBUG
//DEBUG variables
static int tokenCount;
#endif

//////////////////////////////////////////////////
// tTokenPtr T_Init()
// return - tTokenPtr pointer
////////////////////
// Let allocate memory for token and its data (data size is 2 and data are: "/0X" - where X is unused char), returning token pointer
//////////////////////////////////////////////////
tTokenPtr T_Init()
{
	tTokenPtr token = MM_Malloc(sizeof(struct TokenStruct));

	sizeMax = 2;

	token->data = MM_Malloc(sizeof(char) * sizeMax);
	token->data[0] = '\0';

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
	/*Token and its data deallocating must be done in this order otherwise there will be memory leak*/
	MM_Free(token->data);
	MM_Free(token);

#if DEBUG
	printf("Token destroyed at: %d \n", token);
	tokenCount--;
#endif
}

//////////////////////////////////////////////////
// void T_Update(tTokenPtr token, char c)
// token - pointer to token that wants data update
// c - char that will be add to token data
////////////////////
// Let allocate memory for data if needed and add char to this data
//////////////////////////////////////////////////
void T_Update(tTokenPtr token, char c)
{
	size_t size = strlen(token->data) + 1;// + 1 is for \0
	if(size == sizeMax) //Check if in data is NO space - reallocating more
	{
		sizeMax *= 2; //Reallocating is done by 2x size of previous space - therefore there is no need to reallocate for every char
		token->data = MM_Realloc(token->data, sizeof(char) * sizeMax);
	}

	/*Adding char c to data and char \0 to the end of data string*/
	token->data[(int)size] = c;
	token->data[(int)size + 1] = '\0';

#if DEBUG
	printf("Token updated at: %d \n", token);
#endif
}

//////////////////////////////////////////////////
// void T_Finish(tTokenPtr token)
// token - pointer to token that wants to be finished
////////////////////
// Let deallocate surplus memory for data if needed
//////////////////////////////////////////////////
void T_Finish(tTokenPtr token)
{
	size_t size = strlen(token->data) + 1;// + 1 is for \0
	if(size != sizeMax)
	{
		token->data = MM_Realloc(token->data, sizeof(char) * size);
	}
#if DEBUG
	printf("Token finished at: %d \n", token);
#endif
}
