#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *file_p;
	char readed_char;
	
	if (argc != 2)
	{
		//VÝPIS ERRORU
	}
	else
	{
		file_p = fopen(argv[1], "r");
		if (!file_p)
		{
			//VÝPIS CHYBY
		}
		else
		{
			while (readed_char = fgetc(file_p) != EOF)
			{
				// NEJDŘÍV IF , KTEREJ ROZDĚLUJE NA ČÍSLA A PÍSMENA
				// SADA BOOLEANŮ, KTERÁ PŘEPÍNÁ, CO MÁ DĚLAT
				// DÁT MÍSTO ÚVOZOVEK APOSTROFY
			
				switch (readed_char)
				{
					case '\t': ;break;
					case '\n': ;break;
					case ' ': ;break;
					
					case '#': //NAČÍTÁNÍ KNIHOVEN, udělat cyklus, který načte knihovnu do prvního výskytu ">"?
						;break;
					case '{': //ZAVOLAT FCI PRO KONTROLU HRANATÝCH ZÁVOREK
						;break;
					case '}': //ZAVOLAT FCI PRO KONTROLU HRANATÝCH ZÁVOREK
						;break;
					case '(': //ZAVOLAT FCI PRO KONTROLU KULATÝCH ZÁVOREK
						;break;
					case ')': //ZAVOLAT FCI PRO KONTROLU KULATÝCH ZÁVOREK
						;break;
						
					// Jak rozdělovat lexémy, když tam nemusí být mezery?
						
					/*
						ZPRACOVÁNÍ PÍSMEN?
					*/
					
					/*
						ZPRACOVÁNÍ ČÍSLIC?
					*/
					
					// ZÁSOBNÍK ZNAMÉNEK
					case '=':
						;break;
					case '+':
						;break;
					case '-':
						;break;
					case '*':
						;break;
					case '!':
						;break;
					

					default: ;break;
				}
			}
		}
	}
	
	return 0;
}
