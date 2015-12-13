///////////////////////////////////////////////////////////////////////////////
/* ---------- IMPLEMENTACE INTERPRETU IMPERATIVNÍHO JAZYKA IFJ15 ----------- */
///////////////////////////////////////////////////////////////////////////////
//
//	AUTOŘI:
//
//	xbedna57 	ADAM BEDNÁRIK
//	xmacha63 	ERIK MACHÁČEK
//	xmalar02 	MARTIN MALÁRIK
//	xlengu00 	MANH LE NGUYEN
//
///////////////////////////////////////////////////////////////////////////////
#include "interpret.h"



///////////
// int do_instr( Deque internalCode ) is executing instructions
//  Deque internalCode	-	 is standard Queue with 3 adrress code
///////////
//vstup je tmp->data ukazujuci na obsah dequecontainer

int do_instr ( Deque internalCode)
{

	#if DEBUG
		printf("Starting executing instruction \n");
	#endif
  static DequeContainer kontajner = NULL;
	symbolVariablePtr temp1 = NULL /*source 1*/, temp2 = NULL/*source 2 */, temp3 = NULL/* destination*/, temp4 = NULL/* pre call dummy*/;
	nodePtr temporaryNode = NULL;
	string s = NULL;

	AC_itemPtr tmp = D_TopActive(internalCode);
	int Label = tmp->operation;

		switch (Label)
			{
				case AC_OP_ADD:
				case AC_OP_SUB:
				case AC_OP_DIV:
				case AC_OP_MUL:

				temporaryNode = (nodePtr) tmp->source1;
				temp1 = (symbolVariablePtr) temporaryNode->data->data;
				temporaryNode = (nodePtr) tmp->source2;
				temp2 = (symbolVariablePtr) temporaryNode->data->data;
				temporaryNode = (nodePtr) tmp->destination;
				temp3 = (symbolVariablePtr) temporaryNode->data->data;

				break;
				///////////////////////////////////////
				case AC_OP_ASSIGN:


				temporaryNode = (nodePtr) tmp->source1;
				temp1 = (symbolVariablePtr) temporaryNode->data->data;
				temporaryNode = (nodePtr) tmp->destination;
				temp3 = (symbolVariablePtr) temporaryNode->data->data;

				break;
				///////////////////////////////////////
				case AC_LABEL:

				break;
				///////////////////////////////////////
				case AC_LABEL_END:

				break;
				///////////////////////////////////////
				case AC_JUMP:
				temporaryNode = (nodePtr) tmp->destination;
				temp3 = (symbolVariablePtr) temporaryNode->data->data;

				break;
				///////////////////////////////////////
				case AC_JUMP_C_TRUE:
				temporaryNode = (nodePtr) tmp->source1;
				temp1 = (symbolVariablePtr) temporaryNode->data->data;

				temporaryNode = (nodePtr) tmp->destination;
				temp3 = (symbolVariablePtr) temporaryNode->data->data;

				break;
				///////////////////////////////////////
				case AC_JUMP_C_FALSE:
				temporaryNode = (nodePtr) tmp->source1;
				temp1 = (symbolVariablePtr) temporaryNode->data->data;

				temporaryNode = (nodePtr) tmp->destination;
				temp3 = (symbolVariablePtr) temporaryNode->data->data;

				break;
				///////////////////////////////////////
				case AC_JUMP_C_FALSE_E:	 	//skace na konec IF-u;
				temporaryNode = (nodePtr) tmp->source1;
				temp1 = (symbolVariablePtr) temporaryNode->data->data;

				temporaryNode = (nodePtr) tmp->destination;
				temp3 = (symbolVariablePtr) temporaryNode->data->data;
				break;
				///////////////////////////////////////
				case AC_GREATER://cisla
				case AC_GREATER_EQUAL:
				case AC_LESS:
				case AC_LESS_EQUAL:
				case AC_NOT_EQUAL:
				case AC_EQUAL:

				temporaryNode = (nodePtr) tmp->source1;
				temp1 = (symbolVariablePtr) temporaryNode->data->data;
				temporaryNode = (nodePtr) tmp->source2;
				temp2 = (symbolVariablePtr) temporaryNode->data->data;
				temporaryNode = (nodePtr) tmp->destination;
				temp3 = (symbolVariablePtr) temporaryNode->data->data;
				break;
				///////////////////////////////////////
				case AC_CALL_CIN:

				temporaryNode = (nodePtr) tmp->destination;
				temp3 = (symbolVariablePtr) temporaryNode->data->data;

				break;
				///////////////////////////////////////
				case AC_CALL_COUT:

					temporaryNode = (nodePtr) tmp->source1;
					temp1 = (symbolVariablePtr) temporaryNode->data->data;

				break;
				///////////////////////////////////////
				case	AC_CALL_LENGTH:

				temporaryNode = (nodePtr) tmp->source1;
				temp1 = (symbolVariablePtr) temporaryNode->data->data;
				temporaryNode = (nodePtr) tmp->destination;
				temp3 = (symbolVariablePtr) temporaryNode->data->data;

				break;
				///////////////////////////////////////
				case AC_CALL_DUMMY:	//slouzi k posilani parametru ktere by se nevesly

				break;
				///////////////////////////////////////
				case AC_CALL:

				break;
				///////////////////////////////////////
				case AC_RETURN:

				temporaryNode = (nodePtr) tmp->source1;
				temp1 = (symbolVariablePtr) temporaryNode->data->data;

				break;
				///////////////////////////////////////
				case AC_CALL_SORT:
				temporaryNode = (nodePtr) tmp->source1;
				temp1 = (symbolVariablePtr) temporaryNode->data->data;
				temporaryNode = (nodePtr) tmp->destination;
				temp3 = (symbolVariablePtr) temporaryNode->data->data;
				break;
				///////////////////////////////////////
				case AC_CALL_SUBSTR:
				temporaryNode = (nodePtr) tmp->source1;
				temp1 = (symbolVariablePtr) temporaryNode->data->data;
				temporaryNode = (nodePtr) tmp->source2;
				temp2 = (symbolVariablePtr) temporaryNode->data->data;
				temporaryNode = (nodePtr) tmp->destination;
				temp3 = (symbolVariablePtr) temporaryNode->data->data;
				break;
				///////////////////////////////////////
				case AC_CALL_CONCAT:
				case AC_CALL_FIND:
				temporaryNode = (nodePtr) tmp->source1;
				temp1 = (symbolVariablePtr) temporaryNode->data->data;
				temporaryNode = (nodePtr) tmp->source2;
				temp2 = (symbolVariablePtr) temporaryNode->data->data;
				temporaryNode = (nodePtr) tmp->destination;
				temp3 = (symbolVariablePtr) temporaryNode->data->data;

				break;
				///////////////////////////////////////
				default : break;
		}

		switch (Label)
			{
				case AC_OP_ADD: //ok
				if ( (temp1->type == ST_STRING || temp2->type == ST_STRING ) ||
				 (temp1->type == ST_UNDEFINED || temp2->type == ST_UNDEFINED))
				{
					#if DEBUG
						mistake(ERR_RUN_OTH,"cant ADD without int or real variables");
					#endif
				}
				if (temp1->type == ST_INT && temp2->type == ST_INT )
				{
					temp3->type = ST_INT;
					temp3->dataInt = (temp1->dataInt + temp2->dataInt);
				}
				else if (temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )
				{
					temp3->type = ST_DOUBLE;
					temp3->dataDouble = (temp1->dataDouble + temp2->dataDouble);
				}
				else if (temp1->type == ST_DOUBLE && temp2->type == ST_INT)
				{
					temp3->type = ST_DOUBLE;
					temp3->dataDouble = (temp1->dataDouble + temp2->dataInt);
				}
				else if (temp1->type == ST_INT && temp2->type == ST_DOUBLE)
				{
					temp3->type = ST_DOUBLE;
					temp3->dataDouble = (temp1->dataInt + temp2->dataDouble);
				}

				break;

        ///////////////////////////////////////
				case AC_OP_SUB:
				if ( (temp1->type == ST_STRING || temp2->type == ST_STRING ) ||
				 (temp1->type == ST_UNDEFINED || temp2->type == ST_UNDEFINED))
				{
					#if DEBUG
						mistake(ERR_RUN_OTH,"cant Sub without int or real variables");
					#endif
				}
					if (temp1->type == ST_INT && temp2->type == ST_INT )
					{
						temp3->type = ST_INT;
						temp3->dataInt = (temp1->dataInt - temp2->dataInt);
					}
					else if (temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )
					{
						temp3->type = ST_DOUBLE;
						temp3->dataDouble = (temp1->dataDouble - temp2->dataDouble);
					}
					else if (temp1->type == ST_DOUBLE && temp2->type == ST_INT)
					{
						temp3->type = ST_DOUBLE;
						temp3->dataDouble = (temp1->dataDouble - temp2->dataInt);
					}
					else if (temp1->type == ST_INT && temp2->type == ST_DOUBLE)
					{
						temp3->type = ST_DOUBLE;
						temp3->dataDouble = (temp1->dataInt - temp2->dataDouble);
					}
				break;
        ///////////////////////////////////////
				case AC_OP_DIV:
				if ( (temp1->type == ST_STRING || temp2->type == ST_STRING ) ||
				 (temp1->type == ST_UNDEFINED || temp2->type == ST_UNDEFINED))
				{
					#if DEBUG
						mistake(ERR_RUN_OTH,"cant Divide without int or real variables");
					#endif
				}
				if (temp1->type == ST_INT && temp2->type == ST_INT )
				{
					if (temp2->dataInt == 0 )
					{mistake(ERR_ZERO,"cant divide with 0");}
					temp3->type = ST_INT;
					temp3->dataInt = (temp1->dataInt / temp2->dataInt);
				}
				else if (temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )
				{
					if (temp2->dataDouble == 0 )
					{mistake(ERR_ZERO,"cant divide with 0");}
					temp3->type = ST_DOUBLE;
					temp3->dataDouble = (temp1->dataDouble / temp2->dataDouble);
				}
				else if (temp1->type == ST_DOUBLE && temp2->type == ST_INT)
				{
					if (temp2->dataInt == 0 )
					{mistake(ERR_ZERO,"cant divide with 0");}
					temp3->type = ST_DOUBLE;
					temp3->dataDouble = (temp1->dataDouble / temp2->dataInt);
				}
				else if (temp1->type == ST_INT && temp2->type == ST_DOUBLE)
				{
					if (temp2->dataDouble == 0 )
					{mistake(ERR_ZERO,"cant divide with 0");}
					temp3->type = ST_DOUBLE;
					temp3->dataDouble = (temp1->dataInt / temp2->dataDouble);
				}
				break;
        ///////////////////////////////////////
				case	AC_OP_MUL:
				if ( (temp1->type == ST_STRING || temp2->type == ST_STRING ) ||
				 (temp1->type == ST_UNDEFINED || temp2->type == ST_UNDEFINED))
				{
					#if DEBUG
						mistake(ERR_RUN_OTH,"cant MULTI without int or real variables");
					#endif
				}
					if (temp1->type == ST_INT && temp2->type == ST_INT )
					{
						temp3->type = ST_INT;
						temp3->dataInt = (temp1->dataInt - temp2->dataInt);
					}
					else if (temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )
					{
						temp3->type = ST_DOUBLE;
						temp3->dataDouble = (temp1->dataDouble - temp2->dataDouble);
					}
					else if (temp1->type == ST_DOUBLE && temp2->type == ST_INT)
					{
						temp3->type = ST_DOUBLE;
						temp3->dataDouble = (temp1->dataDouble - temp2->dataInt);
					}
					else if (temp1->type == ST_INT && temp2->type == ST_DOUBLE)
					{
						temp3->type = ST_DOUBLE;
						temp3->dataDouble = (temp1->dataInt - temp2->dataDouble);
					}
				break;
        ///////////////////////////////////////
				case	AC_OP_ASSIGN:
				if ( temp1->type == ST_INT ||	temp1->type == ST_DOUBLE  || temp1->type == ST_STRING )
				{
					if ( temp1->type == ST_INT )
					{
						temp3->type = ST_INT;
						temp3->dataInt = temp1->dataInt;
					}
					if ( temp1->type == ST_DOUBLE )
					{
						temp3->type = ST_DOUBLE;
						temp3->dataDouble = temp1->dataDouble;
					}
					if ( temp1->type == ST_STRING )
					{
						temp3->type = ST_STRING;
						temp3->data = temp1->data;
					}
				}
				else mistake(ERR_INTERN,"error in AC_OP_ASSIGN");
				break;
        ///////////////////////////////////////
				case AC_LABEL:
				break;
        ///////////////////////////////////////
				case AC_LABEL_END:
				break;
      	///////////////////////////////////////
				case AC_JUMP:
					s = temp3->data;
					D_ActivateFront(internalCode);

					while (1)
						{
							D_ActiveMoveToBack(internalCode);
							tmp = D_TopActive(internalCode);
							if (tmp->operation == AC_LABEL && (strCompare(tmp->source1,s) == 0 ))
							break;
							else if (internalCode->active == internalCode->last) mistake(ERR_RUN_OTH,"AC_JUMP is not working correctly");
						}
				break;
        ///////////////////////////////////////
				case AC_JUMP_C_TRUE:

				s = temp3->data;
				if (temp1->dataInt == 1)
				{
				D_ActivateFront(internalCode);
				while (1)
					{
						D_ActiveMoveToBack(internalCode);
						tmp = D_TopActive(internalCode);
						if (tmp->operation == AC_LABEL && (strCompare(tmp->source1,s) == 0 ))
						break;
						else if (internalCode->active == internalCode->last) mistake(ERR_RUN_OTH,"AC_JUMP is not working correctly");
					}
				}

				break;
        ///////////////////////////////////////
				case AC_JUMP_C_FALSE:
				s = temp3->data;
				if (temp1->dataInt == 0)
				{
				D_ActivateFront(internalCode);
				while (1)
					{
						D_ActiveMoveToBack(internalCode);
						tmp = D_TopActive(internalCode);
						if (tmp->operation == AC_LABEL && (strCompare(tmp->source1,s) == 0 ))
						break;
						else if (internalCode->active == internalCode->last) mistake(ERR_RUN_OTH,"AC_JUMP is not working correctly");
					}
				}

				break;
        ///////////////////////////////////////
				case AC_JUMP_C_FALSE_E:	 	//skace na konec IF-u;

				s = temp3->data;
				if (temp1->dataInt == 1)
				{
				D_ActivateFront(internalCode);
				while (1)
					{
						D_ActiveMoveToBack(internalCode);
						tmp = D_TopActive(internalCode);
						if (tmp->operation == AC_LABEL_END && (strCompare(tmp->source1,s) == 0 ))
						break;
						else if (internalCode->active == internalCode->last) mistake(ERR_RUN_OTH,"AC_JUMP is not working correctly");
					}
				}

				break;
        ///////////////////////////////////////
				case AC_GREATER://cisla
				if ((temp1->type == ST_DOUBLE && temp2->type == ST_INT)||
				(temp1->type == ST_INT && temp2->type == ST_DOUBLE)||
				(temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )||
				(temp1->type == ST_INT && temp2->type == ST_INT)||
				(temp1->type == ST_STRING && temp2->type == ST_STRING ))
				{
					temp3->type = ST_INT;
					if(temp1->type != ST_STRING)
					{
						if (temp1->type == ST_INT && temp2->type == ST_INT)
						{
							if (temp1->dataInt > temp2->dataInt) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )
						{
							if (temp1->dataDouble > temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_INT && temp2->type == ST_DOUBLE)
						{
							temp1->dataDouble = temp1->dataInt;
							if (temp1->dataDouble > temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_DOUBLE && temp2->type == ST_INT)
						{
							temp2->dataDouble = temp2->dataInt;
							if (temp1->dataDouble > temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
					}
					else
					{
						int i = 0;
						i = strCompare(temp1->data,temp2->data);
						if(i > 0)
							{
								temp3->dataInt = 1;
							}
						else temp3->dataInt = 0;
					}
				}
				else mistake(ERR_INTERN,"different combination is not tolerated in AC_GREATER");
				break;
        ///////////////////////////////////////
				case AC_GREATER_EQUAL:
				if ((temp1->type == ST_DOUBLE && temp2->type == ST_INT)||
				(temp1->type == ST_INT && temp2->type == ST_DOUBLE)||
				(temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )||
				(temp1->type == ST_INT && temp2->type == ST_INT)||
				(temp1->type == ST_STRING && temp2->type == ST_STRING ))
				{
					temp3->type = ST_INT;
					if(temp1->type != ST_STRING)
					{
						if (temp1->type == ST_INT && temp2->type == ST_INT)
						{
							if (temp1->dataInt >= temp2->dataInt) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )
						{
							if (temp1->dataDouble >= temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_INT && temp2->type == ST_DOUBLE)
						{
							temp1->dataDouble = temp1->dataInt;
							if (temp1->dataDouble >= temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_DOUBLE && temp2->type == ST_INT)
						{
							temp2->dataDouble = temp2->dataInt;
							if (temp1->dataDouble >= temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
					}
					else
					{
						int i = 0;
						i = strCompare(temp1->data,temp2->data);
						if(i >= 0)
							{
								temp3->dataInt = 1;
							}
						else temp3->dataInt = 0;
					}
				}
				else mistake(ERR_INTERN,"different combination is not tolerated in AC_GREATER");
				break;
        ///////////////////////////////////////
				case AC_LESS:
				if ((temp1->type == ST_DOUBLE && temp2->type == ST_INT)||
				(temp1->type == ST_INT && temp2->type == ST_DOUBLE)||
				(temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )||
				(temp1->type == ST_INT && temp2->type == ST_INT)||
				(temp1->type == ST_STRING && temp2->type == ST_STRING ))
				{
					temp3->type = ST_INT;
					if(temp1->type != ST_STRING)
					{
						if (temp1->type == ST_INT && temp2->type == ST_INT)
						{
							if (temp1->dataInt < temp2->dataInt) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )
						{
							if (temp1->dataDouble < temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_INT && temp2->type == ST_DOUBLE)
						{
							temp1->dataDouble = temp1->dataInt;
							if (temp1->dataDouble < temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_DOUBLE && temp2->type == ST_INT)
						{
							temp2->dataDouble = temp2->dataInt;
							if (temp1->dataDouble < temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
					}
					else
					{
						int i = 0;
						i = strCompare(temp1->data,temp2->data);
						if(i < 0)
							{
								temp3->dataInt = 1;
							}
						else temp3->dataInt = 0;
					}
				}
				else mistake(ERR_INTERN,"different combination is not tolerated in AC_GREATER");
				break;
        ///////////////////////////////////////
				case AC_LESS_EQUAL:
				if ((temp1->type == ST_DOUBLE && temp2->type == ST_INT)||
				(temp1->type == ST_INT && temp2->type == ST_DOUBLE)||
				(temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )||
				(temp1->type == ST_INT && temp2->type == ST_INT)||
				(temp1->type == ST_STRING && temp2->type == ST_STRING ))
				{
					temp3->type = ST_INT;
					if(temp1->type != ST_STRING)
					{
						if (temp1->type == ST_INT && temp2->type == ST_INT)
						{
							if (temp1->dataInt <= temp2->dataInt) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )
						{
							if (temp1->dataDouble <= temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_INT && temp2->type == ST_DOUBLE)
						{
							temp1->dataDouble = temp1->dataInt;
							if (temp1->dataDouble <= temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_DOUBLE && temp2->type == ST_INT)
						{
							temp2->dataDouble = temp2->dataInt;
							if (temp1->dataDouble <= temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
					}
					else
					{
						int i = 0;
						i = strCompare(temp1->data,temp2->data);
						if(i <= 0)
							{
								temp3->dataInt = 1;
							}
						else temp3->dataInt = 0;
					}
				}
				else mistake(ERR_INTERN,"different combination is not tolerated in AC_GREATER");
				break;
        ///////////////////////////////////////
				case AC_EQUAL:
				if ((temp1->type == ST_DOUBLE && temp2->type == ST_INT)||
				(temp1->type == ST_INT && temp2->type == ST_DOUBLE)||
				(temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )||
				(temp1->type == ST_INT && temp2->type == ST_INT)||
				(temp1->type == ST_STRING && temp2->type == ST_STRING ))
				{
					temp3->type = ST_INT;
					if(temp1->type != ST_STRING)
					{
						if (temp1->type == ST_INT && temp2->type == ST_INT)
						{
							if (temp1->dataInt == temp2->dataInt) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )
						{
							if (temp1->dataDouble == temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_INT && temp2->type == ST_DOUBLE)
						{
							temp1->dataDouble = temp1->dataInt;
							if (temp1->dataDouble == temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_DOUBLE && temp2->type == ST_INT)
						{
							temp2->dataDouble = temp2->dataInt;
							if (temp1->dataDouble == temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
					}
					else
					{
						int i = 0;
						i = strCompare(temp1->data,temp2->data);
						if(i == 0)
							{
								temp3->dataInt = 1;
							}
						else temp3->dataInt = 0;
					}
				}
				else mistake(ERR_INTERN,"different combination is not tolerated in AC_GREATER");
				break;
        ///////////////////////////////////////
				case AC_NOT_EQUAL:
				if ((temp1->type == ST_DOUBLE && temp2->type == ST_INT)||
				(temp1->type == ST_INT && temp2->type == ST_DOUBLE)||
				(temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )||
				(temp1->type == ST_INT && temp2->type == ST_INT)||
				(temp1->type == ST_STRING && temp2->type == ST_STRING ))
				{
					temp3->type = ST_INT;
					if(temp1->type != ST_STRING)
					{
						if (temp1->type == ST_INT && temp2->type == ST_INT)
						{
							if (temp1->dataInt != temp2->dataInt) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_DOUBLE && temp2->type == ST_DOUBLE )
						{
							if (temp1->dataDouble != temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_INT && temp2->type == ST_DOUBLE)
						{
							temp1->dataDouble = temp1->dataInt;
							if (temp1->dataDouble != temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
						else if (temp1->type == ST_DOUBLE && temp2->type == ST_INT)
						{
							temp2->dataDouble = temp2->dataInt;
							if (temp1->dataDouble != temp2->dataDouble) temp3->dataInt = 1;
							else  temp3->dataInt = 0;
						}
					}
					else
					{
						int i = 0;
						i = strCompare(temp1->data,temp2->data);
						if(i != 0)
							{
								temp3->dataInt = 1;
							}
						else temp3->dataInt = 0;
					}
				}
				else mistake(ERR_INTERN,"different combination is not tolerated in AC_GREATER");
				break;
        ///////////////////////////////////////

				case AC_CALL_CIN:
				switch (temp1->type)
				{
					//-----------------------
					case ST_INT:
					if (scanf("%d",&temp1->dataInt ) != 1 ) mistake(ERR_LOAD,"didn't loaded int");
					break;
					//-----------------------
					case ST_DOUBLE:
					if (scanf("%lf",&temp1->dataDouble) != 1 ) mistake(ERR_LOAD,"didn't loaded double");
					break;
					//-----------------------
					case ST_STRING:
					{
						char * c,znak;
						int size = 1;
						c = MM_Malloc(sizeof(char));
						znak = getchar();
						if ( znak != '\v' || znak != ' ' || znak != '\f' || znak != '\n' || znak != '\r' || znak != '\t' )
						{
							c[0] = znak;

							while(1)
							{
								size = size + 1 ;
								znak = getchar();
								if ( znak == '\v' || znak == ' ' || znak == '\f' || znak == '\n' || znak == '\r' || znak == '\t' )	{break;}
								MM_Realloc(c, size);
								c[size-1] = znak;
							}

							s = strInit();
							if (strInsert(s, c) == -1 ) {mistake(ERR_LOAD,"didn't loaded string");}
							temp1->data = s;
						}
					}
					break;
					//-----------------------
				}
				break;
        ///////////////////////////////////////
				case AC_CALL_COUT:
				{
						switch (temp1->type)
						{
							//-----------------------
							case ST_INT: printf("%d", temp1->dataInt );
							break;
							//-----------------------
							case ST_DOUBLE: printf("%lf",temp1->dataDouble );
							break;
							//-----------------------
							case ST_STRING:
							s = temp1->data;
							printf("%s",s->str );
							break;
							//-----------------------
						}

				}
				break;
        ///////////////////////////////////////
				case	AC_CALL_LENGTH:
				if ( temp1->type == ST_STRING)
				{
					int i;
					i = length(temp1->data);
					temp3->dataInt = i;
				}
				break;
        ///////////////////////////////////////
				case AC_CALL_DUMMY:	//slouzi k posilani parametru ktere by se nevesly
				break;
        ///////////////////////////////////////
				case AC_CALL:

				break;
        ///////////////////////////////////////
				case AC_RETURN:
				if (kontajner == NULL ) return 42;
				else
				{
					internalCode->active = kontajner;
					tmp = D_TopActive(internalCode);
					temporaryNode = (nodePtr) tmp->destination;
					temp3 = (symbolVariablePtr) temporaryNode->data->data;
					if ( temp3->type == temp1->type)
						switch (temp3->type)
						{
							case ST_INT:
							temp3->dataInt = temp1->dataInt;
							break;
							case ST_DOUBLE:
							temp3->dataDouble = temp1->dataDouble;
							break;
							case ST_STRING:
							temp3->data = temp1->data;
							break;
						}
				}
				break;
        ///////////////////////////////////////
				case AC_CALL_SORT:
				if( temp1->type == ST_STRING )
				{
					temp3->data = sort(temp1->data);
				}
				break;
        ///////////////////////////////////////
				case AC_CALL_SUBSTR:
					D_ActiveMoveToFront(internalCode);
					tmp = D_TopActive(internalCode);

					temporaryNode = (nodePtr) tmp->source1;
					temp4 = (symbolVariablePtr) temporaryNode->data->data;

				  if (tmp->operation == AC_CALL_DUMMY && temp4->type == ST_INT )
					{
						if ( temp1->type == ST_STRING && temp2->type == ST_INT )
							{
								temp3->type = ST_STRING;
								temp3->data = substr( temp1->data, temp2->dataInt, temp4->dataInt);
							}
					}
					D_ActiveMoveToBack(internalCode);
				break;
        ///////////////////////////////////////
				case AC_CALL_CONCAT:
					if( temp1->type == ST_STRING && temp2->type == ST_STRING )
					{
						temp3->type = ST_STRING;
						temp3->data = concat(temp1->data, temp2->data);
					}
					else mistake(ERR_INTERN,"AC_CALL_CONCAT input is wrong");
				break;
        ///////////////////////////////////////
				case AC_CALL_FIND:
					if( temp1->type == ST_STRING && temp2->type == ST_STRING )
						{
							temp3->type = ST_INT;
							temp3->dataInt = find(temp1->data, temp2->data);

						}
					else mistake(ERR_INTERN,"AC_CALL_FIND input is wrong");
				break;

				default: break;
		}

		#if DEBUG
			printf("do_instr done\n");
		#endif
		return 0;
}
///////////
// void Interpret(Deque internalCode, nodePtr symbolTable) main funkcion of interpreter
// Deque internalCode		-	 is standard Queue with 3 adrress code
// nodePtr symbolTable 	-	 binaryTree
///////////
void Interpret(Deque internalCode, nodePtr symbolTable)
{
#if DEBUG
	printf("Starting interpreting internal code\n");
#endif

internalCode->active = internalCode->first;

while(1) // nastav active na main
	{
		if (internalCode->active == internalCode->last )
		{
			mistake(ERR_SEM_UND,"there is no main in program");
		}
AC_itemPtr tmp =  D_TopActive(internalCode);
string str_main = charToStr("main");
		if (strCompare(str_main, tmp->source1) == 0 )
			{
				#if DEBUG
					printf("I have main\n");
				#endif
				break;
			}
		internalCode->active = internalCode->active->nextPtr;
	}

while (internalCode->active != NULL)
	{	//odkazuje sa na AC_itemPtr;

		int i = do_instr(internalCode);
		if ( i == 42 ) break;
		internalCode->active = internalCode->active->nextPtr;
		if(internalCode->active == NULL)
			mistake(ERR_RUN_OTH, "No return in code\n");

	}
#if DEBUG
	printf("Interpreting done\n");
#endif

}
