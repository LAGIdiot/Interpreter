#include "str.h"

const size_t stringSizeBase = 8;

string strInit()
{
#if DEBUG
	printf("Creating string container\n");
#endif
	string s = MM_Malloc(sizeof(struct stringStruct));

	s->str = MM_Malloc(sizeof(char)*stringSizeBase);

	s->length = 0;
	s->allocSize = stringSizeBase;
	return s;
}

void strFree(string s)
{
#if DEBUG
	printf("Removing string container\n");
#endif
	MM_Free(s->str);
	MM_Free(s);
}

//Nemusi byt vzdy nejlepsim resenim, zanechava bordel...
void strClear(string s)
{
#if DEBUG
	printf("Clearing content of string container\n");
#endif
   s->str[0] = '\0';
   s->length = 0;
}

//TODO:Test this, may have problems with + 1 sizes
int strInsert(string s, char *text)
{
#if DEBUG
	printf("Inserting content to string container\n");
#endif
  size_t length = strlen(text);

  if(s->length == 0)
  {
	  if(length + 1 > s->allocSize)
		  s->str = MM_Realloc(s->str, sizeof(char) * (length + 1));

	  s->length = length;
	  s->allocSize = length + 1;

	  s->str = text;

	  return 0;
  }
  else
	  return -1; //standartni praktikou je vracet -1 v pripade chyby tohoto typu
}

//TODO: Re-implement this string concatenation (puvodni implementace ponechana v dolni casti souboru)
string concat (string s1, string s2)
{
	return NULL;
}

//TODO: Implement this substring
string substr(string s, int i, int n)
{
	return NULL;
}

//TODO: Implement this string compare
int strCompare(string s1, string s2)
{
	return 0;
}

char *strGetStr(string s)
{
   return s->str;
}

size_t strGetLength(string s)
{
   return s->length;
}

#if jen_vypoznamkovavam_tohle_abych_to_mohl_prelozit
string concat(string s1,string s2)
{
  int amount = s1.length + s2.length; //mnozstvo miesta potrebneho pre s3     problem s pointerom
  string s3;
  if ((s3.str = (char*) malloc(amount)) == NULL ) //allokuje to miesto
  {
	  mistake(ERR_INTERN); //zatim sem davam intern casem vyresit
  }

  s3.str[0] = '\0';         //  nutne
  s3.length = amount;       //  nutne
  s3.allocSize = amount;    //  nutne
  strcat(s3.str,s1.str);   //  concatenuje s1 na s3  problem s pointerom
  strcat(s3.str,s2.str);   //  concatenuje s2 na s3  problem s pointerom

  return *s3;   //problem s pointerom - pokoušíš se vrátit vnitrní promenou
}
#endif
