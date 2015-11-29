#include "syntactic_analyzer.h"

Deque stack = NULL;

int LL_TableRule(tTokenPtr lastToken, tTokenPtr stackTop);

void PutItInTree();
void CheckSEM(tTokenPtr token);
void ParseExp();

void Test_parse()
{
#if DEBUG
	printf("Parsing\n");

	while(1)
	{
		tTokenPtr token = T_Init();

		T_Get(token);

		printf("%d, %s\n",token->typ, token->data);

		if(token->typ == TT_EOF)
		{
			T_Destroy(token);
			break;
		}
		else
			T_Destroy(token);
	}

#endif

	//Inicializace globalni tabulky symbolu
}

void ParseExp()
{
	tTokenPtr tokenLast = NULL;
	int exp = 1;

	do
	{
		tokenLast = T_Init();
		T_Get(tokenLast);

		//Zpracovani
//TODO: Zpracovani EXP


		if(tokenLast->typ == TT_SEMICOLN)
			exp = 0;

		T_Destroy(tokenLast);
	}while(exp);
}

void Parse()
{
#if DEBUG
	printf("Parsing\n");
#endif

	//bool flag pro parsing 1 dokud se parsovani nedokonci
	int parsing = 1;
	//bool flag pro nacteni tokenu - 0 pokud se provadi vnitri operace
	int next = 1;

	//level zanoreni - vzdy by mel byt kladny nebo 0
	int level = 0;

	int rule;

	stack = S_Init();

	tTokenPtr tokenFirst = NULL;
	tTokenPtr tokenLast = NULL;
	tTokenPtr stackTop = NULL;

	//Pomocny token pro cokoliv - na co jej budu potrebovat
	tTokenPtr tokenTemp;

	//Nahrani prvniho tokenu na stack aby oznacoval konec
	tokenFirst = T_Init();
	tokenFirst->typ = TT_SPECIAL_DOLLAR;
	T_Finish(tokenFirst);

	S_Push(stack, tokenFirst);

	while(parsing)
	{
		if(next)
		{
			tokenLast = T_Init();
			T_Get(tokenLast);
		}

		stackTop = S_Top(stack);

		rule = LL_TableRule(tokenLast, stackTop);


#if DEBUG
		printf("Using rule %d\n",rule);
#endif
		switch(rule)
		{
		//Case 0 is for  comparing tokenLast a stackTop - v danou chvili by se meli rovnat a zaroven odebrat
		//Zde zaroven dochazi k overovani SEM a tvorbe syntaxTree
		case 0:
			next = 1;

/*
			//if podminky na volani funkci
			PutItInTree();
			ChceckSEM(tokenLast);
*/

			if(stackTop->typ == TT_SPECIAL_DOLLAR && tokenLast->typ == TT_EOF)
				parsing = 0; //parsovani dokonceno

			if(stackTop->typ == tokenLast->typ || parsing == 0)
			{
				tokenTemp = S_Pop(stack);
				T_Destroy(tokenTemp);
				T_Destroy(tokenLast);
			}
			else
				mistake(ERR_SYN,"There was problem with applying RULE 0, on stack was %d but token was %d\n",stackTop->typ,tokenLast->typ);
			break;
		case 1:
			next = 0;

			level--; //dochazi k vynoreni

			//znici nejvyssi TT_SPECIAL (krome $, osetreno jinde)

			tokenTemp = S_Pop(stack);
			T_Destroy(tokenTemp);

			break;
		case 2:
			next = 0;

			//STAT jiz na zasobniku

			tokenTemp = T_Init();
			tokenTemp->typ = TT_PAR_R;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SPECIAL_EXP;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_PAR_L;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_KEYWORLD_IF;
			S_Push(stack, tokenTemp);

			break;
		case 3:
			next = 0;

			//STAT jiz na zasobniku

			tokenTemp = T_Init();
			tokenTemp->typ = TT_KEYWORLD_ELSE;
			S_Push(stack, tokenTemp);

			break;
		case 4:
			next = 0;

			//odebere STAT ze zasobniku
			tokenTemp = S_Pop(stack);
			T_Destroy(tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SPECIAL_STAT;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_PAR_R;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SPECIAL_EXP;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SEMICOLN;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SPECIAL_EXP;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SEMICOLN;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SPECIAL_EXP;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_PAR_L;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_KEYWORLD_FOR;
			S_Push(stack, tokenTemp);

			break;
		case 5:
			next = 0;

			//STAT_LS jiz na zasobniku

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SPECIAL_STAT;
			S_Push(stack, tokenTemp);

			break;
		case 6:
			next = 0;

			//odebere STAT ze zasobniku
			tokenTemp = S_Pop(stack);
			T_Destroy(tokenTemp);

			tokenTemp = S_Pop(stack);
			tokenTemp->typ = TT_SEMICOLN;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SPECIAL_EXP;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_KEYWORLD_RETURN;
			S_Push(stack, tokenTemp);

			break;
		case 7:
			next = 0;

			//odebere STAT ze zasobniku a rovnou ho nahradi
			tokenTemp = S_Pop(stack);
			tokenTemp->typ = TT_SPECIAL_CIN_LS;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_KEYWORLD_CIN;
			S_Push(stack, tokenTemp);

			break;
		case 8:
			next = 0;

			//odebere STAT ze zasobniku a rovnou ho nahradi
			tokenTemp = S_Pop(stack);
			tokenTemp->typ = TT_SPECIAL_COUT_LS;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_KEYWORLD_COUT;
			S_Push(stack, tokenTemp);

			break;
		case 9:
			next = 0;

			//odebere STAT ze zasobniku
			tokenTemp = S_Pop(stack);
			T_Destroy(tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_BRACE_R;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SPECIAL_STAT_LS;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_BRACE_L;
			S_Push(stack, tokenTemp);

			break;
		case 10:
			next = 0;

			//FUNKCE_P jiz na zasobniku

			tokenTemp = T_Init();
			tokenTemp->typ = TT_COMMA;
			S_Push(stack, tokenTemp);

			break;
		case 11:
			next = 0;

			//odebere STAT ze zasobniku a rovnou ho nahradi
			tokenTemp = S_Pop(stack);
			tokenTemp->typ = TT_SEMICOLN;
			S_Push(stack, tokenTemp);

			break;
		case 12:
			next = 0;

			tokenTemp = T_Init();
			tokenTemp->typ = TT_IDENTIFIER;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_INSERTION;
			S_Push(stack, tokenTemp);

			break;
		case 13:
			next = 0;

			tokenTemp = T_Init();
			tokenTemp->typ = TT_IDENTIFIER;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_EXTRACTION;
			S_Push(stack, tokenTemp);

			break;
		case 14:
			next = 0;

			tokenTemp = S_Pop(stack);
			tokenTemp->typ = TT_SEMICOLN;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SPECIAL_EXP;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_ASSIGN; //Tady budou problemy...protoze je k dispozici moc druhu assignu //FIXME:ASSIGNS
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_IDENTIFIER;
			S_Push(stack, tokenTemp);

			break;
		case 15:
			next = 0;

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SPECIAL_FUNKCE_LS;
			S_Push(stack, tokenTemp);

			break;
		case 16:
			next = 0;

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SPECIAL_FUNKCE;

			break;
		case 17:
			next = 0;

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SPECIAL_STAT;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_PAR_R;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_SPECIAL_FUNKCE_P;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_PAR_L;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = TT_IDENTIFIER;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = tokenLast->typ; //Zde pouziju trik aby typ indentifikatoru byl stejny jako typ tokenu - tohle resi az semantika
			S_Push(stack, tokenTemp);

			break;
		case 18:
			next = 0;

			//pozor tady se FUNKCE_P nechava na zasobniku protoze nepouziva svuj list

			tokenTemp = T_Init();
			tokenTemp->typ = TT_IDENTIFIER;
			S_Push(stack, tokenTemp);

			tokenTemp = T_Init();
			tokenTemp->typ = tokenLast->typ;
			S_Push(stack, tokenTemp);

			break;
		case 19:	//SPECIAL CASE - EXP: slouzi k praci na podminkach a vyrazech

			ParseExp();

			break;
		default:
			mistake(ERR_SYN,"There is no rule for this operation");
			break;
		}
	}

	T_Destroy(tokenFirst);

	S_Terminate(stack);
#if DEBUG
	printf("Parsing done\n");
#endif
}

int LL_TableRule(tTokenPtr lastToken, tTokenPtr stackTop)
{
	//Zacnu s -1 aby mapovani odpovidalo papiru
	int row = -1;
	int column= -1;

	switch(stackTop->typ)
	{
		case TT_SPECIAL_DOLLAR:
			row += 1;
			break;
		case TT_SPECIAL_FUNKCE_LS:
			row += 2;
			break;
		case TT_SPECIAL_FUNKCE:
			row += 3;
			break;
		case TT_SPECIAL_FUNKCE_P:
			row += 4;
			break;
		case TT_SPECIAL_STAT_LS:
			row += 5;
			break;
		case TT_SPECIAL_STAT:
			row += 6;
			break;
		case TT_SPECIAL_CIN_LS:
			row += 7;
			break;
		case TT_SPECIAL_COUT_LS:
			row += 8;
			break;
		case TT_SPECIAL_EXP:
			row += 9;
			break;
	}

	switch(lastToken->typ)
	{
		case TT_EOF:
			column += 1;
			break;
		case TT_KEYWORLD_IF:
			column += 2;
			break;
		case TT_KEYWORLD_ELSE:
			column += 3;
			break;
		case TT_KEYWORLD_FOR:
			column += 4;
			break;
		case TT_KEYWORLD_RETURN:
			column += 5;
			break;
		case TT_KEYWORLD_CIN:
			column += 6;
			break;
		case TT_KEYWORLD_COUT:
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
		case TT_SEMICOLN:
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
		case TT_KEYWORLD_INT:
		case TT_KEYWORLD_DOUBLE:
		case TT_KEYWORLD_STRING:
		case TT_KEYWORLD_CHAR:
		case TT_KEYWORLD_VOID:
			column += 16;
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

//prozatimni iplementace jen aby bylo co volat
//TODO: Implement function for putting things to tree
void PutItInTree()
{

}

//TODO: Re-think implementation of SEM and auto to something checking AND implement it
void CheckSEM(tTokenPtr token)
{

}
