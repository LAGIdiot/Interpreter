#include "lexical_analyzer.h"

void T_Get(tTokenPtr tokenPtr)
{
	int state = FM_START;
	int read_char;
	
	int whiteSpace;

	while (state != FM_END)
	{
		read_char = fgetc(file_p);
		whiteSpace = isspace(read_char);
		
		//Odchyceni bilych znaku zde aby se usetri na rychlosti
		if(whiteSpace && state == FM_START)
		{
			continue;
		}

		//Odchyceni konce souboru zde protoze switch nechape EOF konstantu
		if(read_char == EOF)
		{
			tokenPtr->typ = TT_EOF;
			state = FM_END;
			break;
		}

		switch (state)
		{
			case FM_START:
				switch(read_char)
				{
					case ';':
						state = FM_SEMICOLN;
						break;
					case '#':
						state = FM_HASH;
						break;
					case '*':
						state = FM_STAR;
						break;
					case '+':
						state = FM_PLUS;
						break;
					case '-':
						state = FM_MINUS;
						break;
					case '/':
						state = FM_DIVIDE;
						break;
					default:	//special case - pro nezaregistrovany znaky (casem by nemel byt zadny...)
						T_Update(read_char);

						state = FM_UNRECOGNIZED;
						break;
				}	//switch
				break;
				case FM_SEMICOLN:
					tokenPtr->typ = TT_SEMICOLN;

					ungetc(read_char, file_p);
					state = FM_END;

					break;
				case FM_HASH:
					tokenPtr->typ = TT_HASH;

					ungetc(read_char, file_p);
					state = FM_END;

					break;
				case FM_STAR:
					tokenPtr->typ = TT_STAR;

					if(read_char == '=')
						state = FM_STAR_ASSIGN;
					else
					{
						ungetc(read_char, file_p);
						state = FM_END;
					}
					break;
				case FM_STAR_ASSIGN:
					tokenPtr->typ = TT_ASSIGN_MUL;

					ungetc(read_char, file_p);
					state = FM_END;

					break;
				case FM_PLUS:
					tokenPtr->typ = TT_PLUS;
					if(read_char == '=')
						state = FM_PLUS_ASSIGN;
//TODO: ++
					else
					{
						ungetc(read_char, file_p);
						state = FM_END;
					}
					break;
				case FM_PLUS_ASSIGN:
					tokenPtr->typ = TT_ASSIGN_ADD;

					ungetc(read_char, file_p);
					state = FM_END;

					break;
				case FM_MINUS:
					tokenPtr->typ = TT_MINUS;
					if(read_char == '=')
						state = FM_MINUS_ASSIGN;
//TODO: --
					else
					{
						ungetc(read_char, file_p);
						state = FM_END;
					}
					break;
				case FM_MINUS_ASSIGN:
					tokenPtr->typ = TT_ASSIGN_SUB;

					ungetc(read_char, file_p);
					state = FM_END;

					break;
				case FM_DIVIDE:
					tokenPtr->typ = TT_DIVIDE;

					if(read_char == '=')
						state = FM_DIVIDE_ASSIGN;
					else if(read_char == '/')
						state = FM_COMMENT_SINGLELINE;
					else if(read_char == '*')
						state = FM_COMMENT_MULTILINE;
					else
					{
						ungetc(read_char, file_p);
						state = FM_END;
					}
					break;
				case FM_DIVIDE_ASSIGN:
					tokenPtr->typ = TT_ASSIGN_DIV;

					ungetc(read_char, file_p);
					state = FM_END;

					break;
				case FM_COMMENT_SINGLELINE:
					tokenPtr->typ = TT_UNDEFINED;

					if(read_char == NEW_LINE)
						state = FM_START;

					break;
				case FM_COMMENT_MULTILINE:
					tokenPtr->typ = TT_UNDEFINED;

					if(read_char == '*')
						state = FM_COMMENT_MULTILINE_END;

					break;
				case FM_COMMENT_MULTILINE_END:
					if(read_char == '/')
						state = FM_START;

					break;
			default:	//special case - zatim nezaregistrovany znaky/slova -> system je bude flusat po jednom ven;
				tokenPtr->typ = TT_UNRECOGNIZED;

				if(!whiteSpace)
					T_Update(read_char);
				else
					state = FM_END;
				break;
		}	//switch

#if just_using_this_for_storing_code_that_needs_to_be_rewriten_but_must_not_be_compiled

		///////////////////////////////////////////////////////////////////////////
		// ROZPOZNÁVÁNÍ NAČTENÉHO ZNAKU
		/*------------------------------------------------------------------------- 
			větvící struktura rozlišuje jeden načtený znak a následně nastavuje
			aktuální stav konečného automatu.
		*//////////////////////////////////////////////////////////////////////////
		switch (read_char)
		{
			case '.':
			{
				if (state == FM_INTEGER)
				{
					T_Update(tokenPtr, read_char);
					state = FM_DOUBLE;
				}
			}break;
			case '_':
			{
				if (state == FM_START)
				{
					state = FM_VARIABLE;
				}
				
				T_Update(tokenPtr, read_char);
			}break;
			
			case '=':
			{
				if (state == FM_ASSIGN)
				{
					state = FM_EQUAL;
				}
				else
				{
					state = FM_ASSIGN;
				}
				
				T_Update(tokenPtr, read_char);
			}break;
			/////////////////////////////////////////////////////////////////////////
			// ROZPOZNÁVÁNÍ "BĚŽNÝCH" ZNAKŮ
			/*-----------------------------------------------------------------------
					Detekce běžných znaků je oddělená, protože není nutné, aby každý znak
					byl vypsán ve SWITCHI. Navíc se zde ošetřují speciální případy jako
					klíčová slova.
			*////////////////////////////////////////////////////////////////////////
			default:
			{
				if (((read_char >= CAPITAL_A) && (read_char <= CAPITAL_Z))
					|| ((read_char >= LETTER_A) && (read_char >= LETTER_Z)))
				{
					switch (state)
					{
						case FM_ASSIGN:
						{
							ungetc(read_char, file_p);
						} break;
						
						default:
						{
							T_Update(tokenPtr, read_char);
							/////////////////////////////////////////////////////////////////
							// POROVNÁNÍ OBSAHU TOKENU S KLÍČOVÝMI SLOVY
							/* --------------------------------------------------------------
								 Podmínka testuje, zda se obsah tokenu nerovná jednomu z
								 klíčových slov IFJ15. Následně dochází ke kontrole, zda se
								 nejedná o proměnnou. Jakmile řetězec pokračuje, jde o proměnnou,
								 pokud ne, jde o klíčové slovo a je přečtený znak vrácen souboru.
							*////////////////////////////////////////////////////////////////
							if ((strlen(tokenPtr->data) == 2) || (strlen(tokenPtr->data) == 3)
								|| (strlen(tokenPtr->data) == 4) || (strlen(tokenPtr->data) == 5))
							{
								if ((strcmp(tokenPtr->data, "auto") != 0) || (strcmp(tokenPtr->data, "cin") != 0)
									|| (strcmp(tokenPtr->data, "cout") != 0) || (strcmp(tokenPtr->data, "double") != 0)
									|| (strcmp(tokenPtr->data, "else") != 0) || (strcmp(tokenPtr->data, "for") != 0)
									|| (strcmp(tokenPtr->data, "if") != 0) || (strcmp(tokenPtr->data, "int") != 0)
									|| (strcmp(tokenPtr->data, "return") != 0) || (strcmp(tokenPtr->data, "string") != 0))
								{
									read_char = fgetc(file_p);
									if (((read_char >= CAPITAL_A) && (read_char <= CAPITAL_Z))
										|| ((read_char >= LETTER_A) && (read_char >= LETTER_Z))
										|| (read_char == '_'))
									{
										state = FM_VARIABLE;
									}
									else
									{
										state = FM_KEYWORDS;
									}
									
									ungetc(read_char, file_p);
								}
							}
							
						} break;
					}
				}

				else if ((read_char >= ZERO) && (read_char <= NINE))
				{
					if (state == FM_START)
					{
						state = FM_INTEGER;
					}
					else if (state == FM_INTEGER)
					{
							
					}
					else if (state == FM_DOUBLE)
					{
							
					}
					else if (state == FM_VARIABLE)
					{
						T_Update(tokenPtr, read_char);
					}
				}
			}
			/////////////////////////////////////////////////////////////////////////
			// PŘEPÍNÁNÍ STAVŮ AUTOMATU A UKONČOVÁNÍ TOKENU
			/*-----------------------------------------------------------------------
					Na základě stavu z předchozího switche se rozhodne, zda ukončit token
			*////////////////////////////////////////////////////////////////////////
			switch (state)
			{
				case FM_COMMENT_SINGLELINE:
				{
					if (read_char == '\n')
					{
						state = FM_START;
					}
					else if (read_char == '\\')
					{
						fgetc(file_p);
					}
				}break;
				
				case FM_COMMENT_MULTILINE:
				{
					if (read_char == '*')
					{
						if ((read_char = fgetc(file_p)) == '/')
						{
							state = FM_START;
						}
					}
				}break;
				
				case FM_SEMICON:
				{
					state = FM_END;
				}break;
				
				case FM_ASSIGN:
				{
					
				}break;
				
				case FM_EQUAL:
				{
					state = FM_END;
				} break;
				
				case FM_PLUS:
				{
					if ((read_char = fgetc(file_p)) != '+')
					{
						ungetc(read_char, file_p);
						state = FM_END;
					}
				} break;
				
				case FM_INCREMENT:
				{
					state = FM_END;
				} break;
				
				case FM_MINUS:
				{
					if ((read_char = fgetc(file_p)) != '-')
					{
						ungetc(read_char, file_p);
						state = FM_END;
					}
				} break;
				
				case FM_DECREMENT:
				{
					state = FM_END;
				} break;
				
				case FM_STAR:
				{
					if ((read_char = fgetc(file_p)) != '/')
					{
						ungetc(read_char, file_p);
						state = FM_END;
					}
				} break;
				
				case FM_DIVISION:
				{
					if ((read_char = fgetc(file_p)) != '/')
					{
						ungetc(read_char, file_p);
						state = FM_END;
					}
				} break;
				
				case FM_KEYWORDS:
				{
					state = FM_END;
				} break;
				
				default: ;break;
			}
		}
#endif
	}	//while
	T_Finish(tokenPtr);
}	//T_Get
