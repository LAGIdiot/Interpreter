#include <stdio.h>

#include "errors.h"
#include "memory_manager.h"
#include "scanner.h"
#include "parser.h"
#include "interpret.h"
#include "deque.h"
#include "ial.h"

FILE *file_p;

int main(int argc, char *argv[])
{
#if DEBUG
	printf("I am alive...\nRunning in DEBUG mode...\n");
#endif
	if (argc != 2)
		mistake(ERR_INTERN, "Too few arguments");
	else
	{
#if DEBUG
		printf("Opening file: %s\n", argv[1]);
#endif
		file_p = fopen(argv[1], "r");
		
		if (file_p == NULL)
			mistake(ERR_INTERN, "Unable to open file %s", argv[1]);
		else
		{
			MM_Init(); //Initialize memory manager
			T_SystemInit();

			//Token Queue
			Deque tokenQueue = D_Init();

			Scann(tokenQueue);

			//BT of global symbols
			nodePtr globalSymbolTree;
			treeInit(&globalSymbolTree);

			//Dequeu of intern code
			Deque internCode = Parse(tokenQueue, &globalSymbolTree);


			Interpret(internCode, globalSymbolTree);


//			D_Terminate(tokenQueue);
//			D_Terminate(internCode);
//			deleteTree(globalSymbolTree);


			T_SystemTerminate();

			MM_FreeAll(); //TODO: Vymyslet lepsi provedeni na vymazani pameti po ukonceni programu
		}
	}

	if(file_p != NULL)
		fclose(file_p);

	return 0;
}
