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

#ifndef ERRORS_Header
#define ERRORS_Header

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "memory_manager.h"

enum mistakes {
    ERR_LEX = 1,
    ERR_SYN = 2,
    ERR_SEM_UND = 3,
    ERR_SEM_COMP = 4,
    ERR_SEM_TYP = 5,
    ERR_SEM_OTH = 6,
    ERR_LOAD = 7,
    ERR_INIT = 8,
    ERR_ZERO = 9,
    ERR_RUN_OTH = 10,
    ERR_INTERN = 99
};

void mistake (int errCode, const char *message, ...);

#endif //ERRORS_Header
