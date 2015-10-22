#ifndef ST_Header
#define ST_Header

#include "str.h"
#include "errors.h"
#include "memory_manager.h"

enum symbolType{
	ST_INT,
	ST_DOUBLE,
	ST_CHAR,
	ST_STRING,
	ST_AUTO,

	ST_FUNCTION,
	ST_JUMP,
}symbols;


/* data obsahuji pointer na data:
 * int double char - data samotny
 * string - struct string obsahuji string
 * function - string s poznamenanym poradim parametru a navratovym typem (pozice 0 = navrat)
 * jump (navesti) - adresa skoku*/
typedef struct symbolItem{
	string key;					// nazev promene
	int symbol;
	int inicializovano;
#if DEBUG
	int used;
#endif
	void * data;
}symbolItemStruct, *symbolItemPtr;

//Function prototypes - vetsina je ulozena v ial.h (ty k binarnimu stromu)
void ST_I_Destroy(symbolItemPtr itemPtr);
symbolItemPtr ST_I_Create(string key, int symbolCode, void  * data);

//TODO: pockat na strCompare od Adama a napsat porovnani
int ST_I_Compare(symbolItemPtr itemPtr1, symbolItemPtr itemPtr);


#endif //ST_Header
