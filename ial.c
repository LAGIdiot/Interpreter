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
		*Root = MM_Malloc(sizeof(struct binaryTree));

        (*Root)->data = symbol;
        (*Root)->lChild = NULL;
        (*Root)->rChild = NULL;

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
