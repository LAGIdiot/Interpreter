#ifndef STRING_Header
#define STRING_Header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"

typedef struct
{
  char* str;		// misto pro dany retezec ukonceny znakem '\0'
  int length;		// skutecna delka retezce
  int allocSize;	// velikost alokovane pameti
} string;


int strInit(string *s);
void strFree(string *s);

void strClear(string *s);
int strInsert(char *text, string *s);
string concat(string s1,string s2);

char *strGetStr(string *s);
int strGetLength(string *s);

#endif
