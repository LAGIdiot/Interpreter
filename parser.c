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
void ParseIf(nodePtr localSymbolTable);
void ParseFor(nodePtr localSymbolTable);

//rozsireni WHILE
void ParseDoWhile(nodePtr localSymbolTable);
void ParseDoWhilePart2(nodePtr localSymbolTable);
void ParseWhile(nodePtr localSymbolTable);

//Parsovani funkci
nodePtr ParseBuiltinFunction(int function, Deque dequeExp, nodePtr localSymbolTable);
nodePtr ParseUserDefinedFunction(Deque dequeExp, nodePtr localSymbolTable);

nodePtr ParseExp(nodePtr localSymbolTable, int exitSymbolType);
symbolPackagePtr TokenToSymbol(tTokenPtr token);

int LL_TableRule(tTokenPtr lastToken, tTokenPtr stackTop);

void Rule0(nodePtr localSymbolTable);

string RozsahPlatnostiBuildStringFromChars(char * newPart);
string RozsahPlatnostiBuildString(string newPart);
void RozsahPlatnostiAddInner(string inner);
void RozsahPlatnostiRemoveInner();
string RozsahPlatnostiGet();
void RozsahPlatnostiTerminate();
int RozsahPlatnostiLastPart(char * str);

void TokenPusher(Deque stack, int tokensPushed, ...);

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
	TokenPusher(P_specialStack, 1, TT_S_DOLLAR);

	while(parsing)
	{
		//nakopiruju si posledni token a token ze specialu
		stackTop = S_Top(P_specialStack);
		tokenLast = D_TopFront(P_tokenQueue);

		//zajisteni jaky pravidlo se pouzije
		rule = LL_TableRule(tokenLast, stackTop);

		//Odchytavani jeste neimplementovanych ale rozpoznanych tokenu
		if(tokenLast->typ == TT_AND || tokenLast->typ == TT_OR || tokenLast->typ == TT_INCREMENT ||
			tokenLast->typ == TT_DECREMENT || tokenLast->typ == TT_KEYWORD_BOOL || tokenLast->typ == TT_KEYWORD_TRUE ||
			tokenLast->typ == TT_KEYWORD_FALSE)
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
			TokenPusher(P_specialStack, 1, TT_S_FUNKCE_LS);
			break;
		case 3:
			TokenPusher(P_specialStack, 2, TT_S_FUNKCE_HEAD_END, TT_S_FUNKCE_HEAD);
			break;
		case 4:
			//remove FUNKCE_HEAD
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 5, TT_PAR_R, TT_S_FUNKCE_P, TT_PAR_L, TT_IDENTIFIER, TT_S_TYP_UNIVERSAL);

			localSymbolTable = ParseFunctionHead();
			break;
		case 10:
			TokenPusher(P_specialStack, 1, TT_S_STAT);
			break;
		case 11:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 3, TT_S_VAR_END, TT_IDENTIFIER, TT_S_TYP_UNIVERSAL);

			ParseVariable(localSymbolTable);
			break;
		case 14:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 3, TT_SEMICOLON, TT_S_EXP, TT_ASSIGN);

			ParsePrirazeni(localSymbolTable);
			break;
		case 15:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 4, TT_S_CIN_LS, TT_IDENTIFIER, TT_INSERTION, TT_KEYWORD_CIN);

			ParseIO(localSymbolTable, 1, 1);
			break;
		case 16:
			TokenPusher(P_specialStack, 2, TT_IDENTIFIER, TT_INSERTION);

			ParseIO(localSymbolTable, 0, 1);
			break;
		case 17:
			//remove CIN_LS
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 1, TT_SEMICOLON);
			break;
		case 18:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 4, TT_S_COUT_LS, TT_IDENTIFIER, TT_EXTRACTION, TT_KEYWORD_COUT);

			ParseIO(localSymbolTable, 1, 0);
			break;
		case 19:
			//remove COUT_LS
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 1, TT_SEMICOLON);
			break;
		case 20:
			TokenPusher(P_specialStack, 2, TT_IDENTIFIER, TT_EXTRACTION);

			ParseIO(localSymbolTable, 0, 0);
			break;
		case 21:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 3, TT_SEMICOLON, TT_S_EXP, TT_KEYWORD_RETURN);

			ParseReturn(localSymbolTable);
			break;
		case 22:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 1, TT_SEMICOLON);
			break;
		case 23:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 11, TT_BRACE_R, TT_S_STAT_LS, TT_BRACE_L, TT_KEYWORD_ELSE,
				TT_BRACE_R, TT_S_STAT_LS, TT_BRACE_L, TT_PAR_R, TT_S_EXP, TT_PAR_L, TT_KEYWORD_IF);

			ParseIf(localSymbolTable);
			break;
		case 24:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 3, TT_BRACE_R, TT_S_STAT_LS, TT_BRACE_L);

			//posunuti rozsahu platnosti
			RozsahPlatnostiAddInner(RozsahPlatnostiBuildStringFromChars("_BRACE"));

			//label pro novou platnost
			AC_itemPtr AC_Item = AC_I_Create(AC_LABEL,RozsahPlatnostiGet(), NULL, NULL);
			AC_Add(P_internalCode, AC_Item);
			break;
		case 25:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 16, TT_BRACE_R, TT_S_STAT_LS, TT_BRACE_L, TT_PAR_R,
				TT_S_EXP, TT_ASSIGN, TT_IDENTIFIER, TT_SEMICOLON, TT_S_EXP, TT_SEMICOLON,
				TT_S_EXP, TT_ASSIGN, TT_IDENTIFIER, TT_S_TYP_UNIVERSAL, TT_PAR_L, TT_KEYWORD_FOR);

			ParseFor(localSymbolTable);
			break;
		case 26:
			//remove STAT_LS
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);
			break;
		case 27:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 9, TT_SEMICOLON, TT_PAR_R, TT_S_EXP, TT_PAR_L,
					TT_KEYWORD_WHILE, TT_BRACE_R, TT_S_STAT_LS, TT_BRACE_L, TT_KEYWORD_DO);

			ParseDoWhile(localSymbolTable);
			break;
		case 28:
			//remove STAT
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 7, TT_BRACE_R, TT_S_STAT_LS, TT_BRACE_L, TT_PAR_R,
				TT_S_EXP, TT_PAR_L, TT_KEYWORD_WHILE);

			ParseWhile(localSymbolTable);
			break;
		default:
			mistake(ERR_SYN,"No rule for this");
			break;
		}
	}

	tokenTemp = S_Pop(P_specialStack);
	T_Destroy(tokenTemp);
	S_Terminate(P_specialStack);

	RozsahPlatnostiTerminate();

#if DEBUG
	printf("Parsing done intern code was made\n");
#endif

	return internCode;
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
			variable->labelPlatnosti = RozsahPlatnostiBuildString(functionName);

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
				Rule0(NULL); //trochu podvod, ale zde nehrozi riziko ze by parametr byl potreba
				break;
			case 5:
				TokenPusher(P_specialStack, 2, TT_IDENTIFIER, TT_S_TYP_UNIVERSAL);

				parametr = 1;
				break;
			case 6:
				tokenTemp = S_Pop(P_specialStack);
				T_Destroy(tokenTemp);

				TokenPusher(P_specialStack, 1, TT_PAR_R);
				break;
			case 7:
				tokenTemp = S_Pop(P_specialStack);
				T_Destroy(tokenTemp);

				TokenPusher(P_specialStack, 1, TT_SEMICOLON);

				body = 0;
				break;
			case 8:
				tokenTemp = S_Pop(P_specialStack);
				T_Destroy(tokenTemp);

				TokenPusher(P_specialStack, 3, TT_BRACE_R, TT_S_STAT_LS, TT_BRACE_L);

				body = 1;

				break;
			case 9:
				TokenPusher(P_specialStack, 1, TT_COMMA);
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
		RozsahPlatnostiAddInner(RozsahPlatnostiBuildString(functionNode->data->key));

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
			variable->labelPlatnosti = RozsahPlatnostiGet();
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
			nodePtr nodeExp = ParseExp(localSymbolTable, TT_SEMICOLON);

			AC_itemPtr AC_Item = AC_I_Create(AC_OP_ASSIGN,node, nodeExp, node);
			AC_Add(P_internalCode, AC_Item);
		}

		switch(rule)
		{
		case 0:
			Rule0(localSymbolTable);
			break;
		case 12:
			//remove VAR_END
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 1, TT_SEMICOLON);
			break;
		case 13:
			//remove VAR_END
			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);

			TokenPusher(P_specialStack, 3, TT_SEMICOLON, TT_S_EXP, TT_ASSIGN);

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
	for(int i = 0; i < end; i++)
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
			nodePtr nodeExp = ParseExp(localSymbolTable, TT_SEMICOLON);

			AC_itemPtr AC_Item = AC_I_Create(AC_OP_ASSIGN, nodeId, nodeExp, nodeId);
			AC_Add(P_internalCode, AC_Item);
		}
		// i == 3 //;

		switch(rule)
		{
		case 0:
			Rule0(localSymbolTable);
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
			Rule0(localSymbolTable);
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

	//vim ze tu budu potrebovat nejmene 3 tahy a to 1. RETURN, 2. EXP, 3. ;
	int end = 3;

	for(int i = 0; i < end; i++)
	{
		stackTop = S_Top(P_specialStack);
		tokenLast = D_TopFront(P_tokenQueue);

		//zajisteni jaky pravidlo se pouzije
		rule = LL_TableRule(tokenLast, stackTop);

		if(i == 1) //EXP
		{
			nodePtr nodeExp = ParseExp(localSymbolTable, TT_SEMICOLON);

			AC_itemPtr AC_Item = AC_I_Create(AC_RETURN, nodeExp, NULL, NULL);
			AC_Add(P_internalCode, AC_Item);
		}

		switch(rule)
		{
		case 0:
			Rule0(localSymbolTable);
			break;
		default:
			mistake(ERR_SYN,"No rule for this\n");
			break;
		}
	}
}

void ParseIf(nodePtr localSymbolTable)
{
	int rule;

	//vim ze tu budu potrebovat nejmene 3 tahy a to 1. IF, 2. (, 3. EXP
	int end = 3;

	for(int i = 0; i < end; i++)
	{
		stackTop = S_Top(P_specialStack);
		tokenLast = D_TopFront(P_tokenQueue);

		//zajisteni jaky pravidlo se pouzije
		rule = LL_TableRule(tokenLast, stackTop);

		if(i == 0)
		{
			RozsahPlatnostiAddInner(RozsahPlatnostiBuildStringFromChars("_IF"));
			AC_itemPtr AC_Item = AC_I_Create(AC_LABEL, RozsahPlatnostiGet(), NULL, NULL);
			AC_Add(P_internalCode, AC_Item);
		}

		if(i == 3)
		{
			nodePtr nodeExp = ParseExp(localSymbolTable, TT_PAR_R);

			AC_itemPtr AC_Item = AC_I_Create(AC_JUMP_C_FALSE, nodeExp, NULL, RozsahPlatnostiBuildStringFromChars("_ELSE"));
			AC_Add(P_internalCode, AC_Item);
		}

		switch(rule)
		{
		case 0:
			Rule0(localSymbolTable);
			break;
		default:
			mistake(ERR_SYN,"No rule for this\n");
			break;
		}
	}
}

void ParseFor(nodePtr localSymbolTable)
{
	int rule;
	nodePtr node = NULL;
	symbolVariablePtr variable = NULL;
	symbolPackagePtr packedVariable = NULL;

	AC_itemPtr AC_Item = NULL;


	int end = 13;

	for(int i = 0; i < end; i++)
	{
		stackTop = S_Top(P_specialStack);
		tokenLast = D_TopFront(P_tokenQueue);

		//zajisteni jaky pravidlo se pouzije
		rule = LL_TableRule(tokenLast, stackTop);

		if(i == 2)
		{
			if(!(tokenLast->typ == TT_KEYWORD_INT || tokenLast->typ == TT_KEYWORD_DOUBLE || tokenLast->typ == TT_KEYWORD_STRING))
				mistake(ERR_SYN,"Bad token type in parsing variable");

			//label for FOR - must be there because of rozsah platnosti
			RozsahPlatnostiAddInner(RozsahPlatnostiBuildStringFromChars("_FOR"));

			variable = ST_VariableCreate();
			variable->type = ST_Remap(tokenLast->typ);
			variable->labelPlatnosti = RozsahPlatnostiGet();

			AC_Item = AC_I_Create(AC_LABEL,RozsahPlatnostiGet(), NULL, NULL);
			AC_Add(P_internalCode, AC_Item);
		}

		if(i == 3)
		{
			if(tokenLast->typ != TT_IDENTIFIER)
				mistake(ERR_SYN,"Bad token type in parsing variable");

			packedVariable = ST_PackageCreate(charToStr(tokenLast->data), ST_VARIABLE, variable);
			node = nodeInsert(&localSymbolTable, packedVariable);
		}

		if(i == 5)
		{
			nodePtr nodeExp = ParseExp(localSymbolTable, TT_SEMICOLON);

			AC_Item = AC_I_Create(AC_OP_ASSIGN,node, nodeExp, node);
			AC_Add(P_internalCode, AC_Item);
		}


		if(i == 7)
		{
			AC_Item = AC_I_Create(AC_LABEL, RozsahPlatnostiBuildStringFromChars("_CONDITION"),NULL,NULL);
			AC_Add(P_internalCode, AC_Item);

			nodePtr nodeExp = ParseExp(localSymbolTable, TT_SEMICOLON);

			AC_Item = AC_I_Create(AC_JUMP_C_TRUE, nodeExp, NULL, RozsahPlatnostiBuildStringFromChars("_BODY"));
			AC_Add(P_internalCode, AC_Item);

			AC_Item = AC_I_Create(AC_JUMP_C_FALSE_E, nodeExp, NULL, RozsahPlatnostiGet());
			AC_Add(P_internalCode, AC_Item);
		}

		if(i == 9)
		{
			AC_Item = AC_I_Create(AC_LABEL, RozsahPlatnostiBuildStringFromChars("_MODIFICATION"),NULL,NULL);
			AC_Add(P_internalCode, AC_Item);

			node = searchNodeByKey(&localSymbolTable,charToStr(tokenLast->data));
			if(node == NULL)
				mistake(ERR_SEM_UND,"No symbol with this name\n");
		}

		if(i == 11)
		{
			nodePtr nodeExp = ParseExp(localSymbolTable, TT_PAR_R);

			AC_Item = AC_I_Create(AC_OP_ASSIGN,nodeExp, NULL, node);
			AC_Add(P_internalCode, AC_Item);

			AC_Item = AC_I_Create(AC_JUMP, NULL, NULL, RozsahPlatnostiBuildStringFromChars("_CONDITION"));
			AC_Add(P_internalCode, AC_Item);

			AC_Item = AC_I_Create(AC_LABEL, RozsahPlatnostiBuildStringFromChars("_BODY"), NULL, NULL);
			AC_Add(P_internalCode, AC_Item);
		}

		switch(rule)
		{
		case 0:
			Rule0(localSymbolTable);
			break;
		default:
			mistake(ERR_SYN,"No rule for this\n");
			break;
		}
	}
}

//////////////////////////////////////////////////
// nodePtr ParseExp(nodePtr localSymbolTable, int exitSymbolType)
// return nodePtr - pointer to node in local symbol tree
// localSymbolTable
// exitSymbolType - symbol that is expected after EXP
////////////////////
// Returning nodePtr to last/top/left symbol
//////////////////////////////////////////////////
nodePtr ParseExp(nodePtr localSymbolTable, int exitSymbolType)
{
	nodePtr nodeLastProcessed = NULL;
	nodePtr nodeFunction = NULL;

	nodePtr nodeFirst = NULL;
	nodePtr nodeSecond = NULL;

	Deque deque = D_Init();

	AC_itemPtr AC_Item = NULL;
	symbolPackagePtr symbolPackage = NULL;
	symbolVariablePtr symbolVariable = NULL;

	int tokenCount = 0;
	int endPAR = 0;

	int PAR_L_Count = 0;
	int PAR_R_Count = 0;

	int expectingFunction = 0;

	if(exitSymbolType == TT_PAR_R)
		endPAR = 1;

	//preliti tokenu
	while(1)
	{
		tokenLast = D_TopFront(P_tokenQueue);

		if(tokenLast->typ == TT_PAR_R && endPAR &&  PAR_L_Count == PAR_R_Count) //ukoncovani pro exitSymbol PAR_R
			break;

		if(tokenLast->typ == exitSymbolType)
			break;

		if(tokenLast->typ == TT_PAR_L)
			PAR_L_Count++;

		if(tokenLast->typ == TT_PAR_R)
			PAR_R_Count++;

		D_PushBack(deque,D_PopFront(P_tokenQueue));
		tokenCount++;
	}

	tokenTemp = D_TopFront(deque);

	//if ohnuti zadani jako krava

	if(tokenTemp->typ == TT_KEYWORD_CONCAT || tokenTemp->typ == TT_KEYWORD_FIND || tokenTemp->typ == TT_KEYWORD_SUBSTRING || tokenTemp->typ == TT_KEYWORD_LENGTH)
		expectingFunction = 2;
	else if(tokenTemp->typ == TT_IDENTIFIER)
	{
		nodeFunction = searchNodeByKey(P_symbolTable, charToStr(tokenTemp->data));
		if(nodeFunction != NULL)
			expectingFunction = 1;
	}

	if(tokenCount == 1)
	{
		if(tokenTemp->typ == TT_IDENTIFIER)
		{
			nodeLastProcessed = searchNodeByKey(&localSymbolTable, charToStr(tokenTemp->data));

			//zabiti tokenu
			tokenTemp = D_PopFront(deque);
			T_Destroy(tokenTemp);

			if(nodeLastProcessed == NULL)
				mistake(ERR_SEM_UND, "Problem with only argument in EXP\n");
		}
		else
		{
			symbolPackage = TokenToSymbol(tokenTemp);

			//zabiti tokenu
			tokenTemp = D_PopFront(deque);
			T_Destroy(tokenTemp);

			if(symbolPackage == NULL)
				mistake(ERR_SYN, "Problem with only argument in EXP\n");

			nodeLastProcessed = nodeInsert(&localSymbolTable, symbolPackage);
		}
	}
	else if(tokenCount == 3)
	{
		//prvni ID/cislo
		if(tokenTemp->typ == TT_IDENTIFIER)
		{
			nodeFirst = searchNodeByKey(&localSymbolTable, charToStr(tokenTemp->data));

			//zabiti tokenu
			tokenTemp = D_PopFront(deque);
			T_Destroy(tokenTemp);

			if(nodeFirst == NULL)
				mistake(ERR_SEM_UND, "Problem with only argument in EXP\n");
		}
		else
		{
			symbolPackage = TokenToSymbol(tokenTemp);

			//zabiti tokenu
			tokenTemp = D_PopFront(deque);
			T_Destroy(tokenTemp);

			if(symbolPackage == NULL)
				mistake(ERR_SYN, "Problem with only argument in EXP\n");

			nodeFirst = nodeInsert(&localSymbolTable, symbolPackage);
		}

		//operace pro pocitani
		tokenTemp = D_TopFront(deque);
		int AC_Operation = 0;

		switch(tokenTemp->typ)
		{
		case TT_PLUS:
			AC_Operation = AC_OP_ADD;
			break;
		case TT_MINUS:
			AC_Operation = AC_OP_SUB;
			break;
		case TT_STAR:
			AC_Operation = AC_OP_MUL;
			break;
		case TT_DIVIDE:
			AC_Operation = AC_OP_DIV;
			break;

		case TT_EQUAL:
			AC_Operation = AC_EQUAL;
			break;
		case TT_NOT_EQUAL:
			AC_Operation = AC_NOT_EQUAL;
			break;
		case TT_GREATER:
			AC_Operation = AC_GREATER;
			break;
		case TT_EQUAL_GREATER:
			AC_Operation = AC_GREATER_EQUAL;
			break;
		case TT_LESS:
			AC_Operation = AC_LESS;
			break;
		case TT_EQUAL_LESS:
			AC_Operation = AC_LESS_EQUAL;
			break;
		default:
			mistake(ERR_SYN, "Problem with sign\n");
			break;
		}

		//zabiti tokenu
		tokenTemp = D_PopFront(deque);
		T_Destroy(tokenTemp);


		tokenTemp = D_TopFront(deque);
		//druhy ID/cislo
		if(tokenTemp->typ == TT_IDENTIFIER)
		{
			nodeFirst = searchNodeByKey(&localSymbolTable, charToStr(tokenTemp->data));

			//zabiti tokenu
			tokenTemp = D_PopFront(deque);
			T_Destroy(tokenTemp);

			if(nodeFirst == NULL)
				mistake(ERR_SEM_UND, "Problem with only argument in EXP\n");
		}
		else
		{
			symbolPackage = TokenToSymbol(tokenTemp);

			//zabiti tokenu
			tokenTemp = D_PopFront(deque);
			T_Destroy(tokenTemp);

			if(symbolPackage == NULL)
				mistake(ERR_SYN, "Problem with only argument in EXP\n");

			nodeFirst = nodeInsert(&localSymbolTable, symbolPackage);
		}

		//AC a operace a navrat
		symbolVariable = ST_VariableCreate();
		symbolVariable->defined = 1;
		symbolVariable->labelPlatnosti = RozsahPlatnostiGet();
		symbolVariable->type = ST_AUTO;
		symbolVariable->data = NULL;

		symbolPackage = ST_PackageCreate(ST_RandomKeyGenerator(), ST_VARIABLE, symbolVariable);

		nodeLastProcessed = nodeInsert(&localSymbolTable, symbolPackage);

		AC_Item = AC_I_Create(AC_Operation, nodeFirst, nodeSecond, nodeLastProcessed);
	}
	else
	{
		//funkce
		if(expectingFunction == 1)
			nodeLastProcessed = ParseUserDefinedFunction(deque, localSymbolTable);
		else if(expectingFunction == 2)
		{
			if(tokenTemp->typ == TT_KEYWORD_LENGTH)
			{
				TokenPusher(P_specialStack, 4, TT_PAR_R, TT_IDENTIFIER, TT_PAR_L, TT_KEYWORD_LENGTH);

				nodeLastProcessed = ParseBuiltinFunction(BF_LENGTH, deque, localSymbolTable);
			}
			else if(tokenTemp->typ == TT_KEYWORD_SUBSTRING)
			{
				TokenPusher(P_specialStack, 8, TT_PAR_R, TT_IDENTIFIER, TT_COMMA, TT_IDENTIFIER,
					TT_COMMA, TT_IDENTIFIER, TT_PAR_L, TT_KEYWORD_SUBSTRING);

				nodeLastProcessed = ParseBuiltinFunction(BF_SUBSTR, deque, localSymbolTable);
			}
			else if(tokenLast->typ == TT_KEYWORD_CONCAT)
			{
				TokenPusher(P_specialStack, 6, TT_PAR_R, TT_IDENTIFIER, TT_COMMA, TT_IDENTIFIER, TT_PAR_L, TT_KEYWORD_CONCAT);

				nodeLastProcessed = ParseBuiltinFunction(BF_CONCAT, deque, localSymbolTable);
			}
			else if(tokenLast->typ == TT_KEYWORD_FIND)
			{
				TokenPusher(P_specialStack, 6, TT_PAR_R, TT_IDENTIFIER, TT_COMMA, TT_IDENTIFIER, TT_PAR_L, TT_KEYWORD_FIND);

				nodeLastProcessed = ParseBuiltinFunction(BF_FIND, deque, localSymbolTable);
			}
			else if(tokenLast->typ == TT_KEYWORD_SORT)
			{
				TokenPusher(P_specialStack, 4, TT_PAR_R, TT_IDENTIFIER, TT_PAR_L, TT_KEYWORD_SORT);

				nodeLastProcessed = ParseBuiltinFunction(BF_SORT, deque, localSymbolTable);
			}
			else
				mistake(ERR_INTERN, "Unrecognized built-in function\n");
		}
		else
			mistake(ERR_SYN, "Unrecognized token in EXP\n");
	}
	//odeber EXP ze stacku
	tokenTemp = S_Pop(P_specialStack);
	T_Destroy(tokenTemp);

	return nodeLastProcessed;
}

nodePtr ParseUserDefinedFunction(Deque dequeExp, nodePtr localSymbolTable)
{
	//Battle plan:	get functionSymbol and list of its parametrs -> expecting number of parametrs
	//				take the deque from end, found PAR_R and take arguments from end and put them to AC_CALL_DUMMYs and AC_CALL

	symbolFunctionPtr function = NULL;
	symbolVariablePtr variable = NULL;
	symbolPackagePtr package = NULL;

	nodePtr nodeFunction = NULL;
	nodePtr nodeFirst = NULL;
	nodePtr nodeSecond = NULL;
	nodePtr nodeRet = NULL;

	AC_itemPtr AC_Item = NULL;

	int numberOfArguments = 0;
	int tokenCount = 0;

	tokenTemp = D_TopFront(dequeExp);

	nodeFunction = searchNodeByKey(P_symbolTable, charToStr(tokenTemp->data));
	if(nodeFunction == NULL)
		mistake(ERR_SEM_UND, "User defined function not found\n");

	function = nodeFunction->data->data;

	if(function->defined != 1)
		mistake(ERR_SEM_UND, "Definition of user defined function not found\n");

	numberOfArguments = function->paramTypes->length;

	Deque stack = S_Init();

	//preliti tokenu
	while(1)
	{
		tokenLast = D_TopFront(dequeExp);

		S_Push(stack,D_PopFront(P_tokenQueue));
		tokenCount++;

		if(tokenLast->typ == TT_PAR_R) //ukoncovani pro PAR_R
			break;
	}

	for(int i = 0; i < tokenCount; i++)
	{
		tokenTemp = D_TopFront(dequeExp);

		if ((i % 2) == 1) //jede se po lichych protoze na 0 je PAR_R
		{
			if((numberOfArguments % 2) == 1)	//uklada se na adress 1 - zde taky dochazi k volani funcke dummy
			{
				if(tokenTemp->typ == TT_IDENTIFIER)
				{
					nodeFirst = searchNodeByKey(&localSymbolTable, charToStr(tokenTemp->data));
					if(nodeFirst == NULL)
						mistake(ERR_SEM_UND, "This identifier is not registered in symbol table \n");

					variable = nodeFirst->data->data;
					if(ST_CompareParamS(function, variable->type, numberOfArguments) != 0)
						mistake(ERR_SEM_COMP, "Bad token type\n");
				}
				else if(ST_CompareParamT(function, tokenTemp->typ, numberOfArguments) == 0)
					nodeFirst = nodeInsert(&localSymbolTable, TokenToSymbol(tokenTemp));
				else
					mistake(ERR_SEM_COMP, "Bad token type\n");

				if(numberOfArguments > 2)	//volani funkce dummy - volani funkce je az za cyklem
				{
					AC_Item = AC_I_Create(AC_CALL_DUMMY, nodeFirst, nodeSecond, NULL);
					AC_Add(P_internalCode, AC_Item);
				}

			}
			else	//uklda se na adress 2
			{
				if(tokenTemp->typ == TT_IDENTIFIER)
				{
					nodeSecond = searchNodeByKey(&localSymbolTable, charToStr(tokenTemp->data));
					if(nodeSecond == NULL)
						mistake(ERR_SEM_UND, "This identifier is not registered in symbol table \n");

					variable = nodeSecond->data->data;
					if(ST_CompareParamS(function, variable->type, numberOfArguments) != 0)
						mistake(ERR_SEM_COMP, "Bad token type\n");
				}
				else if(ST_CompareParamT(function, tokenTemp->typ, numberOfArguments) == 0)
					nodeSecond = nodeInsert(&localSymbolTable, TokenToSymbol(tokenTemp));
				else
					mistake(ERR_SEM_COMP, "Bad token type\n");
			}
		}

		if(tokenTemp->typ == stackTop->typ)
		{
			tokenTemp = D_PopFront(dequeExp);
			T_Destroy(tokenTemp);

			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);
		}
		else
			mistake(ERR_SYN, "Top of stack and token are not equal\n");
	}

	//vytvoreni promena pro vraceni z funkce
	variable = ST_VariableCreate();
	variable->defined = 1;
	variable->labelPlatnosti = RozsahPlatnostiGet();
	variable->type = function->returnType;

	package = ST_PackageCreate(ST_RandomKeyGenerator(), ST_VARIABLE, variable);

	nodeRet = nodeInsert(&localSymbolTable, package);

	//volani funkce

	AC_Item = AC_I_Create(AC_CALL, nodeFirst, nodeSecond, nodeRet);
	AC_Add(P_internalCode, AC_Item);

	return nodeRet;
}

nodePtr ParseBuiltinFunction(int function, Deque dequeExp, nodePtr localSymbolTable)
{
	nodePtr nodeFirst = NULL;
	nodePtr nodeSecond = NULL;
	nodePtr nodeThird = NULL;
	nodePtr nodeRet = NULL;

	symbolVariablePtr variable = NULL;
	symbolPackagePtr package = NULL;

	AC_itemPtr AC_Item = NULL;

	int end = 0;

	switch(function)
	{
	case BF_LENGTH:
	case BF_SORT:
		end = 4;
		break;
	case BF_FIND:
	case BF_CONCAT:
		end = 6;
		break;
	case BF_SUBSTR:
		end = 8;
		break;
	default:
		mistake(ERR_INTERN, "Unrecognized built in function.\n");
		break;
	}

	for(int i = 0; i < end; i++)
	{
		tokenTemp = D_TopFront(dequeExp);
		stackTop = S_Top(P_specialStack);

		if(i == 2) //there must be IDENTIFIER type STRING every time
		{
			if(tokenTemp->typ == TT_IDENTIFIER)
			{
				nodeFirst = searchNodeByKey(&localSymbolTable, charToStr(tokenTemp->data));
				if(nodeFirst == NULL)
					mistake(ERR_SEM_UND, "This identifier is not registered in symbol table \n");

				variable = nodeFirst->data->data;
				if(variable->type != ST_STRING)
					mistake(ERR_SEM_COMP, "This param needs to be string\n");
			}
			else if(tokenTemp->typ == TT_STRING)
				nodeFirst = nodeInsert(&localSymbolTable, TokenToSymbol(tokenTemp));
			else
				mistake(ERR_SEM_COMP, "Bad token type\n");
		}

		if(i == 4)
		{
			if(tokenTemp->typ == TT_IDENTIFIER)
			{
				nodeSecond = searchNodeByKey(&localSymbolTable, charToStr(tokenTemp->data));
				if(nodeSecond == NULL)
					mistake(ERR_SEM_UND, "This identifier is not registered in symbol table \n");

				variable = nodeSecond->data->data;
				switch(function)
				{
				case BF_CONCAT:
				case BF_FIND:
					if(variable->type != ST_STRING)
						mistake(ERR_SEM_COMP, "This param needs to be string\n");
					break;
				case BF_SUBSTR:
					if(variable->type != ST_INT)
						mistake(ERR_SEM_COMP, "This param needs to be string\n");
					break;
				default:
					mistake(ERR_INTERN, "Someone messed up with second build-in function list\n");
					break;
				}
			}
			else if((function == BF_CONCAT || function == BF_FIND) && tokenTemp->typ == TT_STRING)
				nodeThird = nodeInsert(&localSymbolTable, TokenToSymbol(tokenTemp));
			else if (function == BF_SUBSTR && (tokenTemp->typ == TT_INT || tokenTemp->typ == TT_BIN_NUM || tokenTemp->typ == TT_OCT_NUM || tokenTemp->typ == TT_HEX_NUM))
				nodeThird = nodeInsert(&localSymbolTable, TokenToSymbol(tokenTemp));
			else
				mistake(ERR_SEM_COMP, "Bad token type\n");
		}

		if(i == 6)
		{
			if(tokenTemp->typ == TT_IDENTIFIER)
			{
				nodeThird = searchNodeByKey(&localSymbolTable, charToStr(tokenTemp->data));
				if(nodeThird == NULL)
					mistake(ERR_SEM_UND, "This identifier is not registered in symbol table \n");

				variable = nodeThird->data->data;
				if(variable->type != ST_INT)
					mistake(ERR_SEM_COMP, "This param needs to be string\n");
			}
			else if (tokenTemp->typ == TT_INT || tokenTemp->typ == TT_BIN_NUM || tokenTemp->typ == TT_OCT_NUM || tokenTemp->typ == TT_HEX_NUM)
				nodeThird = nodeInsert(&localSymbolTable, TokenToSymbol(tokenTemp));
			else
				mistake(ERR_SEM_COMP, "Bad token type\n");
		}

		if(tokenTemp->typ == stackTop->typ)
		{
			tokenTemp = D_PopFront(dequeExp);
			T_Destroy(tokenTemp);

			tokenTemp = S_Pop(P_specialStack);
			T_Destroy(tokenTemp);
		}
		else
			mistake(ERR_SYN, "Top of stack and token are not equal\n");
	}

	variable = ST_VariableCreate();
	variable->defined = 1;
	variable->labelPlatnosti = RozsahPlatnostiGet();

	switch(function)
	{
	case BF_LENGTH:
	case BF_FIND:
		variable->type = ST_INT;
		break;
	case BF_SUBSTR:
	case BF_CONCAT:
	case BF_SORT:
		variable->type = ST_STRING;
		break;
	default:
		mistake(ERR_INTERN, "Someone messed up with second build-in function list\n");
		break;
	}

	package = ST_PackageCreate(ST_RandomKeyGenerator(), ST_VARIABLE, variable);

	nodeRet = nodeInsert(&localSymbolTable, package);

	switch(function)
	{
	case BF_LENGTH:
		AC_Item = AC_I_Create(AC_CALL_LENGTH, nodeFirst, NULL, nodeRet);
		AC_Add(P_internalCode, AC_Item);
		break;
	case BF_SUBSTR:
		AC_Item = AC_I_Create(AC_CALL_DUMMY, nodeThird, NULL, NULL);
		AC_Add(P_internalCode, AC_Item);

		AC_Item = AC_I_Create(AC_CALL_SUBSTR, nodeFirst, nodeSecond, nodeRet);
		AC_Add(P_internalCode, AC_Item);
		break;
	case BF_CONCAT:
		AC_Item = AC_I_Create(AC_CALL_CONCAT, nodeFirst, nodeSecond, nodeRet);
		AC_Add(P_internalCode, AC_Item);
		break;
	case BF_FIND:
		AC_Item = AC_I_Create(AC_CALL_FIND, nodeFirst, nodeSecond, nodeRet);
		AC_Add(P_internalCode, AC_Item);
		break;
	case BF_SORT:
		AC_Item = AC_I_Create(AC_CALL_SORT, nodeFirst, NULL, nodeRet);
		AC_Add(P_internalCode, AC_Item);
		break;
	default:
		mistake(ERR_INTERN, "Someone messed up with second build-in function list\n");
		break;
	}

	return nodeRet;
}

symbolPackagePtr TokenToSymbol(tTokenPtr token)
{
	symbolVariablePtr symbolVariable = NULL;
	symbolPackagePtr symbolPackage = NULL;

	if(token->typ != TT_INT || token->typ != TT_BIN_NUM || token->typ != TT_OCT_NUM || token->typ != TT_HEX_NUM || token->typ != TT_DOUBLE || token->typ != TT_STRING)
		return NULL;
	else
	{
		symbolVariable = ST_VariableCreate();
		symbolVariable->type = ST_Remap(tokenLast->typ);
		symbolVariable->defined = 1;
		symbolVariable->labelPlatnosti = RozsahPlatnostiGet();

		if(tokenLast->typ == TT_INT || tokenLast->typ == TT_BIN_NUM || tokenLast->typ == TT_OCT_NUM || tokenLast->typ == TT_HEX_NUM)
			ST_VariableAddData_INT(symbolVariable, charToInt(tokenLast->data));
		else if(tokenLast->typ == TT_DOUBLE)
			ST_VariableAddData_INT(symbolVariable, charToDouble(tokenLast->data));
		else if(tokenLast->typ == TT_STRING)
			symbolVariable->data = charToStr(tokenLast->data);
		else
			mistake(ERR_INTERN, "Problem with parsing token to symbol\n");

		symbolPackage = ST_PackageCreate(ST_RandomKeyGenerator(), ST_VARIABLE, symbolVariable);
	}
	return symbolPackage;
}

void ParseDoWhile(nodePtr localSymbolTable)
{
	int rule;
	AC_itemPtr AC_Item = NULL;

	int end = 1;

	for(int i = 0; i < end; i++)
	{
		stackTop = S_Top(P_specialStack);
		tokenLast = D_TopFront(P_tokenQueue);

		//zajisteni jaky pravidlo se pouzije
		rule = LL_TableRule(tokenLast, stackTop);

		if(i == 0)
		{
			RozsahPlatnostiAddInner(RozsahPlatnostiBuildStringFromChars("_DO"));	//label je pouze DO aby se nekomplikovalo hledani
			AC_Item = AC_I_Create(AC_LABEL,RozsahPlatnostiGet(),NULL,NULL);
			AC_Add(P_internalCode, AC_Item);

			AC_Item = AC_I_Create(AC_LABEL,RozsahPlatnostiBuildStringFromChars("_BODY"),NULL,NULL);
			AC_Add(P_internalCode, AC_Item);
		}
		switch(rule)
		{
		case 0:
			Rule0(localSymbolTable);
			break;
		default:
			mistake(ERR_SYN,"No rule for this\n");
			break;
		}
	}
}
void ParseDoWhilePart2(nodePtr localSymbolTable)
{
	int rule;
	AC_itemPtr AC_Item = NULL;

	int end = 5; //1. WHILE, 2. (, 3. EXP, 4. ), 5. ;

	for(int i = 0; i < end; i++)
	{
		stackTop = S_Top(P_specialStack);
		tokenLast = D_TopFront(P_tokenQueue);

		//zajisteni jaky pravidlo se pouzije
		rule = LL_TableRule(tokenLast, stackTop);

		if(i == 2)
		{
			AC_Item = AC_I_Create(AC_LABEL,RozsahPlatnostiBuildStringFromChars("_CONDIFION"),NULL,NULL);
			AC_Add(P_internalCode, AC_Item);

			nodePtr nodeExp = ParseExp(localSymbolTable, TT_PAR_R);

			AC_Item = AC_I_Create(AC_JUMP_C_TRUE, nodeExp, NULL, RozsahPlatnostiBuildStringFromChars("_BODY"));
			AC_Add(P_internalCode, AC_Item);

			AC_Item = AC_I_Create(AC_JUMP_C_FALSE_E, nodeExp, NULL, RozsahPlatnostiGet());
			AC_Add(P_internalCode, AC_Item);
		}

		if(i == 4)
		{
			//nahraje label oznacujici ukonceni oblasti platnosti
			AC_itemPtr AC_Item = AC_I_Create(AC_LABEL_END,RozsahPlatnostiGet(), NULL, NULL);
			AC_Add(P_internalCode, AC_Item);

			//odebere vnitni platnost
			RozsahPlatnostiRemoveInner();
		}

		switch(rule)
		{
		case 0:
			Rule0(localSymbolTable);
			break;
		default:
			mistake(ERR_SYN,"No rule for this\n");
			break;
		}
	}
}

void ParseWhile(nodePtr localSymbolTable)
{
	int rule;
	AC_itemPtr AC_Item = NULL;

	int end = 5;

	for(int i = 0; i < end; i++)
	{
		stackTop = S_Top(P_specialStack);
		tokenLast = D_TopFront(P_tokenQueue);

		//zajisteni jaky pravidlo se pouzije
		rule = LL_TableRule(tokenLast, stackTop);

		if(i == 2)
		{
			RozsahPlatnostiAddInner(RozsahPlatnostiBuildStringFromChars("_WHILE"));
			AC_Item = AC_I_Create(AC_LABEL,RozsahPlatnostiGet(),NULL,NULL);
			AC_Add(P_internalCode, AC_Item);

			AC_Item = AC_I_Create(AC_LABEL,RozsahPlatnostiBuildStringFromChars("_CONDIFION"),NULL,NULL);
			AC_Add(P_internalCode, AC_Item);

			nodePtr nodeExp = ParseExp(localSymbolTable, TT_PAR_R);

			AC_Item = AC_I_Create(AC_JUMP_C_TRUE, nodeExp, NULL, RozsahPlatnostiBuildStringFromChars("_BODY"));
			AC_Add(P_internalCode, AC_Item);

			AC_Item = AC_I_Create(AC_JUMP_C_FALSE_E, nodeExp, NULL, RozsahPlatnostiGet());
			AC_Add(P_internalCode, AC_Item);
		}

		if(i == 5)
		{
			AC_Item = AC_I_Create(AC_LABEL,RozsahPlatnostiBuildStringFromChars("_BODY"),NULL,NULL);
			AC_Add(P_internalCode, AC_Item);
		}

		switch(rule)
		{
		case 0:
			Rule0(localSymbolTable);
			break;
		default:
			mistake(ERR_SYN,"No rule for this\n");
			break;
		}
	}
}

//////////////////////////////////////////////////
// int LL_TableRule(tTokenPtr lastToken, tTokenPtr stackTop)
// return int - rule for parsing tokens
// lastToken - first unused token
// stackTop - top of stack from pushdown automaton
////////////////////
// Returning rule int value of next rule
//////////////////////////////////////////////////
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
	case TT_KEYWORD_DO:
		column += 19;
		break;
	case TT_KEYWORD_WHILE:
		column += 20;
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

//Function for removing one piece from stack and one from deque
void Rule0(nodePtr localSymbolTable)
{
	int remove = 0;
	int removeLabel = 1;
	AC_itemPtr AC_Item = NULL;

	if(tokenLast->typ == TT_BRACE_R && stackTop->typ == TT_BRACE_R)
	{
		//odchyceni veci jako FOR - nutno zachytit pred end label
		if(RozsahPlatnostiLastPart("FOR"))	//pokud je posledni for cyklus
		{
			AC_Item = AC_I_Create(AC_JUMP, NULL, NULL, RozsahPlatnostiBuildStringFromChars("_MODIFICATION"));
			AC_Add(P_internalCode, AC_Item);
		}

		if(RozsahPlatnostiLastPart("WHILE"))	//pokud je posledni for cyklus
		{
			AC_Item = AC_I_Create(AC_JUMP, NULL, NULL, RozsahPlatnostiBuildStringFromChars("_CONDITION"));
			AC_Add(P_internalCode, AC_Item);
		}

		if(RozsahPlatnostiLastPart("DO"))
			removeLabel = 0;


		if(removeLabel)
		{
			//nahraje label oznacujici ukonceni oblasti platnosti
			AC_itemPtr AC_Item = AC_I_Create(AC_LABEL_END,RozsahPlatnostiGet(), NULL, NULL);
			AC_Add(P_internalCode, AC_Item);

			//odebere vnitni platnost
			RozsahPlatnostiRemoveInner();
		}

		remove = 1;
	}
	else if(tokenLast->typ == TT_KEYWORD_WHILE)
	{
		if(RozsahPlatnostiLastPart("DO"))	//pokud je posledni for cyklus
			ParseDoWhilePart2(localSymbolTable);

		remove = 0;
	}
	else if(tokenLast->typ == TT_KEYWORD_ELSE)
	{
		RozsahPlatnostiAddInner(RozsahPlatnostiBuildStringFromChars("_ELSE"));
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

//nelze nijak ochranit pred padem pokud prijde rozdilne cislo v tokensPushed a tokenu samotnych
void TokenPusher(Deque stack, int tokensPushed, ...)
{
	va_list va;
	va_start(va, tokensPushed);

	for(int i = 0; i < tokensPushed; i++)
	{
		tokenTemp = T_Init();
		tokenTemp->typ = va_arg(va, int);
		S_Push(stack, tokenTemp);
	}

	va_end(va);
}

//////////////////////////////////////////////////
// int RozsahPlatnostiLastPart(char * str)
// return int (1 for TRUE, 0 for FALSE and -1 for error)
// str - char * for comparing
////////////////////
// Returning TRUE if top level rozsah platnosti a str are equal
//////////////////////////////////////////////////
//return 0 for false 1 for true
int RozsahPlatnostiLastPart(char * str)
{
	if(str != NULL)
	{
		int length;

		for(length = 0; str[length] != '\0'; length++); //spociat delku casti kterou hledam

		string rozsahPlatnosti = RozsahPlatnostiGet();

		if(rozsahPlatnosti->length < length)
			return -1;

		string lastPart = substr(rozsahPlatnosti,rozsahPlatnosti->length - length, length);

		if(strCompare(lastPart,charToStr(str)) == 0)
			return 1;
		else
			return 0;
	}
	else
		return -1;
}

//////////////////////////////////////////////////
// string RozsahPlatnostiBuildString(string newPart)
// return string
// newPart - part that will be added to top level rozsah platnosti
////////////////////
// Returning concat of top level rozsah platnosti and newPart
//////////////////////////////////////////////////
string RozsahPlatnostiBuildString(string newPart)
{
	string oldPart = NULL;
	string finished = NULL;

	if(newPart == NULL)
		mistake(ERR_INTERN, "Problem with building label\n");

	oldPart = RozsahPlatnostiGet();
	if(oldPart == NULL)
		finished = newPart;
	else
		finished = concat(oldPart,newPart);

	return finished;
}

//////////////////////////////////////////////////
// string RozsahPlatnostiBuildStringFromChars(char * newPart)
// return string
// newPart - part that will be added to top level rozsah platnosti
////////////////////
// Returning call to RozsahPlatnostiBuildString
//////////////////////////////////////////////////
string RozsahPlatnostiBuildStringFromChars(char * newPart)
{
	return RozsahPlatnostiBuildString(charToStr(newPart));
}

//////////////////////////////////////////////////
// void RozsahPlatnostiAddInner(string inner)
// inner - last part to be added to string
////////////////////
// Add inner to the end of top string and push it to P_platnostStack (Init stack if needed)
//////////////////////////////////////////////////
void RozsahPlatnostiAddInner(string inner)
{
	if(P_platnostStack == NULL)
		P_platnostStack = S_Init();

	if(P_platnostStack->last == NULL)
		S_Push(P_platnostStack, inner);
	else
	{
		string outer = S_Top(P_platnostStack);
		string innerComplete = concat(outer, inner);

		S_Push(P_platnostStack, innerComplete);
	}
}

//////////////////////////////////////////////////
// void RozsahPlatnostiRemoveInner()
////////////////////
// Remove top level (most inner) rozsah platnosti
//////////////////////////////////////////////////
void RozsahPlatnostiRemoveInner()
{
	string temp = S_Pop(P_platnostStack);
	strFree(temp);
}

//////////////////////////////////////////////////
// string RozsahPlatnostiGet()
// return string
////////////////////
// Return top level (most inner) rozsah platnosti
//////////////////////////////////////////////////
string RozsahPlatnostiGet()
{
	if(!S_Empty(P_platnostStack))
		return S_Top(P_platnostStack);
	else
		return NULL;
}

//////////////////////////////////////////////////
// void RozsahPlatnostiTerminate()
////////////////////
// Terminate content of P_platnostStack and free all string in it
//////////////////////////////////////////////////
void RozsahPlatnostiTerminate()
{
	while(!S_Empty(P_platnostStack))
	{
		RozsahPlatnostiRemoveInner();
	}

	S_Terminate(P_platnostStack);
	P_platnostStack = NULL;
}
