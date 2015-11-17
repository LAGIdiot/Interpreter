#ifndef STRING_Header
#define STRING_Header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "memory_manager.h"

typedef struct stringStruct
{
  char* str;		// misto pro dany retezec ukonceny znakem '\0'
  int length;		// skutecna delka retezce
  int allocSize;	// velikost alokovane pameti
} *string;


void strInit(string s);
void strFree(string s);

void strClear(string s);
int strInsert(char *text, string s);
string concat(string s1,string s2);

char *strGetStr(string s);
int strGetLength(string s);

#endif
