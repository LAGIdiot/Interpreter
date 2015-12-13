///////////////////////////////////////////////////////////////////////////////
/* ---------- IMPLEMENTACE INTERPRETU IMPERATIVNÍHO JAZYKA IFJ15 ----------- */
///////////////////////////////////////////////////////////////////////////////

AUTOŘI:

xbedna57 	ADAM BEDNÁRIK 	()
xmacha63 	ERIK MACHÁČEK 	()
xmalar02 	MARTIN MALÁRIK 	()
xklaci00 	MICHAL KLACIK 	()
xlengu00 	MANH LE NGUYEN 	()

///////////////////////////////////////////////////////////////////////////////

#ifndef ST_Header
#define ST_Header

#include "str.h"
#include "errors.h"
#include "memory_manager.h"
#include "deque.h"

#include "token.h"

enum symbolType{
	ST_VARIABLE,
	ST_FUNCTION,
}symbols;

enum variableType{
	ST_UNDEFINED,

	ST_INT,
	ST_DOUBLE,
	ST_STRING,
	ST_AUTO,
}variables;

typedef struct symbolParamStruct{
	string name;
	int typ;
}*symbolParamPtr;

typedef struct symbolFunctionStruct{
	int returnType;
	int defined;
	int declared;	//prototyp
	Deque params;	//params
	void * symbolTable;	//symbol table pro tuto funkci
}*symbolFunctionPtr;

typedef struct symbolVariableStruct{
	int type;		//variableType
	int defined; 	//defined
	string labelPlatnosti; //label ve kterem nejpozdeji plati dana promena
	void *data;		//pointer to memory
}*symbolVariablePtr;

typedef struct symbolPackegeStruct{
	string key;					// nazev promene .. u nekterych bude potreba generovat
	int typ;		//symbolType
	void * data;	//samotna struktura obsahujici symbol
}*symbolPackagePtr;

symbolPackagePtr ST_PackageCreate(string key, int typ, void * symbol);
void ST_PackageDestroy(symbolPackagePtr symbol);

symbolFunctionPtr ST_FunctionCreate();
void ST_FunctionDestroy(symbolFunctionPtr symbol);

void ST_FunctionAddParam(symbolFunctionPtr symbol, string name, int tokenType);

symbolVariablePtr ST_VariableCreate();
void ST_VariableDestroy(symbolVariablePtr symbol);

void ST_VariableAddData_INT(symbolVariablePtr symbol, int data);
void ST_VariableAddData_DOUBLE(symbolVariablePtr symbol, double data);

string ST_RandomKeyGenerator();

int ST_Compare(symbolPackagePtr symbol1, symbolPackagePtr symbol2);
int ST_CompareFunctions(symbolFunctionPtr symbol1, symbolFunctionPtr symbol2);

int ST_ParamOKV(symbolFunctionPtr symbol, int variableType, int position);
int ST_ParamOKT(symbolFunctionPtr symbol, int tokenType, int position);

int ST_Remap(int tokenTyp);

#endif //ST_Header
