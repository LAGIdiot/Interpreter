#include "str.h"

const size_t stringSizeBase = 8;
const size_t rngSizeBase = 8;

static Deque rngDeque = NULL;

int strRNGSearch(string data);
void strRNGAdd(string data);
void strRNGTerminate();

string strInit()
{
#if DEBUG
	printf("Creating string container\n");
#endif
	string s = MM_Malloc(sizeof(struct stringStruct));

#if DEBUG
	printf("Allocating memory for char array\n");
#endif
	s->str = MM_Malloc(sizeof(char)*stringSizeBase);
	s->str[0] = '\0';

	s->length = 0;
	s->allocSize = stringSizeBase;
	return s;
}

void strFree(string s)
{
#if DEBUG
	printf("Removing string container\n");
#endif
	MM_Free(s->str);	//FIXME: pad pameti
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

int strInsert(string s, char *text)
{
#if DEBUG
	printf("Inserting content to string container\n");
#endif
  size_t length = strlen(text);

  if(s->length == 0)
  {
	  if(length + 1 > s->allocSize)
	  {
		  s->str = MM_Realloc(s->str, sizeof(char) * (length + 1));
		  s->allocSize = length + 1;
	  }

	  s->length = length;

	  strncpy(s->str, text, length);

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
			mistake (ERR_INTERN,"Intern error in substr function in str.c after strInsert\n");
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
string substr = strInit();
if ( s->length < i+n )
		{
			char * pom;
			int dlzka = s->length - i + 1 ;
			pom = MM_Malloc(sizeof(char)*dlzka); //alokacia miesta
			for ( int x = 0 ; x != dlzka ; x++ )
				{
					pom[x] = s->str[i+x];		//zapis na pomocnu
				}
			if( strInsert(substr,pom) == -1 )
				mistake (ERR_INTERN,"Intern error in substr funcion in str.c after strInsert\n");

		}
else if ( s->length > i+n )
			{

					char * pom;
					pom = MM_Malloc(sizeof(char)*n); //alokacia miesta
					for ( int x = 0 ; x != n ; x++ )
					{
						pom[x] = s->str[i+x];		//zapis na pomocnu
					}
					if( strInsert(substr,pom) == -1 )
						mistake (ERR_INTERN,"Intern error in substr funcion in str.c after strInsert\n");

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
		mistake (ERR_SEM_OTH,"char to double: EOF, or less/more variables are used\n");
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
			mistake (ERR_SEM_OTH,"char to double: EOF, or less/more variables are used\n");
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
string charToStr (char *c)
{
	string s;
	s = strInit();
	int i = strInsert(s , c);
	if ( i != 0 )
		mistake (ERR_INTERN,"Problem with casting char to string\n");
	return s;
}

int *prefix_to_FIND (string search)
{
	int k = -1, i = 1, size = search->length;
	int * pi = MM_Malloc(sizeof(int)*size);			// kontrola
	if (!pi)
		return NULL;
	pi[0] = k;
	for (i = 1; i < size; i++) {
		while (k > -1 && search->str[k+1] != search->str[i])
			k = pi[k];
		if (search->str[i] == search->str[k+1])
			k++;
		pi[i] = k;
	}
	return pi;
}

//TODO:Test this! Mozny problem s praci s pointery
void strConcatChar(string s1, char * s2)
{
	string temp = strInit();
	strInsert(temp, s2);

	string final = concat(s1, temp);

	strFree(temp);
	strFree(s1);

	s1 = final;
}

void strRNGInit()
{
	srand(time(NULL));
}

string strRNG()
{
	char rng[rngSizeBase + 1];
	string str = NULL;

	do
	{
		if(str != NULL)
			strFree(str);

		for(int i = 0; i < rngSizeBase; i++)
		{
			rng[i] = (rand() % 26) + 97; //generuje pouze maly pismena
		}

		rng[rngSizeBase +1] = '\0';

		str = charToStr(rng);
	}while(strRNGSearch(str));

	strRNGAdd(str);

	return str;
}

int strRNGSearch(string data)
{
	if(rngDeque != NULL)
	{
		string first = D_PopFront(rngDeque);
		D_PushBack(rngDeque, first);
		string temp = NULL;

		do
		{
			temp = D_PopFront(rngDeque);
			D_PushBack(rngDeque, temp);

			if(temp == data)
				return 1;
		}while(temp != first);
	}

	return 0;
}


void strRNGAdd(string data)
{
	if(rngDeque == NULL)
		rngDeque = D_Init();

	D_PushBack(rngDeque, data);
}

void strRNGTerminate()
{
	while(!D_Empty(rngDeque))
	{
		string temp = D_PopFront(rngDeque);
		strFree(temp);
	}
	D_Terminate(rngDeque);
	rngDeque = NULL;
}
