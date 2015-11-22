#include "ial.h"

//TODO: presunout implementaci binarniho stromu sem

#if tohle_to_tu_nema_vubec_co_byt_potreba_preimplementovat_a_zakryt

int find (char *target, int tsize, char *pattern, int psize)
{
	int i;
	int *pi = prefix_to_FIND(pattern, psize);
	int k = -1;
	if (!pi)
		{				//chyba v pridelovaní pamete v compute_prefix_function
		#if DEBUG
			char message[] = {"mistake appeared in previous function, in allocating memory\n"};
			mistake (ERR_INTERN,message);
		#else
			mistake (ERR_INTERN);
		#endif
		}
	for (i = 0; i < tsize; i++) {
		while (k > -1 && pattern[k+1] != target[i])
			k = pi[k];
		if (target[i] == pattern[k+1])
			k++;
		if (k == psize - 1) {
			MM_Free(pi);		//kontrola
			return i-k;			//vracia poziciu
		}
	}
	MM_Free(pi);				//kontrola

	#if DEBUG			// chyba , nenaslo to zhodu
		char message[] = {"no results found\n"};
		mistake (ERR_RUN_OTH,message);
	#else
		mistake (ERR_RUN_OTH);
	#endif
}

#endif
