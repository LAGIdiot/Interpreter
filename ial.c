#include "ial.h"

void treeInit (nodePtr *Root)
{
	*Root = NULL;
}

nodePtr searchNodeBySymbol (nodePtr *Root, symbolPackagePtr symbol)
{

	if(Root != NULL)
	{
		int i = ST_Compare((*Root)->data, symbol);
		if(i == 0)
			return *Root;
		else if(i < 0)
			return searchNodeBySymbol(&(*Root)->lChild, symbol);
		else
			return searchNodeBySymbol(&(*Root)->rChild, symbol);
	}
	else
		return NULL;
}

nodePtr searchNodeByKey (nodePtr *Root, string key)
{
	if(Root != NULL)
	{
		int i = strCompare((*Root)->data->key, key);
		if(i == 0)
			return *Root;
		else if(i < 0)
			return searchNodeByKey(&(*Root)->lChild, key);
		else
			return searchNodeByKey(&(*Root)->rChild, key);
	}
	else
		return NULL;
}

nodePtr nodeInsert (nodePtr* Root, symbolPackagePtr symbol)
{	
	if(*Root == NULL)
	{
		nodePtr node = MM_Malloc(sizeof(struct binaryTree));
		node->data = symbol;
		node->lChild = NULL;
		node->rChild = NULL;

		*Root = node;

        return *Root;
	}
	else
	{
		int i = ST_Compare((*Root)->data, symbol);
		if(i < 0)
		{
			return nodeInsert(&(*Root)->lChild, symbol);
		}
		else if(i > 0)
		{
			return nodeInsert(&(*Root)->rChild,symbol);
		}
		else 
		{
			(*Root)->data = symbol;
			return *Root;
		}
	}
}

void deleteTree (nodePtr *RootPtr)
{
	if(*RootPtr != NULL)
	{
		deleteTree (&(*RootPtr)->lChild);
		deleteTree (&(*RootPtr)->rChild);
		MM_Free(*RootPtr);
		*RootPtr = NULL;
	}
}

int find(string s, string search)
{
	int i	, k = -1, tsize = s->length , psize = search->length ;
	int *pi = prefix_to_FIND(search);
	if (!pi)
		{				//chyba v pridelovaní pamete v compute_prefix_function
    printf("error\n");
		}
	for (i = 0; i < tsize; i++) {
		while (k > -1 && search->str[k+1] != s->str[i])
			k = pi[k];
		if ( s->str[i] == search->str[k+1])
			k++;
		if (k == psize - 1) {
			MM_Free(pi);		//kontrola
			return i-k;			//vracia poziciu
		}
	}
	MM_Free(pi);				//kontrola
}
