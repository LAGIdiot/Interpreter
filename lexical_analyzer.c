#include <stdio.h>
#include <string.h>
#include "token.c"
#include "lexical_analyzer.h"

FILE *file_p;
tTokenPtr *lex_token;

tTokenPtr getToken()
{
	//T_Init();
	int state = FM_START;
	
	while (state != FM_END)
	{
		read_char = fgetc(file_p);
		
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
					T_Update(lex_token, read_char);
					state = FM_DOUBLE;
				}
			}
			case '_':
			{
				if (state == FM_START)
				{
					state = FM_VARIABLE;
				}
				
				T_Update(lex_token, read_char);
			}
			
			case ';':
			{
				T_Update(lex_token, read_char);
				state = FM_SEMICON;
			}
			
			case '+': 
			{
				if (state == FM_PLUS)
				{
					state = FM_INCREMENT;
				}
				else if (state == FM_START)
				{
					state = FM_PLUS;
				}
				
				T_Update(lex_token, read_char);
			} break;
			
			case '-':
			{
				if (state == FM_MINUS)
				{
					state = FM_DECREMENT;
				}
				else if(state == FM_START)
				{
					state = FM_MINUS;
				}
				
				T_Update(lex_token, read_char);
			} break;
			
			case '*':
			{
				if (state == FM_DIVISION)
				{
					state = FM_COMMENT_MULTILINE;
				}
				else if (state == FM_START)
				{
					state = FM_STAR;
					T_Update(lex_token, read_char);
				}
			} break;
			
			case '/':
			{
				if (state == FM_DIVISION)
				{
					state = FM_COMMENT_SINGLELINE;
				}
				else if (state == FM_START)
				{
					state = FM_DIVISION;
					T_Update(lex_token, read_char);
				}
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
				
				T_Update(lex_token, read_char);
			}
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
							ungetc(c, file_p);	
						} break;
						
						default:
						{
							T_Update(lex_token, read_char);
							/////////////////////////////////////////////////////////////////
							// POROVNÁNÍ OBSAHU TOKENU S KLÍČOVÝMI SLOVY
							/* --------------------------------------------------------------
								 Podmínka testuje, zda se obsah tokenu nerovná jednomu z
								 klíčových slov IFJ15. Následně dochází ke kontrole, zda se
								 nejedná o proměnnou. Jakmile řetězec pokračuje, jde o proměnnou,
								 pokud ne, jde o klíčové slovo a je přečtený znak vrácen souboru.
							*////////////////////////////////////////////////////////////////
							if ((strlen(lex_token->data) == 2) || (strlen(lex_token->data) == 3)
								|| (strlen(lex_token->data) == 4) || (strlen(lex_token->data) == 5))
							{
								if ((strcmp(lex_token->data, "auto") != 0) || (strcmp(lex_token->data, "cin") != 0)
									|| (strcmp(lex_token->data, "cout") != 0) || (strcmp(lex_token->data, "double") != 0)
									|| (strcmp(lex_token->data, "else") != 0) || (strcmp(lex_token->data, "for") != 0)
									|| (strcmp(lex_token->data, "if") != 0) || (strcmp(lex_token->data, "int") != 0)
									|| (strcmp(lex_token->data, "return") != 0) || (strcmp(lex_token->data, "string") != 0))
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
						T_Update(lex_token, read_char);
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
				}
				
				case FM_COMMENT_MULTILINE:
				{
					if (read_char == '*')
					{
						if ((read_char = fgetc(file_p)) == '/')
						{
							state = FM_START;
						}
					}
				}
				
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
				} braek;
				
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
	}
	
	return *lex_token;
}
