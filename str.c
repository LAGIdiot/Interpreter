#include "str.h"

/*
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
*/

//FIXME: Tahle funkce by asi mela initializovat cely string ne pouze jeho obsah
//Doporuceni zmenit na: string strInit(); || string strInit(char *str);
void strInit(string s)
{

   if ((s->str = (char*) malloc(8)) == NULL)
      return;
   s->str[0] = '\0';
   s->length = 0;
   s->allocSize = 8;
   return;
}

void strFree(string s)

{
   free(s->str);
}

void strClear(string s)
{
   s->str[0] = '\0';
   s->length = 0;
}

int strInsert(char *text, string s)
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

char *strGetStr(string s)
{
   return s->str;
}

int strGetLength(string s)
{
   return s->length;
}
