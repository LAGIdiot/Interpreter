#include "lexical_analyzer.h"

///////////////////////////////////////////////////////////////////////////////
// FUNKCE PRO ZJIŠTĚNÍ, ZDA JE TOKEN KLÍČOVÉ SLOVO
//-----------------------------------------------------------------------------
/*Funkce projíždí obsah pole keywordů a porovnává
jednotlivé položky s tokenem*/
///////////////////////////////////////////////////////////////////////////////
int IsKeyword()
{
	char *token_content =  T_GetData();
	
	if (strlen(token_content) > LONGEST_KEYWORD)
	{
		// je delší než nejdelší keyword, nemá cenu řešit dál
		return 1;
	}
	else
	{
		for (int i = 0; i < KEYWORD_COUNT; i++)
		{
			if (strlen(key_words[i]) == strlen(token_content))
			{
				if (!strcmp(key_words[i], token_content))
				{
					return 0;
				}
				else
				{
					return 1;
				}
			}
			else
			{
				return 1;
			}
		}
	}
}

int EndOfNumber(char c)
{
	for (int i = 0; i < EON_COUNT; i++)
	{
		if (c == eon[i])
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// FUNKCE PRO ZÍSKÁVÁNÍ JEDNOHO TOKENU
//-----------------------------------------------------------------------------
/*Funkce po dotázání vyflusne jeden token s typem a obsahem*/
///////////////////////////////////////////////////////////////////////////////
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
//TODO: prerovnat stavy atomatu at je nabeh co nejrychlejsi
//TODO: doplnit dalsi stavy a rozpoznani tokenu
			//-----------------------------------------------------------------------
			
			/////////////////////////////////////////////////////////////////////////
			// ROZPOZNÁNÍ NOVĚ PŘÍCHOZÍHO ZNAKU
			//-----------------------------------------------------------------------
			/*Stav FM_START rozpoznává první příchozí znak po ukončení předchozího
			tokenu*/
			/////////////////////////////////////////////////////////////////////////
			case FM_START:
				switch(read_char)
				{
					case '(':
						state = FM_PAR_L;
						break;
						
					case ')':
						state = FM_PAR_R;
						break;
						
					case '{':
						state = FM_BRACE_L;
						break;
						
					case '}':
						state = FM_BRACE_R;
						break;
						
					case '[':
						state = FM_BRACKET_L;
						break;
						
					case ']':
						state = FM_BRACKET_R;
						break;
				
					case ';':
						state = FM_SEMICOLON;
						break;
						
					//TODO smazat
					/*case '#': // asi k hovnu
						state = FM_HASH;
						break;*/
						
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
						
					case '=':
						state = FM_ASSIGN;
						break;
						
					//TODO smazat
					/*case '.': // asi k hovnu 
						state = FM_DOT;
						break;*/
						
					case ',':
						state = FM_COMMA;
						break;
						
					case '|':
						state = FM_OR;
						break;
						
					case '&':
						state = FM_AND;
						break;
						
					case '>':
						state = FM_GREATER;
						break;
						
					case '<':
						state = FM_LESS;
						break;
						
					case '_':
						state = FM_VARIABLE;
						break;
					
					case '!':
						state = FM_NOT_EQUAL;
						break;
						
					case '\':
						state = FM_NUM_BASE;
						break;
						
					case '"'
						state = FM_STRING;
						break;
						
					//-------------------------------------------------------------------
					// Zpracování všech ostatní znaků (bordelu) včetně a-z, A-Z a 0-9
					//-------------------------------------------------------------------
					default:	//special case - pro nezaregistrovany znaky (casem by nemel byt zadny...)
					{
						// když je to znak a-z nebo A-Z
						if (((read_char >= LETTER_A) && (read_char <= LETTER_Z))
						|| ((read_char >= CAPITAL_A) && (read_char <= CAPITAL_Z)))
						{
							state = FM_CODEWORD;
						}
						// když je to znak 0
						else if (read_char == ZERO)
						{
							continue; // Nuly se na začátku čísla ignorují
						}
						// když je to znak 1-9
						else if ((read_char >= ZERO+1) && (read_char <= NINE))
						{
							state = FM_NUMBER;
						}
						else
						{
							state = FM_UNRECOGNIZED;
						}
						T_Update(read_char, file_p);
					}
					break;
						
				}	//switch v case FM_START
			break;
				
			/////////////////////////////////////////////////////////////////////////
			// DALŠÍ STAVY 
			/////////////////////////////////////////////////////////////////////////
			//TODO PŘETOVNAT ZA ÚČELEM ZVÝŠENÍ RYCHLOSTI KA
			
			case FM_PAR_L:
			{
				tokenPtr->typ = TT_PAR_L;
				
				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
			
			case FM_PAR_R:
			{
				tokenPtr->typ = TT_PAR_R;
				
				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
			
			case FM_BRACE_L:
			{
				tokenPtr->typ = TT_BRACE_L;
				
				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
			
			case FM_BRACE_R:
			{
				tokenPtr->typ = TT_BRACE_R;
				
				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
			
			case FM_BRACKET_L:
			{
				tokenPtr->typ = TT_BRACKET_L;
				
				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
			
			case FM_BRACKET_R:
			{
				tokenPtr->typ = TT_BRACKET_R;
				
				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
			
			case FM_SEMICOLON:
			{
				tokenPtr->typ = TT_SEMICOLN;

				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
				
			case FM_HASH:
			{
				tokenPtr->typ = TT_HASH;

				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
				
			case FM_STAR:
			{
				tokenPtr->typ = TT_STAR;
				
				//TODO smazat
				/*if(read_char == '=')
					state = FM_STAR_ASSIGN;*/

				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
			
			//TODO smazat	
			/*case FM_STAR_ASSIGN:
			{
				tokenPtr->typ = TT_ASSIGN_MUL;

				ungetc(read_char, file_p);
				state = FM_END;
			} break;*/
			//-----------------------------------------------------------------------
					
			case FM_PLUS:
			{
				tokenPtr->typ = TT_PLUS;
				
				//TODO smazat
				/*if(read_char == '=')
					state = FM_PLUS_ASSIGN;*/
				if (read_char == '+')
				{
					state = FM_INCREMENT;
				}
				else
				{
					ungetc(read_char, file_p);
					state = FM_END;
				}
			} break;
			//-----------------------------------------------------------------------
					
			case FM_INCREMENT:
			{
				tokenPtr->typ = TT_INCREMENT;
					
				ungetc(read_char, file_p);
				state = FM_END;
			}
			
			//TODO smazat		
			/*case FM_PLUS_ASSIGN:
			{
				tokenPtr->typ = TT_ASSIGN_ADD;

				ungetc(read_char, file_p);
				state = FM_END;
			} break;*/
			//-----------------------------------------------------------------------
				
			case FM_MINUS:
			{
				tokenPtr->typ = TT_MINUS;
				//TODO smazat
				/*if(read_char == '=')
					state = FM_MINUS_ASSIGN;*/
				if (read_char == '-')
				{
					state = FM_DECREMENT;
				}
				else
				{
					ungetc(read_char, file_p);
					state = FM_END;
				}
			} break;
			//-----------------------------------------------------------------------
					
			case FM_DECREMENT:
			{
				tokenPtr->typ = TT_DECREMENT;
	
				ungetc(read_char, file_p);
				state = FM_END;
			}	break;
			//-----------------------------------------------------------------------
			
			//TODO smazat
			/*case FM_MINUS_ASSIGN:
			{
				tokenPtr->typ = TT_ASSIGN_SUB;

				ungetc(read_char, file_p);
				state = FM_END;
			} break;*/
			//-----------------------------------------------------------------------
				
			case FM_DIVIDE:
			{
				tokenPtr->typ = TT_DIVIDE;

				//TODO smazat
				/*if(read_char == '=')
					state = FM_DIVIDE_ASSIGN;*/
				if(read_char == '/')
					state = FM_COMMENT_SINGLELINE;
				else if(read_char == '*')
					state = FM_COMMENT_MULTILINE;
				else
				{
					ungetc(read_char, file_p);
					state = FM_END;
				}
			}	break;
			//-----------------------------------------------------------------------
			
			//TODO smazat
			/*case FM_DIVIDE_ASSIGN:
			{
				tokenPtr->typ = TT_ASSIGN_DIV;

				ungetc(read_char, file_p);
				state = FM_END;
			} break;*/
			//-----------------------------------------------------------------------
				
			case FM_COMMENT_SINGLELINE:
			{
				tokenPtr->typ = TT_UNDEFINED;

				if(read_char == NEW_LINE)
					state = FM_START;
			} break;
			//-----------------------------------------------------------------------
				
			case FM_COMMENT_MULTILINE:
			{
				tokenPtr->typ = TT_UNDEFINED;

				if(read_char == '*')
					state = FM_COMMENT_MULTILINE_END;
			} break;
			//-----------------------------------------------------------------------
				
			case FM_COMMENT_MULTILINE_END:
			{
				if(read_char == '/')
					state = FM_START;
				else
					state = FM_COMMENT_MULTILINE;
			} break;
			//-----------------------------------------------------------------------
				
			case FM_ASSIGN:
			{
				tokenPtr->typ = TT_ASSIGN;
				if(read_char == '=')
					state = FM_EQUAL;
				else
				{
					ungetc(read_char, file_p);
					state = FM_END;
				}
			} break;
			//-----------------------------------------------------------------------
				
			case FM_EQUAL:
			{
				tokenPtr->typ = TT_EQUAL;

				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
				
			case FM_NOT_EQUAL:
			{
				tokenPtr->typ = TT_NOT_EQUAL;
					
				if (read_char == '=')
				{
					state = FM_END;
				}
				else
				{
						//TODO: ERROR
				}
			} break;
			//-----------------------------------------------------------------------
					
			//TODO smazat		
			/*case FM_DOT:
			{
				tokenPtr->typ = TT_DOT;
					
				ungetc(read_char, file_p);
				state = FM_END;
			} break;*/
			//-----------------------------------------------------------------------
					
			case FM_COMMA:
			{
				tokenPtr->typ = TT_COMMA;
					
				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
				
			case FM_OR:
			{
				if (read_char == '|')
				{
					tokenPtr->typ = TT_OR;
					state = FM_END;	
				}
				else
				{
					//TODO ERROR
				}
				
			} break;
			//-----------------------------------------------------------------------
			
			case FM_AND:
			{
				if (read_char == '&')
				{
					tokenPtr->typ = TT_AND;
					state = FM_END;	
				}
				else
				{
					//TODO ERROR
				}
				
			} break;
			//-----------------------------------------------------------------------
					
			case FM_GREATER:
			{
				tokenPtr->typ = TT_GREATER;
					
				if (read_char == '=')
					state = FM_G_EQUAL;
				else if (read_char == ">")
				{
					state = FM_EXTRACTION;
				}
				else
				{
					ungetc(read_char, file_p);
					state = FM_END;
				}
			} break;
			//-----------------------------------------------------------------------
					
			case FM_G_EQUAL:
			{
				tokenPtr->typ = TT_EQUAL_GREATER;
					
				ungetc(read_char, file_p);
				state = FM_END;					
			} break;
			//-----------------------------------------------------------------------
					
			case FM_LESS:
			{
				tokenPtr->typ = TT_LESS;
					
				if (read_char == '=')
					state = FM_L_EQUAL;
				else if (read_char == '<')
				{
					T_Update(read_char);
					state = FM_INSERTION;
				}
				else
				{
					ungetc(read_char, file_p);
					state = FM_END;
				}
			} break;
			//---------------------------------------------------------------------
					
			case FM_L_EQUAL:
			{
				tokenPtr->typ = TT_EQUAL_LESS;
					
				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
					
			case FM_CODEWORD:
			{
				if (((read_char >= LETTER_A) && (read_char <= LETTER_Z))
					|| ((read_char >= CAPITAL_A) && (read_char <= CAPITAL_Z)))
				{
					T_Update(read_char);
				}
				else if (((read_char >= ZERO) && (read_char <= NINE))
					|| (read_char = '_'))
				{
					T_Update(read_char);
					state = FM_IDENTIFIER;
				}
				else
				{
					if (!IsKeyword())
					{
						state = FM_KEYWORDS;
					}
					else
					{
						state = FM_IDENTIFIER;
					}
					ungetc(read_char, file_p);
				}
			} break;
			//-----------------------------------------------------------------------
					
			case FM_IDENTIFIER:
			{
				if (((read_char >= LETTER_A) && (read_char <= LETTER_Z))
					|| ((read_char >= CAPITAL_A) && (read_char <= CAPITAL_Z))
					|| ((read_char >= ZERO) && (read_char <= NINE))
					|| (read_char = '_'))
				{
					T_Update(read_char);
				}
				else
				{
					tokenPtr->typ = TT_IDENTIFIER;
						
					ungetc(read_char, file_p);
					state = FM_END;
				}
			} break;
			//-----------------------------------------------------------------------
			
			case FM_KEYWORDS:
			{
				tokenPtr->typ = TT_KEYWORD;
				
				ungetc(read_char, file_p);
				state = FM_END;
			}
			//-----------------------------------------------------------------------
					
			case FM_EXTRACTION:
			{
				tokenPtr->typ = TT_EXTRACTION;
						
				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------	
					
			case FM_INSERTION:
			{
				tokenPtr->typ = TT_INSERTION;
						
				ungetc(read_char);
				state = FM_END;		
			} break;
			//-----------------------------------------------------------------------
			
			case FM_NUMBER:
			{
				if ((read_char >= ZERO) && (read_char <= NINE))
				{
					T_Update(read_char);
				}
				else if ((read_char == 'e') || (read_char == '.') || (read_char == 'E'))
				{
					T_Update(read_char);
					state = FM_DOUBLE;
				}
				else
				{
					if (!EndOfNumber(read_char))
					{
						state = FM_INTEGER;
						ungetc(read_char, file_p);
					}
					else
					{
						//TODO odchytávání chyb
					}
					
				}
			}
			//-----------------------------------------------------------------------
			
			case FM_INTEGER:
			{
				tokenPtr->typ = TT_INT;
				
				ungetc(read_char, file_p);
				state = FM_END;
			}
			//-----------------------------------------------------------------------
			
			case FM_DOUBLE:
			{
				if ((read_char > ZERO) && (read_char < NINE))
				{
					T_Update(read_char);
				}
				else
				{
					if (!EndOfNumber(read_char))
					{
						ungetc(read_char, file_p);
						state = FM_END;
					}
					else
					{
						// TODO ERROR
					}
				}
			}
			//-----------------------------------------------------------------------
			
			case FM_NUM_BASE:
			{
				switch (read_char)
				{
					case 'x':
						state = FM_HEX_NUM;
						break;
						
					case '0':
						state = FM_OCT_NUM;
						break;
						
					case 'b':
						state = FM_BIN_NUM;
						break;
						
					default:
						//TODO --ERROR
						 break;
				}
			} break;
			//-----------------------------------------------------------------------
			
			case FM_HEX_NUM:
			{
				tokenPtr->type = TT_HEX_NUM;
				
				if (((read_char >= LETTER_A) && (read_char <= LETTER_Z))
					|| ((read_char >= CAPITAL_A) && (read_char <= CAPITAL_Z))
					|| ((read_char >= ZERO) && (read_char <= NINE)))
				{
					T_Update(read_char);
				}
				else
				{
					ungetc(read_char, file_p);
					state = FM_END;
				}
			}
			//-----------------------------------------------------------------------
			
			case FM_OCT_NUM:
			{
				tokenPtr->typ = TT_OCT_NUM;
				
				// znaky '0' - '7'
				if ((read_char >= ZERO) && (read_char <= NINE-2))
				{
					T_Update(read_char);
				}
				else
				{
					ungetc(read_char, file_p);
					state = FM_END;
				}
			}
			//-----------------------------------------------------------------------
			
			case FM_BIN_NUM:
			{
				tokenPtr->typ = TT_BIN_NUM;
				
				// pouze znaky '0' a '1'
				if ((read_char == ZERO) || (read_char == ZERO+1))
				{
					T_Update(read_char);
				}
				else
				{
					ungetc(read_char, file_p);
					state = FM_END;
				}
			}
			//-----------------------------------------------------------------------
			
			case FM_STRING:
			{
				if (read_char == '"')
				{
					state = FM_END;
				}
				else if (read_char == '\')
				{
					state = FM_ESC_SQ;
				}
				else
				{
					T_Update(read_char);
				}
			}
			//-----------------------------------------------------------------------
			
			//TODO - dodělat escape sekvence a k tomu příslušící stavy
			case FM_ESC_SQ:
			{
				switch (read_char)
				{
					case 'n':
						;break;
					case '\':
						;break;
					case 't':
						;break;
					case 'x':
						;break;
				}
				
			}
			//-----------------------------------------------------------------------
			default:	//special case - zatim nezaregistrovany znaky/slova -> system je bude flusat po jednom ven;
			{
				tokenPtr->typ = TT_UNRECOGNIZED;

				if(!whiteSpace)
					T_Update(read_char);
				else
					state = FM_END;
			} break;
		}	//switch
	}	//while
	T_Finish(tokenPtr);
}	//T_Get
