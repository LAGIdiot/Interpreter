#include "symbol_table.h"

void ST_I_Destroy(symbolItemPtr itemPtr)
{
	MM_Free(itemPtr);
}

symbolItemPtr ST_I_Create(string key, int symbolCode, void * data)
{
	symbolItemPtr item = MM_Malloc(sizeof(symbolItemStruct));

	//TODO: pockat na funkce od Martina

	return item;
}


/* -1 = rozdilny, 0 = stejny, 1 = stejny nazev rozdilny typ (bacha na implementaci auto) */
int ST_I_Compare(symbolItemPtr itemPtr1, symbolItemPtr itemPtr);

