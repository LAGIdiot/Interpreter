///////////////////////////////////////////////////////////////////////////////
/* ---------- IMPLEMENTACE INTERPRETU IMPERATIVNÍHO JAZYKA IFJ15 ----------- */
///////////////////////////////////////////////////////////////////////////////
//
//	AUTOŘI:
//
//	xbedna57 	ADAM BEDNÁRIK 	()
//	xmacha63 	ERIK MACHÁČEK 	()
//	xmalar02 	MARTIN MALÁRIK 	()
//	xklaci00 	MICHAL KLACIK 	()
//	xlengu00 	MANH LE NGUYEN 	()
//
///////////////////////////////////////////////////////////////////////////////

#include "errors.h"

const char *errMessage[11] = {
	"Error : internal mistake of interpreter\n",
	"Error : mistake in lex\n",
	"Error : mistake in syntax\n",
	"Error : undefined function/variable.\n",
	"Error : incompatible types \n",
	"Error : unknown definition of type\n",
	"Error : semantical mistake\n",
	"Error : value wasn't loaded \n",
	"Error : variable wasn't initialized\n",
	"Error : dividing with zero\n",
	"Error : mistake in interpreter\n",
};

//////////////////
// mistake (ErrorCode errCode, const char *message)
// errCode - code number of mistake
// message - pripojena zprava pro jednodusi deteminaci kde k chybe doslo
// ... - dalsi casti message
//////////////////
//funkcia vypise chybovu hlásku zavola funkci na dealokaci pameti a ukončí program
/////////////////
void mistake(int errCode, const char *message, ...)
{
	if(errCode == ERR_INTERN)
		fprintf(stderr, "%s", errMessage[0]);
	else
		fprintf(stderr, "%s", errMessage[(int)errCode]);

#if DEBUG
	va_list va;
	va_start(va, message);

	vfprintf(stderr, message, va);

	va_end(va);

	fprintf(stderr, "\n");

#endif

	MM_Terminate(); //Uklizeni pameti

	exit((int)errCode);
}

