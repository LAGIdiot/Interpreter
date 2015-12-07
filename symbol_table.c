#include "symbol_table.h"

int ST_Remap(int tokenTyp);

symbolPackagePtr ST_PackageCreate(string key, int typ, void * symbol)
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


//Function for maping datat taypes from token to symbolTbale
int ST_Remap(int tokenTyp)
{
	int ret = 0;

	switch(tokenTyp)
	{
		case TT_KEYWORD_INT:
		case TT_INT:
		case TT_BIN_NUM:
		case TT_OCT_NUM:
		case TT_HEX_NUM:
			ret = 1;
			break;
		case TT_KEYWORD_DOUBLE:
		case TT_DOUBLE:
			ret = 2;
			break;
		case TT_KEYWORD_STRING:
		case TT_STRING:
			ret = 3;
			break;
		case TT_KEYWORD_AUTO:
			ret = 4;
			break;
	}
	return ret;
}

void ST_FunctionAddParam(symbolFunctionPtr symbol, int tokenType)
{
	if(symbol != NULL)
	{
		string params = strInit();
		if(symbol->paramTypes == NULL)
			symbol->paramTypes = params;

		int variableType =  ST_Remap(tokenType);

		switch(variableType)
		{
			case ST_INT:
				strConcatChar(symbol->paramTypes, "i");
				break;
			case ST_DOUBLE:
				strConcatChar(symbol->paramTypes, "d");
				break;
			case ST_STRING:
				strConcatChar(symbol->paramTypes, "s");
				break;
			case ST_AUTO:
				strConcatChar(symbol->paramTypes, "a");
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

int ST_CompareFunctions(symbolFunctionPtr symbol1, symbolFunctionPtr symbol2)
{
	if(symbol1->returnType != symbol1->returnType)
		return -1;
	else
		return strCompare(symbol1->paramTypes, symbol2->paramTypes);
}

int ST_CompareVariables(symbolVariablePtr symbol1, symbolVariablePtr symbol2)
{
	if(symbol1->type == symbol2->type)
		return 0;
	else if(symbol1->type == ST_AUTO || symbol1->type == ST_AUTO)
		return 2;
	else
		return -1;
}

//Nemuze dojik k rozdilu v symbol->type !!!
int ST_Compare(symbolPackagePtr symbol1, symbolPackagePtr symbol2)
{
	int compareInner = 0;
	int str = strCompare(symbol1->key, symbol2->key);
	if(str != 0)
		return str;
	else
	{
		if(symbol1->typ == ST_FUNCTION && symbol2->typ == ST_FUNCTION)
			return ST_CompareFunctions(symbol1->data, symbol2->data);
		else if(symbol1->typ == ST_VARIABLE && symbol2->typ == ST_VARIABLE)
			return ST_CompareVariables(symbol1->data, symbol2->data);
		else
			mistake(ERR_SEM_UND, "There was problem with comparing two symbols with different type\n");
			return -2;
	}

	return 0;
}

//TODO: test this 2 functions
void ST_VariableAddData_INT(symbolVariablePtr symbol, int data)
{
	int *intPtr = MM_Malloc(sizeof(int));
	intPtr = &data;
	symbol->data = intPtr;

}
void ST_VariableAddData_DOUBLE(symbolVariablePtr symbol, double data)
{
	double *doublePtr = MM_Malloc(sizeof(double));
	doublePtr = &data;
	symbol->data = doublePtr;
}
