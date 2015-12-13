#include "interpret.h"







int do_instr( Deque internalCode )	//vykonava instrukcie
//vstup je tmp->data ukazujuci na obsah dequecontainer;
{

	#if DEBUG
		printf("Starting executing instruction \n");
	#endif
	symbolVariablePtr temp1 /*source 1*/, temp2 /*source 2 */, temp3 /* destination*/, temp4 /* pre call dummy*/;
	nodePtr temporaryNode;


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
				case	AC_OP_ASSIGN:
				case AC_RETURN:

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
				/*case AC_JUMP:
					string s = NULL;
					s = tmp->destination->data->key;
					DequeContainer pom = NULL;
					DequeContainer pom = tmp->data;
					internalCode->active = internalCode->first;

					while (internalCode->active != NULL )
						{
							internalCodeNext(Deque * internalCode);
							if ((internalCode->active != pom ) && (s == tmp->destination->data->key ||
								 s == tmp->source1->data->key ||  s == tmp->source2->data->key))
								{
									return 0;
								}

							else
							{
								if (internalCode->active == internalCode->last) mistake(ERR_RUN_OTH,"AC_JUMP is not working correctly");
							}
						}
				break;
				///////////////////////////////////////
				case AC_JUMP_C_TRUE:
				if (temp1->type == ST_INT || temp1->type == ST_DOUBLE )
				{
					if (temp1->data == 1 )
					{
						string s = NULL;
						s = tmp->destination->data->key;
						DequeContainer pom = NULL;
						DequeContainer pom = tmp->data;
						internalCode->active = internalCode->first;

						while (internalCode->active != NULL )
							{
								internalCodeNext(Deque * internalCode);
								if ((internalCode->active != pom ) && (s == tmp->destination->data->key ||
									 s == tmp->source1->data->key ||  s == tmp->source2->data->key))
									{
										return 0;
									}

								else
								{
									if (internalCode->active == internalCode->last) mistake(ERR_RUN_OTH,"AC_JUMP is not working correctly");
								}
							}
					}
				}
				break;
				///////////////////////////////////////
				case AC_JUMP_C_FALSE:
				if (temp1->type == ST_INT || temp1->type == ST_DOUBLE )
				{
					if (temp1->data == 0 )
					{
						string s = NULL;
						s = tmp->destination->data->key;
						DequeContainer pom = NULL;
						DequeContainer pom = tmp->data;
						internalCode->active = internalCode->first;

						while (internalCode->active != NULL )
							{
								internalCodeNext(Deque * internalCode);
								if ((internalCode->active != pom ) && (s == tmp->destination->data->key ||
									 s == tmp->source1->data->key ||  s == tmp->source2->data->key))
									{
										return 0;
									}

								else
								{
									if (internalCode->active == internalCode->last) mistake(ERR_RUN_OTH,"AC_JUMP is not working correctly");
								}
							}
					}
				}
				break;
				///////////////////////////////////////
				case AC_JUMP_C_FALSE_E:	 	//skace na konec IF-u;
				if (temp1->type == ST_INT || temp1->type == ST_DOUBLE )
				{
					if (temp1->data == 0 )
					{
						string s = NULL;
						s = tmp->destination->data->key;
						DequeContainer pom = NULL;
						DequeContainer pom = tmp->data;
						internalCode->active = internalCode->first;

						while (internalCode->active != NULL )
							{
								internalCodeNext(Deque * internalCode);
								if ((internalCode->active != pom ) && (s == tmp->destination->data->key ||
									 s == tmp->source1->data->key ||  s == tmp->source2->data->key))
									{
										return 0;
									}

								else
								{
									if (internalCode->active == internalCode->last) mistake(ERR_RUN_OTH,"AC_JUMP is not working correctly");
								}
							}
					}
				}

				break; */
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

				D_ActiveMoveToBack(internalCode);

				AC_itemPtr tmp2 = D_TopActive(internalCode);
				temporaryNode = (nodePtr) tmp2->source1;
				temp4 = (symbolVariablePtr) temporaryNode->data->data;

				D_ActiveMoveToFront(internalCode);
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
					temp3->type == ST_INT;

				}
				else
				{
					temp3->type == ST_DOUBLE;
				}
				//double i = ( temp1->data + temp2->data);
				printf("%lf %lf\n",temp1->data, temp2->data);
				break;
				#if fuck_off
        ///////////////////////////////////////
				case AC_OP_SUB:
				if ( !(temp1->type == ST_INT || temp1->type == ST_DOUBLE ) ||
				 !(temp2->type == ST_INT || temp2->type == ST_INT))
				{
					#if DEBUG
						mistake(ERR_RUN_OTH,"cant Sub without int or real variables");
					#endif
				}
				if (temp1->type == ST_INT && temp2->type == ST_INT ) temp3->type == ST_INT;
					else temp3->type == ST_DOUBLE;
				temp3->data = (temp1->data - temp2->data );
				break;
        ///////////////////////////////////////
				case AC_OP_DIV:
				if ( !(temp1->type == ST_INT || temp1->type == ST_DOUBLE ) ||
				 !(temp2->type == ST_INT || temp2->type == ST_DOUBLE))
				{
					#if DEBUG
						mistake(ERR_RUN_OTH,"cant Divide without int or real variables");
					#endif
				}
				if (temp1->type == ST_INT && temp2->type == ST_INT )
				{
					int i = temp2->data
					temp3->type == ST_INT;
				}
				else temp3->type == ST_DOUBLE;
				if (temp2->data == 0 ) mistake(ERR_ZERO,"Dividing by zero is not possible");
				temp3->data = (temp1->data / temp2->data);
				break;
        ///////////////////////////////////////
				case	AC_OP_MUL:
				if ( !(temp1->type == ST_INT || temp1->type == ST_DOUBLE ) ||
				 !(temp2->type == ST_INT || temp2->type == ST_DOUBLE))
				{
					#if DEBUG
						mistake(ERR_RUN_OTH,"cant MULTI without int or real variables");
					#endif
				}
				if (temp1->type == ST_INT && temp2->type == ST_INT ) temp3->type == ST_INT;
					else temp3->type == ST_DOUBLE;
				temp3->data = (temp1->data * temp2->data);

				break;
        ///////////////////////////////////////
				case	AC_OP_ASSIGN:
				if ( temp1->type == ST_INT ||
					temp1->type == ST_DOUBLE  ||
					temp1->type == ST_STRING ) {
				if ( temp1->type == ST_INT ) temp3->type = ST_INT;
				if ( temp1->type == ST_DOUBLE ) temp3->type = ST_DOUBLE;
				if ( temp1->type == ST_STRING ) temp3->type = ST_STRING;
				temp3->data = temp1->data;
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
					string s = NULL;
					s = tmp->destination->data->key;
					DequeContainer pom = NULL;
					DequeContainer pom = tmp->data;
					internalCode->active = internalCode->first;

					while (internalCode->active != NULL )
						{
							internalCodeNext(Deque * internalCode);
							if ((internalCode->active != pom ) && (s == tmp->destination->data->key ||
								 s == tmp->source1->data->key ||  s == tmp->source2->data->key))
								{
									return 0;
								}

							else
							{
								if (internalCode->active == internalCode->last) mistake(ERR_RUN_OTH,"AC_JUMP is not working correctly");
							}
						}
				break;
        ///////////////////////////////////////
				case AC_JUMP_C_TRUE:
				if (temp1->type == ST_INT || temp1->type == ST_DOUBLE )
				{
					if (temp1->data == 1 )
					{
						string s = NULL;
						s = tmp->destination->data->key;
						DequeContainer pom = NULL;
						DequeContainer pom = tmp->data;
						internalCode->active = internalCode->first;

						while (internalCode->active != NULL )
							{
								internalCodeNext(Deque * internalCode);
								if ((internalCode->active != pom ) && (s == tmp->destination->data->key ||
									 s == tmp->source1->data->key ||  s == tmp->source2->data->key))
									{
										return 0;
									}

								else
								{
									if (internalCode->active == internalCode->last) mistake(ERR_RUN_OTH,"AC_JUMP is not working correctly");
								}
							}
					}
				}
				break;
        ///////////////////////////////////////
				case AC_JUMP_C_FALSE:
				if (temp1->type == ST_INT || temp1->type == ST_DOUBLE )
				{
					if (temp1->data == 0 )
					{
						string s = NULL;
						s = tmp->destination->data->key;
						DequeContainer pom = NULL;
						DequeContainer pom = tmp->data;
						internalCode->active = internalCode->first;

						while (internalCode->active != NULL )
							{
								internalCodeNext(Deque * internalCode);
								if ((internalCode->active != pom ) && (s == tmp->destination->data->key ||
									 s == tmp->source1->data->key ||  s == tmp->source2->data->key))
									{
										return 0;
									}

								else
								{
									if (internalCode->active == internalCode->last) mistake(ERR_RUN_OTH,"AC_JUMP is not working correctly");
								}
							}
					}
				}
				break;
        ///////////////////////////////////////
				case AC_JUMP_C_FALSE_E:	 	//skace na konec IF-u;
				if (temp1->type == ST_INT || temp1->type == ST_DOUBLE )
				{
					if (temp1->data == 0 )
					{
						string s = NULL;
						s = tmp->destination->data->key;
						DequeContainer pom = NULL;
						DequeContainer pom = tmp->data;
						internalCode->active = internalCode->first;

						while (internalCode->active != NULL )
							{
								internalCodeNext(Deque * internalCode);
								if ((internalCode->active != pom ) && (s == tmp->destination->data->key ||
									 s == tmp->source1->data->key ||  s == tmp->source2->data->key))
									{
										return 0;
									}

								else
								{
									if (internalCode->active == internalCode->last) mistake(ERR_RUN_OTH,"AC_JUMP is not working correctly");
								}
							}
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
						if (temp1->data > temp2->data) temp3->data = 1;
						else  temp3->data = 0;
					}
					else
					{
						int i = 0;
						i = strcmp(temp1->data->str,temp2->data->str);
						if(i > 0)
							{
								temp3->data = 1;
							}
						else temp3->data = 0;
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
						if (temp1->data >= temp2->data) temp3->data = 1;
						else  temp3->data = 0;
					}
					else
					{
						int i = 0;
						i = strcmp(temp1->data->str,temp2->data->str);
						if(i >= 0)
							{
								temp3->data = 1;
							}
						else temp3->data = 0;
					}
				}
				else mistake(ERR_INTERN,"different combination is not tolerated in AC_GREATER_EQUAL");
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
						if (temp1->data < temp2->data) temp3->data = 1;
						else  temp3->data = 0;
					}
					else
					{
						int i = 0;
						i = strcmp(temp1->data->str,temp2->data->str);
						if(i < 0)
							{
								temp3->data = 1;
							}
						else temp3->data = 0;
					}
				}
				else mistake(ERR_INTERN,"different combination is not tolerated in AC_LESS");
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
						if (temp1->data <= temp2->data) temp3->data = 1;
						else  temp3->data = 0;
					}
					else
					{
						int i = 0;
						i = strcmp(temp1->data->str,temp2->data->str);
						if(i <= 0)
							{
								temp3->data = 1;
							}
						else temp3->data = 0;
					}
				}
				else mistake(ERR_INTERN,"different combination is not tolerated in AC_LESS_EQUAL");

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
						if (temp1->data == temp2->data) temp3->data = 1;
						else  temp3->data = 0;
					}
					else
					{
						int i = 0;
						i = strcmp(temp1->data->str,temp2->data->str);
						if(i == 0)
							{
								temp3->data = 1;
							}
						else temp3->data = 0;
					}
				}
				else mistake(ERR_INTERN,"different combination is not tolerated in AC_EQUAL");
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
						if (temp1->data != temp2->data) temp3->data = 1;
						else  temp3->data = 0;
					}
					else
					{
						int i = 0;
						i = strcmp(temp1->data->str,temp2->data->str);
						if(i != 0)
							{
								temp3->data = 1;
							}
						else temp3->data = 0;
					}
				}
				else mistake(ERR_INTERN,"different combination is not tolerated in AC_NOT_EQUAL");
				break;
        ///////////////////////////////////////
				case AC_CALL_CIN:

				break;
        ///////////////////////////////////////
				case AC_CALL_COUT: {
				//vypis hmmm
					switch (temp1->type)
						//-----------------------
						case ST_INT: printf("%d", temp1->data );
						break;
						//-----------------------
						case ST_DOUBLE: printf("%lf",temp1->data );
						break;
						//-----------------------
						case ST_STRING: printf("%s",temp1->data->str );
						break;
						//-----------------------
					}
				break;
        ///////////////////////////////////////
				case	AC_CALL_LENGTH:
				if ( temp1->type == ST_STRING)
				{ int i;
					i = strGetLength(temp1->data);
					temp3->data = i;
				}
				break;
        ///////////////////////////////////////
				case AC_CALL_DUMMY:	//slouzi k posilani parametru ktere by se nevesly

				break;
        ///////////////////////////////////////
				case AC_CALL:

				break;
        ///////////////////////////////////////
				case AC_RETURN:	// vrati

				break;
        ///////////////////////////////////////
				case AC_CALL_SORT:
				if( temp1->type == ST_STRING )
				{
					temp3->data = sort( temp1->data);
				}
				break;
        ///////////////////////////////////////
			/*	case AC_CALL_SUBSTR:
				  if (internalCode->active->prevPtr->dataPtr->data->operation == AC_CALL_DUMMY &&
					internalCode->active->prevPtr->dataPtr->data->source1->data->type == ST_INT )
					{
						if ( temp1->type == ST_STRING && temp2->type == ST_INT )
							{
								temp3->type == ST_STRING;
								int n = internalCode->active->prevPtr->dataPtr->data->source1->data->data;
								int i = temp2->data;
								temp3->data = substr( temp1->data,  temp2->data, n);
							}
					}
				break;*/
        ///////////////////////////////////////
				case AC_CALL_CONCAT:
					if( temp1->type == ST_STRING && temp2->type == ST_STRING )
					{
						temp3->type = ST_STRING;
						temp3->data = concat(temp1->data,temp2->data);

					}
					else mistake(ERR_INTERN,"AC_CALL_CONCAT input is wrong");
				break;
        ///////////////////////////////////////
				case AC_CALL_FIND:
					if( temp1->type == ST_STRING && temp2->type == ST_STRING )
						{
							temp3->type = ST_INT;
							temp3->data = find(temp1->data,temp2->data);

						}
					else mistake(ERR_INTERN,"AC_CALL_FIND input is wrong");
				break;
#endif
				default: break;
		}

		#if DEBUG
			printf("do_instr done\n");
		#endif
		return 0;
}

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
		if ( i != 0 ) mistake(i,"Error in do_instr");
		internalCode->active = internalCode->active->nextPtr;
		if(internalCode->active == NULL)
			mistake(ERR_RUN_OTH, "No return in code\n");

	}
#if DEBUG
	printf("Interpreting done\n");
#endif

}
