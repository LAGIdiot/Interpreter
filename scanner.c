#include "scanner.h"

//Function prototypes - private
void T_Get(tTokenPtr tokenPtr);

void Scann(Deque tokenQueue)
{
#if DEBUG
	printf("Starting scanning source code\n");
	int scannedTokens = 0;
#endif
	int scann = 1;

	while(scann)
	{
		tTokenPtr token = T_Init();
		T_Get(token);

		D_PushBack(tokenQueue, token);
#if DEBUG
		printf("%s",tokenNames[token->typ]);
		scannedTokens++;
#endif
		if(token->typ == TT_EOF)
			scann = 0;
	}
#if DEBUG
	printf("Scanning done %d tokens done\n"), scannedTokens;
}

void T_Get(tTokenPtr tokenPtr);
