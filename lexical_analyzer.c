#include <stdio.h>

#include "lexical_analyzer.h" // své knihovny do uvozovek
#include "ial.h"

//KLÍČOVÁ SLOVA
const char *key_words[10] = {"auto", "cin", "cout", "double", "else", "for", "if", "int", "return", "string"};
/*,"bool", "do", "while", "true", "false"*/

void T_Get(tTokenPtr token)
{
	fm_states state = FM_START;
	int read_char;
	
	int comment_variant = 0; //defaultne nastaveno na nula (aby prekladac nedava  zbytecne warningy), stejne dojde drive k zapisu nez ke cteni
	extern FILE *file_p;

	while (state != FM_END)
	{
		switch (state)
		{
			case FM_START:
			{
				if ((read_char = fgetc(file_p)) != EOF)
				{
					if (((read_char >= CAPITAL_A) && (read_char <= CAPITAL_Z))
						|| ((read_char >= LETTER_A) && (read_char >= LETTER_Z)))
							{
							
							}
				
				//JE ZNAK ČÍSLO?
					else if ((read_char >= ZERO) && (read_char <= NINE))
					{
								
					}
				
				//JE ZNAK BÍLÝ ZNAK?
					else if ((read_char == TAB) || (read_char == NEW_LINE)
						|| (read_char == SPACE))
					{
							
					}
					
					else
					{
						switch (read_char)
						{
							case '#': 
								;break;
							case '{':
								;break;
							case '}':
								;break;
							case '(':
								;break;
							case ')':
								;break;
							case '=':
								;break;
							case '+': state = FM_PLUS;
								;break;
							case '-': state = FM_MINUS;
								;break;
							case '*': state = FM_STAR;
								;break;
							case '/': state = FM_DIVIDE;
								;break;
							case '!':
								;break;
							case ';': state = FM_SEMICON;
								;break;
								
							default: ;
						}
					}	
				}
					
				else
				{
					state = FM_END;
				}	
			}break;
			
			
			//ZPRACOVÁNÍ KOMENTÁŘŮ
			/*Úsek nejprve načte další znak a následně ve zvolené větvi z FM_DIVIDE
			dojde ke zjištění, zda jde o konec komentáře. Pokud ne, dojde k breaku
			a FM_COMMENT je zavolán opět a načte se další znak. Je*/
			case FM_COMMENT:
			{			
				//Jednořádkový
				if (!comment_variant)
				{
					read_char = fgetc(file_p);
					if (read_char == '/') //jednořádkový komentář může být rozšířen pomocí "\"
					{
						fgetc(file_p); //znak konce řádku se zahodí, protože komentář pokračuje na druhém řádku
					}
					else if (read_char == '\n')
					{
						state = FM_START;
					}	
				}
				
				//Víceřádkový
				else if(comment_variant)
				{
					if (read_char == '*')
					{
						read_char = fgetc(file_p);
						if (read_char == '/') //načte ještě jeden znak, pokud nejde o "/",\
						tak nám nevadí, že se načte v dalším cyklu až další znak, \
						protože jsou pro nás posloupnosti "*" a "něco" nepodstatné kromě "*" a "*"
						{
							state = FM_START;
						}
						else if (read_char == '*')
						{
							//Neprovede se žádná operace, kdyby náhodou za sadou "*" bylo "/"
						}
						else
						{
							read_char = fgetc(file_p);
						}
					}
				}
			}break;
			
			case FM_KEYWORDS:
			{
			
			}break;
			
			case FM_VARIABLE:
			{
			
			}break;
			
			case FM_SEMICON:
			{
			
			}break;
			
			case FM_STRING:
			{
			
			}break;
			
			case FM_ESC_SQ:
			{
			
			}break;
			
			//ZNAK DĚLENO, PŘESMĚROVÁNÍ NA KOMENTÁŘE
			/*Prozatím vyřešeno jen přesměrování na komentáře,
			první varianta -> jednořádkové komentáře
			druhá varianta -> víceřádkové*/
			//POZDĚJI PŘIBUDOU OSTATNÍ OPERACE
			case FM_DIVIDE:
			{
				if ((read_char = fgetc(file_p)) == '/')
				{
					comment_variant = 0;
				}
				else if ((read_char = fgetc(file_p)) == '*')
				{
					comment_variant = 1;
				}
			}break;
			
			case FM_STAR:
			{
			
			}break;
			
			case FM_PLUS:
			{
			
			}break;
			
			case FM_MINUS:
			{
			
			}break;
			
			case FM_DOT:
			{
			
			}break;
			
			case FM_EQUAL:
			{
			
			}break;
			
			// RELAČNÍ OPERÁTORY
			//-----------------------------------------------------------------------
			case FM_ASSIGN:
			{
			
			}break;
			
			case FM_GREATER:
			{
			
			}break;
			
			case FM_LESS:
			{
			
			}break;
			case FM_G_EQUAL:
			{
			
			}break;
			
			case FM_L_EQUAL:
			{
			
			}break;
			
			case FM_NOT_EQUAL:
			{
			
			}break;
			
			case FM_PERC:
			{
			
			}break;
			
			case FM_COMMA:
			{
			
			}break;
			
			case FM_PIPE:
			{
			
			}break;
			
			/* DOBROVOLNÉ
			case FM_PLUS2 ;break;
			case FM_MINUS2 ;break;
			case FM_BOOL_ ;break;
			*/
			
			default: ;break;
		}
	}
}
