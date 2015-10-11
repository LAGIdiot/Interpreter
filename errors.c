#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

#if DEBUG
//////////////////
// mstk_debug (int param1, param2, param3)
// param1 - code number of mistake
// param2 - line with mistake
// param3 - which letter is start of mistake
//////////////////
//funkcia vypise chybovu hlásku , pouzivat na debug
/////////////////

void mistake_d ( int param1, int param2, int param3)
{
  switch (param1)
  {
    case 1:fprintf(stderr,"%d:%d : Error : mistake in lex\n",param2,param3 );
    break;

    case 2:fprintf(stderr,"%d:%d : Error : syntax and structure is not correct\n",param2,param3 );
    break;

    case 3:fprintf(stderr,"%d:%d : Error : undefined function/variable.\n",param2,param3 );
    break;

    case 4:fprintf(stderr,"%d:%d : Error : incompatible types \n",param2,param3 );
    break;

    case 5:fprintf(stderr,"%d:%d : Error : unknown definition of type\n",param2,param3 );
    break;

    case 6:fprintf(stderr,"%d:%d : Error : semantical mistake\n",param2,param3 );
    break;

    case 7:fprintf(stderr,"%d:%d : Error : value wasn't loaded \n",param2,param3 );
    break;

    case 8:fprintf(stderr,"%d:%d : Error : variable wasn't inicialized\n",param2,param3 );
    break;

    case 9:fprintf(stderr,"%d:%d : Error : dividing with zero\n",param2,param3 );
    break;

    case 10:fprintf(stderr,"%d:%d : Error : mistake in interpreter\n",param2,param3 );
    break;

    default : fprintf(stderr,"%d:%d : Error : internal mistake of interpreter\n",param2,param3 );
    param1 = 99;
    break;

  }
   exit(param1);
}
#endif

//////////////////
// mistake (int param1)
// param1 - code number of mistake
//////////////////
//funkcia vypise chybovu hlásku a ukončí program
//poznamka: ukoncenie bude casom upravene a stane sa samostatnou funkciou
//na ochranu ukoncenia s alokovanou pametou
/////////////////
void mistake (int param1)
{
  switch (param1)
  {
    case 1:fprintf(stderr,"Error 1 : mistake in lex\n");
    break;

    case 2:fprintf(stderr,"Error 2 : syntax and structure is not correct\n");
    break;

    case 3:fprintf(stderr,"Error 3 : undefined function/variable.\n");
    break;

    case 4:fprintf(stderr,"Error 4 : incompatible types \n");
    break;

    case 5:fprintf(stderr,"Error 5 : unknown definition of type\n");
    break;

    case 6:fprintf(stderr,"Error 6 : semantical mistake\n");
    break;

    case 7:fprintf(stderr,"Error 7 : value wasn't loaded \n");
    break;

    case 8:fprintf(stderr,"Error 8 : variable wasn't initialized\n");
    break;

    case 9:fprintf(stderr,"Error 9 : dividing with zero\n");
    break;

    case 10:fprintf(stderr,"Error 10: mistake in interpreter\n");
    break;

    default :fprintf(stderr,"Error 99 : internal mistake of interpreter\n");
    param1 = 99;
    break;

  }
   exit(param1);
}
