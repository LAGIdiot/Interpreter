#include <stdio.h>

#include "errors.h"
#include "memory_manager.h"
#include "lexical_analyzer.h"

#include "token.h"

FILE *file_p;

/*testovaci funkce na projizdeni lexu */
void test()
{
	while(1)
	{
		tTokenPtr token = T_Init();
		T_Get(token);
		T_Destroy(token);
	}
}

int main(int argc, char *argv[])
{
#if DEBUG
	printf("I am alive...\nRunning in DEBUG mode...\n");
#endif
	if (argc != 2)
	{
#if DEBUG
		mistake(ERR_INTERN, "Too few arguments");
#else
		mistake(ERR_INTERN);
#endif
	}
	else
	{
#if DEBUG
		printf("Opening file: %s\n", argv[1]);
#endif
		file_p = fopen(argv[1], "r");
		
		if (file_p == NULL)
		{
#if DEBUG
			mistake(ERR_INTERN, "Unable to open file %s", argv[1]);
#else
			mistake(ERR_INTERN);
#endif
		}
		else
		{
			MM_Init(); //Initialize memory manager

			test();//prozatimni pro testovani
		}
	}

	if(file_p != NULL)
		fclose(file_p);

	return 0;
}
