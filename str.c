#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "str.h"


int main()
{
  string str1;
  char text[]= "praca";
  strInit(&(str1));
  strInsert(text,&(str1));
  printf("%s \n",str1.str);

  string str2;
  strInit(&(str2));
  strInsert(text,&(str2));
  printf("%s \n",str2.str);

  string str3;
  str3 = concat(*str1,*str2);
  return 0;
}

int strInit(string *s)
{
   if ((s->str = (char*) malloc(8)) == NULL)
      return -1;
   s->str[0] = '\0';
   s->length = 0;
   s->allocSize = 8;
   return 0;
}

void strFree(string *s)

{
   free(s->str);
}

void strClear(string *s)
{
   s->str[0] = '\0';
   s->length = 0;
}

int strInsert(char *text, string *s)
{
  int amount = s->length;
  if (s->str[0] == '\0' )   //ak je prazdna , musi byt
  {
    if (strlen(text) > amount ) //ak je mala , moze nastat
    {
      if((s->str = (char*) realloc(s->str, amount + 1)) != NULL ) //realloc miesta
      {
        s->allocSize = amount + 1; //ulozenie mnozstva
      }
      else return 99;
    }
    //toto sa stane ak je vsetko OK
    s->str=text;
    return 0;
  }
  else return 99;

}

string concat(string s1,string s2)
{
  int amount = s1->length + s2->length; //mnozstvo miesta potrebneho pre s3     problem s pointerom
  string s3;
  if ((s3.str = (char*) malloc(amount)) == NULL ) //allokuje to miesto
    return NULL;
  s3.str[0] = '\0';         //  nutne
  s3.length = amount;       //  nutne
  s3.allocSize = amount;    //  nutne
  strcat(s3.str,s1->str);   //  concatenuje s1 na s3  problem s pointerom
  strcat(s3.str,s2->str);   //  concatenuje s2 na s3  problem s pointerom

  return *s3;   //problem s pointerom
}
char *strGetStr(string *s)
{
   return s->str;
}

int strGetLength(string *s)
{
   return s->length;
}
