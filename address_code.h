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

#ifndef AC_Header
#define AC_Header

#include <stdio.h>
#include "errors.h"
#include "memory_manager.h"
#include "symbol_table.h"
#include "deque.h"

enum operatinType{
	AC_OP_ADD,
	AC_OP_SUB,
	AC_OP_DIV,
	AC_OP_MUL,

	AC_OP_ASSIGN,

	AC_LABEL,
	AC_LABEL_END,	//label konce platnosti - mezi nim a LABEL se stajnym jmenem je platnost symbolu

	AC_JUMP,
	AC_JUMP_C_TRUE,
	AC_JUMP_C_FALSE,
	AC_JUMP_C_FALSE_E,	//skace na label konce platnosti

	AC_GREATER,
	AC_GREATER_EQUAL,
	AC_LESS,
	AC_LESS_EQUAL,
	AC_EQUAL,
	AC_NOT_EQUAL,

	AC_CALL_CIN,
	AC_CALL_COUT,

	AC_CALL_LENGTH,
	AC_CALL_SUBSTR,
	AC_CALL_CONCAT,
	AC_CALL_FIND,
	AC_CALL_SORT,

	AC_CALL_DUMMY,	//slouzi k posilani parametru ktere by se nevesly
	AC_CALL,
	AC_RETURN,
};

/*	Operations - vsechno jsou odkazy do tabulky symbolu (krome LABEL, LABEL_END a vsechny JUMP - zde jde o string v pameti)
 *	AC_OP_ADD,			INT/DOUBLE			INT/DOUBLE 			INT/DOUBLE (vysledek)
 *	AC_OP_SUB, 			INT/DOUBLE 			INT/DOUBLE			INT/DOUBLE (vysledek)
 *	AC_OP_MUL,			INT/DOUBLE 			INT/DOUBLE			INT/DOUBLE (vysledek)
 *	AC_OP_DIV,			INT/DOUBLE			INT/DOUBLE			INT/DOUBLE (vysledek)
 *
 *	AC_OP_ASSIGN		INT/DOUBLE/STRING	NULL				INT/DOUBLE/STRING (vysledek)
 *
 *	AC_LABEL			STRING				NULL				NULL
 *	AC_LABEL_END		STRING				NULL				NULL
 *
 *	AC_JUMP				NULL				NULL				STRING
 *	AC_JUMP_C_TRUE		INT/DOUBLE,			NULL				STRING
 *	AC_JUMP_C_FALSE		INT/DOUBLE,			NULL				STRING
 *	AC_JUMP_C_FALSE_E	INT/DOUBLE,			NULL				STRING
 *
 *	Vzdycky pude o to ze source1 je <nazev oprece> source2 a vysledek je typu int (1 pokud pravda, 0 pokud ne)
 *	AC_GREATER			INT/DOUBLE/STRING	INT/DOUBLE/STRING	INT
 *	AC_GREATER_EQUAL	INT/DOUBLE/STRING	INT/DOUBLE/STRING	INT
 *	AC_LESS				INT/DOUBLE/STRING	INT/DOUBLE/STRING	INT
 *	AC_LESS_EQUAL		INT/DOUBLE/STRING	INT/DOUBLE/STRING	INT
 *	AC_EQUAL			INT/DOUBLE/STRING	INT/DOUBLE/STRING	INT
 *	AC_NOT_EQUAL		INT/DOUBLE/STRING	INT/DOUBLE/STRING	INT
 *
 *	AC_CALL_CIN			NULL				NULL				INT/DOUBLE/STRING
 *	AC_CALL_COUT		INT/DOUBLE/STRING	NULL				NULL
 *
 *	int lenght(string s)
 *	AC_CALL_LENGTH		STRING (s)			NULL				INT
 *
 *	string substr(string s, int i, int n)
 *	AC_CALL_DUMMY		INT (n)				NULL				NULL
 *	AC_CALL_SUBSTR		STRING (s)			INT (i)				STRING
 *
 *	string concat(string s1, string s2)
 *	AC_CALL_CONCAT		STRING (s1)			STRING (s2)			STRING
 *
 *	int find(string s, string search)
 *	AC_CALL_FIND		STRING (s1)			STRING (search)		INT
 *
 *	string sort(string s)
 *	AC_CALL_SORT		STRING (s)			NULL				STRING
 *
 *	Casem doplnim dalsi az rozhodnu o jejich implementaci
 *
 */

typedef struct AC_ItemStruct{
	int operation;
	void *source1;
	void *source2;
	void *destination;
}*AC_itemPtr;

Deque AC_Init();
void AC_Terminate(Deque deque);

void AC_Add(Deque deque, AC_itemPtr item);
AC_itemPtr AC_I_Create(int op, void * source1, void * source2, void * destination);

#endif //AC_Header
