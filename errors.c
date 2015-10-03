#include <stdio.h>
#include <stdlib.h>

//////////////////
// mistake (int param1, param2, param3)
// param1 - code number of mistake
// param2 - line with mistake
// param3 - which letter is start of mistake
//////////////////
//funkcia vypise chybovu hlásku ( zvazit moznost rozsirenia o upresnenie chyby, ako je v 4 uvedene )
/////////////////

void mistake ( int param1, int param2, int param3)
{
  switch (param1)
  {
    case 1:printf("%d:%d : Error : mistake in lex\n",param2,param3 );
    break;

    case 2:printf("%d:%d : Error : syntax and structure is not correct\n",param2,param3 );
    break;

    case 3:printf("%d:%d : Error : undefined function/variable.\n",param2,param3 );
    break;

    case 4:printf("%d:%d : Error : incompatible types \n",param2,param3 );
    break;

    case 5:printf("%d:%d : Error : unknown definition of type\n",param2,param3 );
    break;

    case 6:printf("%d:%d : Error : semantical mistake\n",param2,param3 );
    break;

    case 7:printf("%d:%d : Error : value wasn't loaded \n",param2,param3 );
    break;

    case 8:printf("%d:%d : Error : variable wasn't inicialized\n",param2,param3 );
    break;

    case 9:printf("%d:%d : Error : dividing with zero\n",param2,param3 );
    break;

    case 10:printf("%d:%d : Error : mistake in interpreter\n",param2,param3 );
    break;

    case 99:printf("%d:%d : Error : internal mistake of interpreter\n",param2,param3 );
    break;

    default: printf("%d:%d : Error : unknown mistake\n",param2,param3 );
    break;
  }
}
