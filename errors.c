#include <stdio.h>
#include <stdlib.h>

#include "memory_manager.h"

#include "errors.h"

const char *errMessage[11] = {
	"Error : internal mistake of interpreter\n",
	"Error : mistake in lex\n",
	"Error : undefined function/variable.\n",
	"Error : incompatible types \n",
	"Error : unknown definition of type\n",
	"Error : semantical mistake\n",
	"Error : value wasn't loaded \n",
	"Error : variable wasn't initialized\n",
	"Error : dividing with zero\n",
	"Error : mistake in interpreter\n",
	"Error : mistake in interpreter\n"
};

#if DEBUG
//////////////////
// mistake (ErrorCode errCode, const char *message)
// errCode - code number of mistake
// message - pripojena zprava pro jednodusi deteminaci kde k chybe doslo
//////////////////
//funkcia vypise chybovu hlásku zavola funkci na dealokaci pameti a ukončí program
/////////////////
void mistake(int errCode, const char *message)
{
	if(errCode == ERR_INTERN)
		fprintf(stderr, "%s", errMessage[0]);
	else
		fprintf(stderr, "%s", errMessage[(int)errCode]);

	fprintf(stderr, "%s", message);

	MM_FreeAll(); //Uklizeni pameti

	exit((int)errCode);
}
#else
//////////////////
// mistake (ErrorCode errCode)
// errCode - code number of mistake
//////////////////
//funkcia vypise chybovu hlásku zavola funkci na dealokaci pameti a ukončí program
/////////////////
void mistake(int errCode)
{
	if(errCode == ERR_INTERN)
		fprintf(stderr, "%s", errMessage[0]);
	else
		fprintf(stderr, "%s", errMessage[errCode]);

	MM_FreeAll(); //Uklizeni pameti

	exit(errCode);
}
#endif

