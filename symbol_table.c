#include "symbol_table.h"

symbolPackagePtr ST_PackeageCreate(string key, int typ, void * symbol)
{
	symbolPackagePtr symbolPackage = MM_Malloc(sizeof(struct symbolPackegeStruct));

	symbolPackage->key = key;
	symbolPackage->typ = typ;
	symbolPackage->data = symbol;

	return symbolPackage;
}

void ST_PackageDestroy(symbolPackagePtr symbol)
{
	strFree(symbol->key);

	if(ST_FUNCTION)
		ST_FunctionDestroy(symbol->data);
	else
		ST_VariableDestroy(symbol->data);

	MM_Free(symbol);
}

symbolFunctionPtr ST_FunctionCreate()
{
	symbolFunctionPtr function = MM_Malloc(sizeof(struct symbolFunctionStruct));

	function->returnType = ST_UNDEFINED;
	function->paramTypes = NULL;
	function->symbolTable = NULL;
	function->declared = 0;
	function->defined = 0;

	return function;
}

void ST_FunctionDestroy(symbolFunctionPtr symbol)
{
	if(symbol != NULL)
	{
		if(symbol->paramTypes != NULL)
			strFree(symbol->paramTypes );
		if(symbol->symbolTable != NULL)
			deleteTree(symbol->symbolTable);//Potrebuje funkci z IAL

		MM_Free(symbol);
	}
}

void ST_FunctionAddParam(symbolFunctionPtr symbol, int variableType)
{
	if(symbol != NULL)
	{
		if(symbol->paramTypes == NULL)
		{
			string params = strInit();
			symbol->paramTypes = params;
		}

		switch(variableType)
		{
			case ST_INT:
				strConcatChar(symbol->paramTypes, "i");
				break;
			case ST_DOUBLE:
				strConcatChar(symbol->paramTypes, "d");
				break;
			case ST_CHAR:
				strConcatChar(symbol->paramTypes, "d");
				break;
			case ST_STRING:
				strConcatChar(symbol->paramTypes, "d");
				break;
			case ST_AUTO:
				strConcatChar(symbol->paramTypes, "d");
				break;
			default:
				mistake(ERR_INTERN, "Problem with adding param type to function\n");
		}
	}
	else
		mistake(ERR_INTERN, "Someone call ST_FunctionAddParam on uninitialized symbol\n");
}

symbolVariablePtr ST_VariableCreate()
{
	symbolVariablePtr symbol = MM_Malloc(sizeof(struct symbolVariableStruct));

	symbol->data = NULL;
	symbol->defined = 0;
	symbol->type = ST_UNDEFINED;

	return symbol;

}
void ST_VariableDestroy(symbolVariablePtr symbol)
{
	if(symbol->data != NULL)
		MM_Free(symbol->data);
	MM_Free(symbol);
}

string ST_RandomKeyGenerator()
{
	return strRNG(8);
}

//Nemuze dojik k rozdilu v symbol->type !!!
int ST_Compare(symbolPackagePtr symbol1, symbolPackagePtr symbol2)
{
	return strCompare(symbol1->key, symbol2->key);
}
