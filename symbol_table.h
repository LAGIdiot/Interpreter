#ifndef ST_Header
#define ST_Header

#include "str.h"
#include "errors.h"
#include "memory_manager.h"

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

typedef struct symbolFunctionStruct{
	int returnType;
	string  paramTypes;
	int defined;
	int declared;	//prototyp
	void * symbolTable;
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
void ST_FunctionAddParam(symbolFunctionPtr symbol, int variableType);

symbolVariablePtr ST_VariableCreate();
void ST_VariableDestroy(symbolVariablePtr symbol);

string ST_RandomKeyGenerator();

int ST_Compare(symbolPackagePtr symbol1, symbolPackagePtr symbol2);

int ST_Remap(int tokenTyp);

#endif //ST_Header
