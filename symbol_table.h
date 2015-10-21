#ifndef ST_Header
#define ST_Header

#include "str.h"
#include "memory_manager.h"

enum symbolType{
	ST_INT,
	ST_DOUBLE,
	ST_CHAR,
	ST_STRING,
	ST_AUTO,
}symbols;

typedef struct symbolItem{
	string key;					// nazev promene
	int symbol;
	struct symbolItemStruct *nextItem;
}symbolItemStruct, *symbolItemPtr;

#if DEBUG
typedef struct symbolHead{
	struct symbolItemStruct *First;
	int counter;
}symbolHeadStruct, *symbolHeadPtr;
#else
typedef struct symbolHead{
	struct symbolItemStruct *First;
}symbolHeadStruct,*symbolHeadPtr;
#endif

//Function prototypes
symbolHeadPtr ST_T_Create();
void ST_T_Destroy(symbolHeadPtr tablePtr);
void ST_T_Add(symbolItemPtr itemPtr);
void ST_T_Remove(symbolItemPtr itemPtr);

symbolItemPtr ST_I_Create(string key, int symbolCode);
void ST_I_Destroy(symbolItemPtr itemPtr);

#endif //ST_Header
