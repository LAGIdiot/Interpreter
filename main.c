#include <stdio.h>

#include "errors.h"
//#include "lexical_analyzer.h"

FILE *file_p;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		//CHYBA
	}
	else
	{
		file_p = fopen(argv[1], "r");
		
		if (file_p == NULL)
		{
			//CHYBA
		}
		else
		{
			//syntaxAnalyzer();
		}
	}

	if(file_p != NULL)
		fclose(file_p);

	return 0;
}
