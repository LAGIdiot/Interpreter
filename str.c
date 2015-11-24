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
	string s3;
	s3 = strInit();

	char * pom;
	int dlzka = s1->length + s2->length + 1 ;
	pom = MM_Malloc(sizeof(char*)*dlzka);

	int i = 0;
	for (; i != s1->length; i++ )
		{
			pom[i] = s1->str[i];
		}
	for (int j = 0; j != s2->length; j++ )
		{
			pom[i] = s2->str[j];
			i++;
		}
	if( strInsert(s3, pom) == -1 )
		{
			#if DEBUG
				mistake (ERR_INTERN,"Intern error in substr funcion in str.c after strInsert\n");
			#else
				mistake (ERR_INTERN);
			#endif
		}
	MM_Free(pom);
	return s3;
}

string substr(string s, int i, int n)
{
if ( s->length == i ) //generuj prazdny string
		{
			return  strInit();
		}
if ( s->length < i ) return NULL; //out of range

if ( s->length < i+n )
		{
			char * pom;
			int dlzka = s->length - i + 1 ;
			pom = MM_Malloc(sizeof(char)*dlzka); //alokacia miesta
			for ( int x = 0 ; x != dlzka ; x++ )
				{
					pom[x] = s->str[i+x];		//zapis na pomocnu
				}
			string substr = strInit();
			if( strInsert(substr,pom) == -1 )
			{
				#if DEBUG
					mistake (ERR_INTERN,"Intern error in substr funcion in str.c after strInsert\n");
				#else
					mistake (ERR_INTERN);
				#endif
			}
			MM_Free(pom);
		}
else if ( s->length > i+n )
			{

					char * pom;
					pom = MM_Malloc(sizeof(char)*n); //alokacia miesta
					for ( int x = 0 ; x != n ; x++ )
					{
						pom[x] = s->str[i+x];		//zapis na pomocnu
					}
					string substr = strInit();
					if( strInsert(substr,pom) == -1 )
					{
							#if DEBUG
							mistake (ERR_INTERN,"Intern error in substr funcion in str.c after strInsert\n");
							#else
							mistake (ERR_INTERN);
							#endif
					}
					MM_Free(pom);
			}

return substr;
}

double charToDouble(char * c)
{
	double cislo;
	int chyba;
	chyba = sscanf(c , "%lf", &cislo);
	if (chyba != 1 )
		{
			//pozor na chyby , moze to byt syntakticka , semanticka alebo lexikalne
			#if DEBUG
			mistake (ERR_SEM_OTH,"char to double: EOF, or less/more variables are used\n");
			#else
			mistake (ERR_SEM_OTH);
			#endif
		}
	return cislo;
}

int charToInt(char * c)
{
	int  cislo, chyba;
	chyba = sscanf(c , "%i", &cislo);
	if (chyba != 1 )
		{
			//pozor na chyby , moze to byt syntakticka , semanticka alebo lexikalne
			#if DEBUG
			mistake (ERR_SEM_OTH,"char to double: EOF, or less/more variables are used\n");
			#else
			mistake (ERR_SEM_OTH);
			#endif
		}
	return cislo;
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
string charToStr (char c)
{
	string s;
	s = strInit();
	int i = strInsert(s , &c);
	if ( i != 0 )
	{
		#if DEBUG
		mistake (ERR_INTERN,"\n");
		#else
		mistake (ERR_INTERN);
		#endif
	}
	return s;
}

int *prefix_to_FIND (char *pattern, int psize)
{
	int k = -1;
	int i = 1;
	int * pi = MM_Malloc(sizeof(int)*psize);			// kontrola
	if (!pi)
		return NULL;

	pi[0] = k;
	for (i = 1; i < psize; i++) {
		while (k > -1 && pattern[k+1] != pattern[i])
			k = pi[k];
		if (pattern[i] == pattern[k+1])
			k++;
		pi[i] = k;
	}
	return pi;
}
