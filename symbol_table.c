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

#include "symbol_table.h"

int ST_Remap(int tokenTyp);
void ST_DestroyParams(Deque deque);
int ST_CompareDequeOfParams(Deque params1, Deque params2);
int ST_CompareParams(symbolParamPtr param1, symbolParamPtr param2);

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
	function->declared = 0;
	function->defined = 0;

	function->symbolTable = NULL;
	function->params = NULL;

	return function;
}

void ST_FunctionAddParam(symbolFunctionPtr symbol, string name, int tokenType)
{
	if(symbol == NULL || name == NULL)
		mistake(ERR_INTERN, "Problem with adding function param\n");

	int variableType = ST_Remap(tokenType);
	if(variableType == 0)
		mistake(ERR_SYN, "Bad token type\n");

	symbolParamPtr param = MM_Malloc(sizeof(struct symbolParamStruct));

	param->name = name;
	param->typ = variableType;

	if(symbol->params == NULL)
		symbol->params = D_Init();

	D_PushBack(symbol->params, param);
}

int ST_CompareDequeOfParams(Deque params1, Deque params2)
{
	int params1members = D_MemberCountGet(params1);
	int params2members = D_MemberCountGet(params2);

	if(params1members == -1 && params2members == -1)//nebyly inicializovany
		return 0;
	else if(params1members == 0 && params2members == 0)
		return 0;
	else if(params1members > params2members)
		return -1;
	else if(params1members < params2members)
		return 1;
	else
	{
		D_ActivateFront(params1);
		D_ActivateFront(params2);

		int comp = 0;
		for(int i = 0; i < params1members; i++)
		{
			comp = ST_CompareParams(D_TopActive(params1), D_TopActive(params2));

			if(comp > 0)
				return 1;
			else if(comp < 0)
				return -1;

			D_ActiveMoveToBack(params1);
			D_ActiveMoveToBack(params2);
		}
		return 0;
	}
}

int ST_CompareParams(symbolParamPtr param1, symbolParamPtr param2)
{
	if(param1 == NULL || param2 == NULL)
		mistake(ERR_INTERN, "Nothing to compare");

	if(param1->typ > param2->typ)
		return -1;
	else if(param1->typ < param2->typ)
		return 1;

	int comp = strCompare(param1->name, param2->name);
	if(comp < 0)
		return -1;
	else if(comp > 0)
		return 1;
	else
		return 0;
}

void ST_DestroyParams(Deque deque)
{
	if(deque != NULL)
	{
		symbolParamPtr param = NULL;

		while(!D_Empty(deque))
		{
			param = D_PopFront(deque);

			strFree(param->name);
			MM_Free(param);
		}
		deque = NULL;
	}
}

void ST_FunctionDestroy(symbolFunctionPtr symbol)
{
	if(symbol != NULL)
	{
		if(symbol->params != NULL)
			ST_DestroyParams(symbol->params);
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

symbolVariablePtr ST_VariableCreate()
{
	symbolVariablePtr symbol = MM_Malloc(sizeof(struct symbolVariableStruct));

	symbol->data = NULL;
	symbol->defined = 0;
	symbol->type = ST_UNDEFINED;
	symbol->labelPlatnosti = NULL;

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
	else if(ST_CompareDequeOfParams(symbol1->params, symbol2->params) == 0)
		return 0;
	else
		return 1;
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

int ST_Compare(symbolPackagePtr symbol1, symbolPackagePtr symbol2)
{
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

int ST_ParamOKV(symbolFunctionPtr symbol, int variableType, int position)
{
	int symbolMemberCount = D_MemberCountGet(symbol->params);
	if(symbolMemberCount < position)
		return 0;

	D_ActivateFront(symbol->params);
	for(int i = 1; i < position; i++)
	{
		D_ActiveMoveToBack(symbol->params);
	}

	symbolParamPtr symbolInDeque = D_TopActive(symbol->params);
	if(symbolInDeque->typ != variableType)
		return 0;
	else
		return 1;
}


int ST_ParamOKT(symbolFunctionPtr symbol, int tokenType, int position)
{
	return ST_ParamOKV(symbol, ST_Remap(tokenType), position);
}
