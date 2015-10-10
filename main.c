#include <stdio.h>

FILE *file_p;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		//CHYBA
	}
	else
	{
		file_p = fopen(*argv[1], "r");
		
		if (file_p == NULL)
		{
			//CHYBA
		}
		else
		{
			syntaxAnalyzer();
		}
	}

	fclose(file_p);
	return 0;
}
