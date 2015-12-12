#include "scanner.h"

static int keyword_type = 0;

static const char *key_words[KEYWORD_COUNT] = {"auto", "cin", "cout", "double",
 "else", "for", "if", "int", "return", "string", "bool", "do", "while",
 "true", "false",
 // VESTAVĚNÉ FUNKCE TAKÉ JAKO
 "length", "substr", "concat", "find", "sort"};

//Function prototypes - private
void T_Get(tTokenPtr tokenPtr);
int IsKeyword(void);
int EndOfNumber(char c);

void Scann(Deque tokenQueue)
{
#if DEBUG
	printf("Starting scanning source code\n");
	int scannedTokens = 0;
#endif
	int scann = 1;

	while(scann)
	{
		tTokenPtr token = T_Init();
		T_Get(token);

		D_PushBack(tokenQueue, token);
#if DEBUG
		scannedTokens++;
		printf("%s\n",tokenNames[token->typ]);
#endif
		if(token->typ == TT_EOF)
			scann = 0;
	}
#if DEBUG
	printf("Scanning done %d tokens done\n",scannedTokens);
#endif
}

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
			//-----------------------------------------------------------------------
			
			/////////////////////////////////////////////////////////////////////////
			// ROZPOZNÁNÍ NOVĚ PŘÍCHOZÍHO ZNAKU
			//-----------------------------------------------------------------------
			/*Stav FM_START rozpoznává první příchozí znak po ukončení předchozího
			tokenu*/
			/////////////////////////////////////////////////////////////////////////
			case FM_START:
				switch (read_char)
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
				
					case ';':
						state = FM_SEMICOLON;
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
						
					case '=':
						state = FM_ASSIGN;
						break;
						
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
						state = FM_IDENTIFIER;
						break;
					
					case '!':
						state = FM_NOT_EQUAL;
						break;
						
					case '\\':
						state = FM_NUM_BASE;
						break;
						
					case '\"':
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
							state = FM_ZERO;
						}
						// když je to znak 1-9
						else if ((read_char >= ZERO+1) && (read_char <= NINE))
						{
							state = FM_NUMBER;
						}
						else
						{
							mistake(ERR_LEX, "Znak není povolen v rámci jazyka IFJ15!\n");
						}
						T_Update(read_char);
					}
					break;
						
				}	//switch v case FM_START
			break;
				
			/////////////////////////////////////////////////////////////////////////
			// DALŠÍ STAVY 
			/////////////////////////////////////////////////////////////////////////
			
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
			
			case FM_SEMICOLON:
			{
				tokenPtr->typ = TT_SEMICOLON;

				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
				
			case FM_STAR:
			{
				tokenPtr->typ = TT_STAR;

				ungetc(read_char, file_p);
				state = FM_END;
			} break;
			//-----------------------------------------------------------------------
					
			case FM_PLUS:
			{
				if (read_char == '+')
				{
					state = FM_INCREMENT;
				}
				else
				{
					tokenPtr->typ = TT_PLUS;
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
			}break;
			//-----------------------------------------------------------------------
				
			case FM_MINUS:
			{
				if (read_char == '-')
				{
					state = FM_DECREMENT;
				}
				else
				{
					tokenPtr->typ = TT_MINUS;
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
				
			case FM_DIVIDE:
			{
				if(read_char == '/')
					state = FM_COMMENT_SINGLELINE;
				else if(read_char == '*')
					state = FM_COMMENT_MULTILINE;
				else
				{
					tokenPtr->typ = TT_DIVIDE;
					ungetc(read_char, file_p);
					state = FM_END;
				}
			}	break;
			//-----------------------------------------------------------------------
				
			case FM_COMMENT_SINGLELINE:
			{
				//tokenPtr->typ = TT_UNDEFINED;

				if(read_char == NEW_LINE)
					state = FM_START;
			} break;
			//-----------------------------------------------------------------------
				
			case FM_COMMENT_MULTILINE:
			{
				//tokenPtr->typ = TT_UNDEFINED;

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
				if(read_char == '=')
					state = FM_EQUAL;
				else
				{
					tokenPtr->typ = TT_ASSIGN;
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
				if (read_char == '=')
				{
					tokenPtr->typ = TT_NOT_EQUAL;
					state = FM_END;
				}
				else
				{
					mistake(ERR_LEX, "V kódu se nachází samotný znak \"!\" \n");
				}
			} break;
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
					mistake(ERR_LEX, "V kódu je samotný znak \"&\" \n");
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
					mistake(ERR_LEX, "V kódu je samotná znak \"|\" \n");
				}
				
			} break;
			//-----------------------------------------------------------------------
					
			case FM_GREATER:
			{		
				if (read_char == '=')
					state = FM_G_EQUAL;
				else if (read_char == '>')
				{
					state = FM_EXTRACTION;
				}
				else
				{
					tokenPtr->typ = TT_GREATER;
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
				if (read_char == '=')
					state = FM_L_EQUAL;
				else if (read_char == '<')
				{
					state = FM_INSERTION;
				}
				else
				{
					tokenPtr->typ = TT_LESS;
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
				if ((read_char >= LETTER_A) && (read_char <= LETTER_Z))
				{
					T_Update(read_char);
				}
				else if (((read_char >= ZERO) && (read_char <= NINE))
					|| ((read_char >= CAPITAL_A) && (read_char <= CAPITAL_Z))
					|| (read_char == '_'))
				{
					T_Update(read_char);
					state = FM_IDENTIFIER;
				}
				else
				{
					if (IsKeyword())
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
					|| (read_char == '_'))
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
				tokenPtr->typ = keyword_type;
				
				keyword_type = 0;
				
				ungetc(read_char, file_p);
				state = FM_END;
			}break;
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
						
				ungetc(read_char, file_p);
				state = FM_END;		
			} break;
			//-----------------------------------------------------------------------
			
			case FM_ZERO:
			{
				if (EndOfNumber(read_char))
				{
					tokenPtr->typ = TT_INT;
					T_Update('0');
					ungetc(read_char, file_p);
					state = FM_END;
				}
				else if (read_char == '0')
				{
					continue;
				}
				else
				{
					state = FM_NUMBER;
					ungetc(read_char, file_p);
				}
			}break;
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
					if (EndOfNumber(read_char))
					{
						state = FM_INT;
						ungetc(read_char, file_p);
					}
					else
					{
						mistake(ERR_LEX, "Za číslem není EndOfNumber!\n");
					}
					
				}
			}break;
			//-----------------------------------------------------------------------
			
			case FM_INT:
			{
				tokenPtr->typ = TT_INT;
				
				ungetc(read_char, file_p);
				state = FM_END;
			}break;
			//-----------------------------------------------------------------------
			
			case FM_DOUBLE:
			{
				if ((read_char > ZERO) && (read_char < NINE))
				{
					T_Update(read_char);
				}
				else
				{
					if (EndOfNumber(read_char))
					{
						tokenPtr->typ = TT_DOUBLE;
						ungetc(read_char, file_p);
						state = FM_END;
					}
					else
					{
						mistake(ERR_LEX, "Chyba při čtení double!\n");
					}
				}
			}break;
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
						mistake(ERR_LEX, "Chybný BASE!\n");
						break;
				}
			} break;
			//-----------------------------------------------------------------------
			
			case FM_HEX_NUM:
			{
				if (((read_char >= LETTER_A) && (read_char <= (LETTER_A + 5)))
					|| ((read_char >= CAPITAL_A) && (read_char <= (CAPITAL_A + 5)))
					|| ((read_char >= ZERO) && (read_char <= NINE)))
				{
					T_Update(read_char);
				}
				else
				{
					tokenPtr->typ = TT_HEX_NUM;
					ungetc(read_char, file_p);
					state = FM_END;
				}
			}break;
			//-----------------------------------------------------------------------
			
			case FM_OCT_NUM:
			{
				// znaky '0' - '7'
				if ((read_char >= ZERO) && (read_char <= NINE-2))
				{
					T_Update(read_char);
				}
				else
				{
					tokenPtr->typ = TT_OCT_NUM;
					ungetc(read_char, file_p);
					state = FM_END;
				}
			}break;
			//-----------------------------------------------------------------------
			
			case FM_BIN_NUM:
			{
				// pouze znaky '0' a '1'
				if ((read_char == ZERO) || (read_char == ZERO+1))
				{
					T_Update(read_char);
				}
				else
				{
					tokenPtr->typ = TT_BIN_NUM;
					ungetc(read_char, file_p);
					state = FM_END;
				}
			}break;
			//-----------------------------------------------------------------------
			
			case FM_STRING:
			{
				if (read_char == '\"')
				{
					tokenPtr->typ = TT_STRING;
					state = FM_END;
				}
				else if (read_char == '\\')
				{
					state = FM_ESC_SQ;
				}
				else
				{
					T_Update(read_char);
				}
			}break;
			//-----------------------------------------------------------------------
			
			case FM_ESC_SQ:
			{
				switch (read_char)
				{
					case 'n': 
					{
						state = FM_STRING;
						T_Update('\n');
					} break;
					
					case 't': 
					{
						state = FM_STRING;
						T_Update('\t');
					} break;
					
					case '\\': 
					{
						state = FM_STRING;
						T_Update('\\');
					} break;
					
					case '\"': 
					{
						state = FM_STRING;
						T_Update('\"');
					} break;
					default: 
					{
						T_Update(read_char);
						state = FM_STRING;
					} break;
				}
			} break;
			//-----------------------------------------------------------------------
			
			default:	//special case - zatim nezaregistrovany znaky/slova -> system je bude flusat po jednom ven;
			{
				mistake(ERR_LEX, "Token není povolen v rámci jazyka IFJ15!\n");
				/*tokenPtr->typ = TT_UNDEFINED;

				if(!whiteSpace)
					T_Update(read_char);
				else
					state = FM_END;*/
			} break;
		}	//switch
	}	//while
	T_Finish(tokenPtr);
}

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
		return 0;
	}
	else
	{
		for (int i = 0; i < KEYWORD_COUNT; i++)
		{
			if (strlen(key_words[i]) == strlen(token_content))
			{
				if (!strcmp(key_words[i], token_content))
				{
					keyword_type = i + KEYWORD_SHIFT;
					return keyword_type;
				}
			}
		}
		return 0;
	}
}

int EndOfNumber(char c)
{
	for (int i = 0; i < EON_COUNT; i++)
	{
		if (c == eon[i])
			return 1;
	}
	return 0;
}
