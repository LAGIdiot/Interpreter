#include <stdio.h>
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
		
		// ROZPOZNÁVÁNÍ NAČTENÉHO ZNAKU
		//-----------------------------------------------------------------------
		/* větvící struktura rozlišuje jeden načtený znak a následně nastavuje
		aktuální stav konečného automatu.*/
		//-------------------------------------------------------------------------
		switch (read_char)
		{
			case ';':
			{
				state = FM_SEMICON;
			}
			
			case '+': 
			{
				if (state == FM_PLUS)
				{
					state = FM_INCREMENT;
				}
				else
				{
					state = FM_PLUS;
				}
			} break;
			
			case '-':
			{
				if (state == FM_MINUS)
				{
					state = FM_DECREMENT;
				}
				else
				{
					state = FM_MINUS;
				}
			} break;
			
			case '*':
			{
				if (state == FM_DIVISION)
				{
					state = FM_COMMENT_MULTILINE;
				}
				else if (state == FM_COMMENT_MULTILINE)
				{
					
				}
				else
				{
					state = FM_STAR;
				}
			} break;
			
			case '/':
			{
				if (state == FM_DIVISION)
				{
					state = FM_COMMENT_SINGLELINE;
				}
				else
				{
					state = FM_DIVISION;
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
			}
			
			// ROZPOZNÁVÁNÍ "BĚŽNÝCH" ZNAKŮ
			default:
			{
				if (((read_char >= CAPITAL_A) && (read_char <= CAPITAL_Z))
					|| ((read_char >= LETTER_A) && (read_char >= LETTER_Z)))
				{
					switch ()
					{
						case: ;break;
						default: ;break;
					}
				}

				else if ((read_char >= ZERO) && (read_char <= NINE))
				{
					if (state == FM_INTEGER)
					{
							
					}
					else if (state == FM_DOUBLE)
					{
							
					}
					else
					{
							
					}
				}
			}
			
			// PŘEPÍNÁNÍ STAVŮ AUTOMATU A UKONČOVÁNÍ TOKENU
			//-----------------------------------------------------------------------
			/* Na základě stavu z předchozího switche se rozhodne, zda ukončit token
			nebo načítat další znak*/
			//-----------------------------------------------------------------------
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
					if (read_char == "*")
					{
						if ((read_char = fgetc(file_p)) == '/')
						{
							state = FM_START;
						}
					}
				}
				
				case FM_SEMICON:
				{
					// T_Update(lex_token, read_char);
					state = FM_END;
				}break;
				
				case FM_ASSIGN:
				{
					
				}break;
				
				case FM_EQUAL:
				{
					// T_Update(lex_token, read_char);
					state = FM_END;
				}
				
				case FM_PLUS:
				{
					
				}
				default: ;break;
			}
		}
	}
	
	return *lex_token;
}
