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


string concat (string s1, string s2)
{

	int amount = s1->length + s2->length;
  string s3;
  if ((s3->str = (char*) malloc(amount)) == NULL )

  s3->str[0] = '\0';
  s3->length = amount;
  s3->allocSize = amount;

  strcat(s3->str,s1->str);
  strcat(s3->str,s2->str);

  return s3;

}

string substr(string s, int i, int n)
{
	if ( s->length == i ) //generuj prazdny string
	{
		// string * substr = strInit();
		return ( strInit() );
	}
	if ( s->length < i ) return NULL;

	string sub = MM_Malloc(sizeof(struct stringStruct));

	if ( s-> length - i > n )
		{
			sub->length = n;
		}
	else

		if ( s-> length - i < n )
			{
				//sub->length = n - (s->length - i);
			}

	sub->allocSize = stringSizeBase;
	sub->str = MM_Malloc(sizeof(char)*sub->length);
	for (int j = 0 ; j < sub->length ; j++)
	{
		sub->str[j] = s->str[i+j];
	}
	return sub;
}


int strCompare(string s1, string s2)
{
	if ( s1->length == s2->length )
	for( int i = 0 ; i < s1->length; i++ )
		{
			if ( s1->str[i] > s2->str[i] ) return -1;
			else if ( s1->str[i] < s2->str[i] ) return 1;
		}
	else if ( s1->length > s2->length) return -1;
			else return 1;
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
