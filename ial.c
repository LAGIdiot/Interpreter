#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ial.h"
#include "errors.h"
#include "memory_manager.h"


int *compute_prefix_function (char *pattern, int psize)
{
	int k = -1;
	int i = 1;
	int * pi = MM_Malloc(sizeof(int)*psize);			// kontrola
	if (!pi)
		return NULL;

	pi[0] = k;
	for (i = 1; i < psize; i++) {
		while (k > -1 && pattern[k+1] != pattern[i])
			k = pi[k];
		if (pattern[i] == pattern[k+1])
			k++;
		pi[i] = k;
	}
	return pi;
}

int find (char *target, int tsize, char *pattern, int psize)
{
	int i;
	int *pi = compute_prefix_function(pattern, psize);
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
