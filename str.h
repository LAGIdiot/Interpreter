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
  size_t length;		// skutecna delka retezce
  size_t allocSize;	// velikost alokovane pameti
} *string;


string strInit();
void strFree(string s);

void strClear(string s);
int strInsert(string s, char *text);
string concat(string s1,string s2);

char *strGetStr(string s);
size_t strGetLength(string s);

int strCompare(string s1, string s2);

#endif
