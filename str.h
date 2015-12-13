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

#ifndef STRING_Header
#define STRING_Header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "errors.h"
#include "memory_manager.h"
#include "deque.h"

typedef struct stringStruct
{
  char* str;		// misto pro dany retezec ukonceny znakem '\0'
  size_t length;		// skutecna delka retezce
  size_t allocSize;	// velikost alokovane pameti
} *string;

///////////
// funkcia *prefix_to_FIND( urobi si tabulku pismen  a nastavi hodnoty, vytvori pamet pre tabulku )
//char *pattern - pattern je hladani vzor , pole
//int psize - dlzka vzoru
///////////
int *prefix_to_FIND (string search);
// lets dooooo dis :D
string charToStr (char *c);
string strInit();
void strFree(string s);
void strClear(string s);
int strInsert(string s, char *text);
char *strGetStr(string s);
double charToDouble(char * c);
int charToInt(char * c);

void strConcatChar(string s1, char * s2);
string strRNG();

//Vestavene funkce - dle zadani
string concat(string s1, string s2);
string substr(string s, int i, int n);
int length(string s);

int strCompare(string s1, string s2);

void strRNGInit();
#endif
