#ifndef INTERPRET_Header
#define INTERPRET_Header

#include <stdio.h>

#include "deque.h"
#include "ial.h"
#include "errors.h"
#include "memory_manager.h"
#include "symbol_table.h"
#include "address_code.h"
#include "str.h" 
/*	Operations - vsechno jsou odkazy do tabulky symbolu (krome LABEL, LABEL_END a vsechny JUMP - zde jde o string v pameti)
 *	AC_OP_ADD,			INT/DOUBLE			INT/DOUBLE 			INT/DOUBLE (vysledek) -- Mam
 *	AC_OP_SUB, 			INT/DOUBLE 			INT/DOUBLE			INT/DOUBLE (vysledek)	-- Mam
 *	AC_OP_MUL,			INT/DOUBLE 			INT/DOUBLE			INT/DOUBLE (vysledek)	-- Mam
 *	AC_OP_DIV,			INT/DOUBLE			INT/DOUBLE			INT/DOUBLE (vysledek) -- Mam
 *
 *	AC_OP_ASSIGN		INT/DOUBLE/STRING		NULL				INT/DOUBLE/STRING (vysledek) --	Mam
 *	AC_LABEL				STRING						NULL				NULL --
 *	AC_LABEL_END		STRING						NULL				NULL --
 * lable pouivaj na jump
 *  AC_JUMP						NULL						NULL				STRING -- oprav
 *	AC_JUMP_C_TRUE		INT/DOUBLE,			NULL				STRING --
 *	AC_JUMP_C_FALSE		INT/DOUBLE,			NULL				STRING --
 *	AC_JUMP_C_FALSE_E	INT/DOUBLE,			NULL				STRING --
 *
 *	Vzdycky pude o to ze source1 je <nazev oprece> source2 a vysledek je typu int (1 pokud pravda, 0 pokud ne)
 *	AC_GREATER				INT/DOUBLE/STRING	INT/DOUBLE/STRING	INT --	Mam
 *	AC_GREATER_EQUAL	INT/DOUBLE/STRING	INT/DOUBLE/STRING	INT --	Mam
 *	AC_LESS						INT/DOUBLE/STRING	INT/DOUBLE/STRING	INT --	Mam
 *	AC_LESS_EQUAL			INT/DOUBLE/STRING	INT/DOUBLE/STRING	INT --	Mam
 *	AC_EQUAL					INT/DOUBLE/STRING	INT/DOUBLE/STRING	INT --	Mam
 *	AC_NOT_EQUAL			INT/DOUBLE/STRING	INT/DOUBLE/STRING	INT --	Mam
 *
 *	AC_CALL_CIN				NULL							NULL				INT/DOUBLE/STRING --
 *	AC_CALL_COUT			INT/DOUBLE/STRING	NULL				NULL --	Mam
 *
 *		int lenght(string s)
 *	AC_CALL_LENGTH		STRING (s)				NULL				INT  -- Mam
 *
 *		string substr(string s, int i, int n)
 *	AC_CALL_DUMMY			INT (n)					NULL					NULL  --
 *	AC_CALL_SUBSTR		STRING (s)			INT (i)				STRING -- Mam
 *
 *		string concat(string s1, string s2)
 *	AC_CALL_CONCAT		STRING (s1)			STRING (s2)			STRING -- Mam
 *
 *		int find(string s, string search)
 *	AC_CALL_FIND			STRING (s1)			STRING (search)		INT -- Mam
 *
 *		string sort(string s)
 *	AC_CALL_SORT			STRING (s)			NULL				STRING -- ++
 *
 *	Casem doplnim dalsi az rozhodnu o jejich implementaci
 *
 */
//Functions
void Interpret(Deque internalCode, nodePtr symboltable);
int searchLABEL();
#endif
