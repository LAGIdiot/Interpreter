#include "parser.h"

//Variables static - private
static Deque P_specialStack = NULL;
static Deque P_tokenQueue = NULL;
static nodePtr *P_symbolTable = NULL;

static Deque P_internalCode = NULL;

static tTokenPtr tokenTemp = NULL;
static tTokenPtr tokenLast = NULL;
static tTokenPtr stackTop = NULL;

static Deque P_platnostStack = NULL;

//Function prototypes - private
nodePtr ParseFunctionHead();
void ParseVariable(nodePtr localSymbolTable);
void ParsePrirazeni(nodePtr localSymbolTyble);
void ParseIO(nodePtr localSymbolTable, int keyword, int cin);
void ParseReturn(nodePtr localSymbolTable);

nodePtr ParseExp(nodePtr localSymbolTable, int needReturn);

int LL_TableRule(tTokenPtr lastToken, tTokenPtr stackTop);
string strGenerateLabel(string s1, char * newPart);

void Rule0();

void RozsahPlatnostiAddInner(string inner, int generateLabel);
void RozsahPlatnostiRemoveInner();
string RozsahPlatnostiGet();
void RozsahPlatnostiTerminate();


Deque Parse(Deque tokens, nodePtr *symbolTable)
{
#if DEBUG
	printf("Starting parsing tokens\n");
#endif

	int parsing = 1;
	int rule = 0;

	Deque internCode = AC_Init();
	P_internalCode = internCode;

	P_specialStack = S_Init();

	P_tokenQueue = tokens;

	P_symbolTable = symbolTable;

	nodePtr localSymbolTable = NULL;


	//pushnu si na stak zakoncovaci token
	tTokenPtr tokenFirst = T_Init();
	tokenFirst->typ = TT_S_DOLLAR;
	S_Push(P_specialStack, tokenFirst);


//TODO: Parser automat


	while(parsing)
	{
		//nakopiruju si posledni token a token ze specialu
		stackTop = S_Top(P_specialStack);
		tokenLast = D_TopFront(P_tokenQueue);

		//zajisteni jaky pravidlo se pouzije
		rule = LL_TableRule(tokenLast, stackTop);

		//Odchytavani jeste neimplementovanych ale rozpoznanych tokenu
		if(tokenLast->typ == TT_KEYWORD_DO ||tokenLast->typ == TT_KEYWORD_WHILE || tokenLast->typ == TT_AND ||
			tokenLast->typ == TT_OR ||tokenLast->typ == TT_INCREMENT || tokenLast->typ == TT_DECREMENT ||
			tokenLast->typ == TT_KEYWORD_BOOL || tokenLast->typ == TT_KEYWORD_TRUE || tokenLast->typ == TT_KEYWORD_FALSE)
			mistake(ERR_LEX,"Unimplemented extension\n");


#if DEBUG
		printf("Using rule %d\n",rule);
#endif
		switch(rule)
		{
		case 1:	//Only case that can end parsing without error
			parsing = 0;
			break;
		case 2:
			tokenTemp = T_Init();
			tokenTemp->typ = TT_S_FUNKCE_LS;
			S_Push(P_specialStack, tokenTemp);

			break;
		case 3:
			tokenTemp = T_Init();
			tokenTemp->typ = TT_S_FUNKCE_HEAD_END;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_S_FUNKCE_HEAD;
			S_Push(P_specialStack, tokenTemp);

			break;
		case 4:
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_PAR_R;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_S_FUNKCE_P;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_PAR_L;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_IDENTIFIER;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_S_TYP_UNIVERSAL;
			S_Push(P_specialStack, tokenTemp);

			localSymbolTable = ParseFunctionHead();

			break;
		case 10:
			tokenTemp = T_Init();
			tokenTemp->typ = TT_S_STAT;
			S_Push(P_specialStack, tokenTemp);
			break;
		case 11:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_S_VAR_END;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_IDENTIFIER;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_S_TYP_UNIVERSAL;
			S_Push(P_specialStack, tokenTemp);

			ParseVariable(localSymbolTable);

			break;
		case 14:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SEMICOLON;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_S_EXP;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_ASSIGN;
			S_Push(P_specialStack, tokenTemp);

			ParsePrirazeni(localSymbolTable);

			break;
		case 15:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_S_CIN_LS;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_IDENTIFIER;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_INSERTION;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_KEYWORD_CIN;
			S_Push(P_specialStack, tokenTemp);

			ParseIO(localSymbolTable, 1, 1);
			break;
		case 16:
			tokenTemp = T_Init();
			tokenTemp->typ = TT_IDENTIFIER;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_INSERTION;
			S_Push(P_specialStack, tokenTemp);

			ParseIO(localSymbolTable, 0, 1);
			break;
		case 17:
			//remove CIN_LS
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SEMICOLON;
			S_Push(P_specialStack, tokenTemp);

			break;
		case 18:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_S_COUT_LS;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_IDENTIFIER;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_EXTRACTION;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_KEYWORD_COUT;
			S_Push(P_specialStack, tokenTemp);

			ParseIO(localSymbolTable, 1, 0);
			break;
		case 19:
			//remove COUT_LS
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SEMICOLON;
			S_Push(P_specialStack, tokenTemp);

			break;
		case 20:
			tokenTemp = T_Init();
			tokenTemp->typ = TT_IDENTIFIER;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_EXTRACTION;
			S_Push(P_specialStack, tokenTemp);

			ParseIO(localSymbolTable, 0, 0);
			break;
		case 21:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SEMICOLON;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_S_EXP;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_KEYWORD_RETURN;
			S_Push(P_specialStack, tokenTemp);

			ParseReturn(localSymbolTable);

			break;
		default:
			mistake(ERR_SYN,"No rule for this");
			break;
		}

	}

	T_Destroy(tokenFirst);
	S_Terminate(P_specialStack);

	RozsahPlatnostiTerminate();

	return internCode;

#if DEBUG
	printf("Parsing done intern code was made\n");
#endif
}

//vytvori node z toho co ma k dispozici a na konci porovna jestli uz takovej neni
//return pointer na tabulku symbolu funkce, pokud prototyp tak NULL
nodePtr ParseFunctionHead()
{
	int parsing = 1;
	int rule = 0;
	int parametr = 0;
	int body = 0;

	nodePtr functionNode = NULL;
	symbolFunctionPtr functionSymbol = ST_FunctionCreate();
	symbolPackagePtr packedSymbol = NULL;

	symbolVariablePtr variable = NULL;
	symbolPackagePtr packedVariable = NULL;

	string functionName = NULL;



	int posloupnost = 1; //slouzi k razeni informaci o funkci

	while(parsing)
	{
		//nakopiruju si posledni token a token ze specialu
		stackTop = S_Top(P_specialStack);
		tokenLast = D_TopFront(P_tokenQueue);

		//zajisteni jaky pravidlo se pouzije
		rule = LL_TableRule(tokenLast, stackTop);


		switch(posloupnost)
		{
		case 1: //drzim typ
			functionSymbol->returnType = tokenLast->typ;
			break;
		case 2: //drzim nazev funkce
			functionName = charToStr(tokenLast->data);
			break;
		}

		//pakuje a pridava parametry do funkce
		switch(parametr)
		{
		case 1:
			variable = ST_VariableCreate();
			variable->type = tokenLast->typ;
			variable->defined = 1;
			variable->labelPlatnosti = strGenerateLabel(functionName, NULL);

			ST_FunctionAddParam(functionSymbol,tokenLast->typ);

			parametr++;
			break;
		case 2:
			packedVariable = ST_PackageCreate(charToStr(tokenLast->data), ST_VARIABLE, variable);
			nodeInsert(functionSymbol->symbolTable,packedVariable);
			parametr = 0;
			break;
		}

#if DEBUG
		printf("Using rule %d\n",rule);
#endif
		switch(rule)
		{
			case 0:
				Rule0();
				break;
			case 5:
				tokenTemp = T_Init();
				tokenTemp->typ = TT_IDENTIFIER;
				S_Push(P_specialStack, tokenTemp);

				tokenTemp = T_Init();
				tokenTemp->typ = TT_S_TYP_UNIVERSAL;
				S_Push(P_specialStack, tokenTemp);

				parametr = 1;
				break;
			case 6:
				tokenTemp = S_Pop(P_specialStack);
				T_Destroy(tokenTemp);

				tokenTemp = T_Init();
				tokenTemp->typ = TT_PAR_R;
				S_Push(P_specialStack, tokenTemp);

				break;
			case 7:
				tokenTemp = S_Pop(P_specialStack);
				T_Destroy(tokenTemp);

				tokenTemp = T_Init();
				tokenTemp->typ = TT_SEMICOLON;
				S_Push(P_specialStack, tokenTemp);

				body = 0;
				break;
			case 8:
				tokenTemp = S_Pop(P_specialStack);
				T_Destroy(tokenTemp);

				tokenTemp = T_Init();
				tokenTemp->typ = TT_BRACE_R;
				S_Push(P_specialStack, tokenTemp);

				tokenTemp = T_Init();
				tokenTemp->typ = TT_S_STAT_LS;
				S_Push(P_specialStack, tokenTemp);

				tokenTemp = T_Init();
				tokenTemp->typ = TT_BRACE_L;
				S_Push(P_specialStack, tokenTemp);

				body = 1;

				break;
			case 9:
				tokenTemp = T_Init();
				tokenTemp->typ = TT_COMMA;
				S_Push(P_specialStack, tokenTemp);
				break;
			default:
				mistake(ERR_SYN,"No rule for this");
				break;
		}

		posloupnost++;
	}

	//dokoceni hlavicky funkce

	functionSymbol->declared++;

	packedSymbol = ST_PackageCreate(functionName, ST_FUNCTION, functionSymbol);

	functionNode = searchNodeByKey(P_symbolTable, functionName);

	symbolFunctionPtr functionInTable;

	if(functionNode == NULL)
	{
		nodeInsert(P_symbolTable, packedSymbol);
		functionNode = searchNodeBySymbol(P_symbolTable, packedSymbol);
		functionInTable = functionNode->data->data;
	}
	else
	{
		functionInTable = functionNode->data->data;
		int compare = ST_Compare(functionNode->data, packedSymbol);

		if(compare == 0)
			ST_PackageDestroy(packedSymbol);
		else
			mistake(ERR_SEM_UND, "Redefinition of function prototype \n");
	}

	if(body)
	{
		functionSymbol->defined++;

		//rozliseni levelu platnosti
		RozsahPlatnostiAddInner(functionNode->data->key, 1);

		//LABEL pro skok na funkcy
		AC_itemPtr AC_item = AC_I_Create(AC_LABEL,RozsahPlatnostiGet(), NULL, NULL);
		AC_Add(P_internalCode,AC_item);

		return functionInTable->symbolTable;
	}
	return NULL;

}

void ParseVariable(nodePtr localSymbolTable)
{
	symbolVariablePtr variable = NULL;
	symbolPackagePtr packedVariable = NULL;
	nodePtr node = NULL;

	int rule;

	int expr = 0;

	//vim ze tu budu potrebovat nejmene 4 tahy a to 1.TYP, 2.ID, 3.VAR_END 4. = || ;
	int end = 4;

	for(int i = 0; i < end; i++)
	{
		stackTop = S_Top(P_specialStack);
		tokenLast = D_TopFront(P_tokenQueue);

		//zajisteni jaky pravidlo se pouzije
		rule = LL_TableRule(tokenLast, stackTop);

		if(i == 0)//typ
		{
			if(!(tokenLast->typ == TT_KEYWORD_INT || tokenLast->typ == TT_KEYWORD_DOUBLE || tokenLast->typ == TT_KEYWORD_STRING))
				mistake(ERR_SYN,"Bad token type in parsing variable");

			variable = ST_VariableCreate();
			variable->type = ST_Remap(tokenLast->typ);
		}

		if(i == 1)//id
		{
			if(tokenLast->typ != TT_IDENTIFIER)
				mistake(ERR_SYN,"Bad token type in parsing variable");

			packedVariable = ST_PackageCreate(charToStr(tokenLast->data), ST_VARIABLE, variable);
			node = nodeInsert(&localSymbolTable, packedVariable);
		}

		//i == 2 ->rozebrani VAR_END

		if(i == 3 && expr)
		{
			nodePtr nodeExp = ParseExp(localSymbolTable, 1);

			AC_itemPtr AC_Item = AC_I_Create(AC_OP_ASSIGN,node, nodeExp, node);
			AC_Add(P_internalCode, AC_Item);
		}

		switch(rule)
		{
		case 0:
			Rule0();
			break;
		case 12:
			//remove VAR_END
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SEMICOLON;
			S_Push(P_specialStack, tokenTemp);
			break;
		case 13:
			//remove VAR_END
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SEMICOLON;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_S_EXP;
			S_Push(P_specialStack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_ASSIGN;
			S_Push(P_specialStack, tokenTemp);

			expr = 1;
			end ++;
			break;
		default:
			mistake(ERR_SYN, "No rule for this");
			break;
		}
	}
}

void ParsePrirazeni(nodePtr localSymbolTable)
{
	int rule;

	nodePtr nodeId = NULL;

	//vim ze tu budu potrebovat nejmene 4 tahy a to 1.ID, 2. =, 3. EXP, 4. ;
	int end = 4;
	for(int i = 0; i < 4; i++)
	{
		stackTop = S_Top(P_specialStack);
		tokenLast = D_TopFront(P_tokenQueue);

		//zajisteni jaky pravidlo se pouzije
		rule = LL_TableRule(tokenLast, stackTop);

		if(i == 0)//ID
		{
			nodeId = searchNodeByKey(&localSymbolTable,charToStr(tokenLast->data));
			if(nodeId == NULL)
				mistake(ERR_SEM_UND,"No symbol with this name\n");

		}
		// i == 1 //=
		if(i == 2)// EXP
		{
			nodePtr nodeExp = ParseExp(localSymbolTable, 1);

			AC_itemPtr AC_Item = AC_I_Create(AC_OP_ASSIGN,nodeId, nodeExp, nodeId);
			AC_Add(P_internalCode, AC_Item);
		}
		// i == 3 //;

		switch(rule)
		{
		case 0:
			Rule0();
			break;
		default:
			mistake(ERR_SYN,"No rule for this\n");
			break;
		}
	}
}

void ParseIO(nodePtr localSymbolTable, int keyword, int cin)
{
	int rule;

	nodePtr nodeId = NULL;

	//vim ze tu budu potrebovat nejmene 3 tahy a to 1. CIN, 2. >> 3. ID,
	int end = 3;
	int start = 1;

	if(keyword)
		start = 0;

	for(int i = start; i < end; i++)
	{
		stackTop = S_Top(P_specialStack);
		tokenLast = D_TopFront(P_tokenQueue);

		//zajisteni jaky pravidlo se pouzije
		rule = LL_TableRule(tokenLast, stackTop);

		//i == 0 cin/cout
		//i == 1 <<
		if(i == 2) //ID
		{
			nodeId = searchNodeByKey(&localSymbolTable,charToStr(tokenLast->data));
			if(nodeId == NULL)
				mistake(ERR_SEM_UND,"No symbol with this name\n");

			AC_itemPtr AC_Item = NULL;
			//rozliseni jestli se bude IN or OUT
			if(cin)
				AC_Item = AC_I_Create(AC_CALL_CIN, NULL, NULL, nodeId);
			else
				AC_Item = AC_I_Create(AC_CALL_COUT, nodeId, NULL, NULL);

			AC_Add(P_internalCode, AC_Item);
		}

		switch(rule)
		{
		case 0:
			Rule0();
			break;
		default:
			mistake(ERR_SYN,"No rule for this\n");
			break;
		}
	}
}

void ParseReturn(nodePtr localSymbolTable)
{
	int rule;

	nodePtr nodeId = NULL;

	//TODO: Zamyslet se zda je potreba infromovat funkci o faktu ze jsem nasel jeji return



	//vim ze tu budu potrebovat nejmene 3 tahy a to 1. RETURN, 2. EXP, 3. ;
	int end = 3;

	for(int i = 0; i < end; i++)
	{
		stackTop = S_Top(P_specialStack);
		tokenLast = D_TopFront(P_tokenQueue);

		//zajisteni jaky pravidlo se pouzije
		rule = LL_TableRule(tokenLast, stackTop);

		//i == 0 return
		if(i == 1) //EXP
		{
			nodePtr nodeExp = ParseExp(localSymbolTable, 1);

			AC_itemPtr AC_Item = AC_I_Create(AC_RETURN, nodeExp, NULL, NULL);
			AC_Add(P_internalCode, AC_Item);
		}

		//i == 2 ;

		switch(rule)
		{
		case 0:
			Rule0();
			break;
		default:
			mistake(ERR_SYN,"No rule for this\n");
			break;
		}
	}
}

nodePtr ParseExp(nodePtr localSymbolTable, int needReturn)
{
	//TODO: napsat parsovaci funcki na exp
}

int LL_TableRule(tTokenPtr lastToken, tTokenPtr stackTop)
{
	//Zacnu s -1 aby mapovani odpovidalo papiru
	int row = -1;
	int column= -1;

	switch(stackTop->typ)
	{
	case TT_S_DOLLAR:
		row += 1;
		break;
	case TT_S_FUNKCE_LS:
		row += 2;
		break;
	case TT_S_FUNKCE_HEAD:
		row += 3;
		break;
	case TT_S_FUNKCE_P:
		row += 4;
		break;
	case TT_S_FUNKCE_HEAD_END:
		row += 5;
		break;
	case TT_S_STAT_LS:
		row += 6;
		break;
	case TT_S_STAT:
		row += 7;
		break;
	case TT_S_CIN_LS:
		row +=8;
		break;
	case TT_S_COUT_LS:
		row +=9;
		break;
	}

	switch(lastToken->typ)
	{
	case TT_EOF:
		column += 1;
		break;
	case TT_KEYWORD_IF:
		column += 2;
		break;
	case TT_KEYWORD_ELSE:
		column += 3;
		break;
	case TT_KEYWORD_FOR:
		column += 4;
		break;
	case TT_KEYWORD_RETURN:
		column += 5;
		break;
	case TT_KEYWORD_CIN:
		column += 6;
		break;
	case TT_KEYWORD_COUT:
		column += 7;
		break;
	case TT_BRACE_L:
		column += 8;
		break;
	case TT_BRACE_R:
		column += 9;
		break;
	case TT_PAR_R:
		column += 10;
		break;
	case TT_COMMA:
		column += 11;
		break;
	case TT_SEMICOLON:
		column += 12;
		break;
	case TT_INSERTION:
		column += 13;
		break;
	case TT_EXTRACTION:
		column += 14;
		break;
	case TT_IDENTIFIER:
		column += 15;
		break;
	case TT_S_TYP_UNIVERSAL:
	case TT_KEYWORD_INT:
	case TT_KEYWORD_DOUBLE:
	case TT_KEYWORD_STRING:
		column += 16;
		break;
	case TT_ASSIGN:
		column += 18;
		break;
	default:	//default case for exp
		column += 17;
		break;
	}

	if(row < 0 || row > LL_TABLE_ROWS || column < 0 || column > LL_TABLE_COLUMNS)
		return 0;
	else
		return LL_TABLE[row][column];
}

string strGenerateLabel(string s1, char * newPart)
{
	char *label = "LABEL_";

	string labelPrefix = strInit();
	strInsert(labelPrefix, label);

	string str;

	if(newPart == NULL)
		str = concat(labelPrefix, s1);
	else
		str = concat(s1,charToStr(newPart));

	return str;
}

//Function for removing one piece from stack and one from deque
void Rule0()
{
	int remove = 0;

	if(tokenLast->typ == TT_BRACE_R && stackTop->typ == TT_BRACE_R)
	{
		RozsahPlatnostiRemoveInner();
		remove = 1;
	}
	else if((tokenLast->typ == TT_KEYWORD_INT || tokenLast->typ == TT_KEYWORD_DOUBLE || tokenLast->typ == TT_KEYWORD_STRING) && stackTop->typ == TT_S_TYP_UNIVERSAL)
		remove = 1;
	else if(tokenLast->typ == stackTop->typ)
		remove = 1;
	else
		mistake(ERR_SYN, "Rule 0 got two different token types\n");

	if(remove)
	{
		tokenTemp = S_Pop(P_specialStack);
		T_Destroy(tokenTemp);

		tokenTemp = D_PopFront(P_tokenQueue);
		T_Destroy(tokenTemp);
	}
}

void RozsahPlatnostiAddInner(string inner, int generateLabel)
{
	if(P_platnostStack == NULL)
	{
		P_platnostStack = S_Init();
	}

	if(P_platnostStack->last == NULL)
	{
		if(generateLabel)
			S_Push(P_platnostStack, strGenerateLabel(inner, NULL));
		else
			S_Push(P_platnostStack, inner);
	}
	else
	{
		string outer = S_Top(P_platnostStack);
		string innerComplete = concat(outer, inner);

		S_Push(P_platnostStack, innerComplete);
	}
}

void RozsahPlatnostiRemoveInner()
{
	string temp = S_Pop(P_platnostStack);
	strFree(temp);
}

string RozsahPlatnostiGet()
{
	return S_Top(P_platnostStack);
}

void RozsahPlatnostiTerminate()
{
	while(!S_Empty(P_platnostStack))
	{
		RozsahPlatnostiRemoveInner();
	}

	S_Terminate(P_platnostStack);
	P_platnostStack = NULL;
}
