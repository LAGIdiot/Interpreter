#ifndef IAL_Header
#define IAL_Header

#include <stdio.h>

#include "errors.h"
#include "memory_manager.h"
#include "str.h"
#include "symbol_table.h"

int find(string s, string search);

string sort(string s);

//Funkce pro praci se stromem

///////////
// struktura binaryTree ( struktura stromu )
///////////
typedef struct binaryTree
{
	symbolPackagePtr data;
	struct binaryTree * rChild; //pravy potomok uzlu
	struct binaryTree * lChild; //lavy potomok uzlu
} *nodePtr;

///////////
// funkcia treeInit ( inicializuje strom pred jeho použitím )
//nodePtr* RootPtr - koren stromu ktory sa inicializuje
///////////
void treeInit (nodePtr*);

///////////
// funkcia nodeInsert ( vytvara uzol, alokuje pamat a rozhoduje o velkosti symbolov, podla nich vytvara laveho/praveho potomka )
//nodePtr* Root - uzol podla ktoreho sa vklada dalsi uzol
//bkey key - nazov podla ktoreho sa uklada uzol do stromo
//symbolItemStruct symbol - symbol ktory sa do stromu vklada
///////////
void nodeInsert (nodePtr* , symbolPackagePtr);

///////////
// funkcia deleteTree ( vymazava strom a uvolnuje pamat )
//nodePtr * Root - strom ktory sa vymazava
///////////
void deleteTree(nodePtr*);

///////////
// funkcia searchNode ( vyhladavy dany symbol v strome )
//nodePtr Root - strom v ktorom sa vyhladava
//bKey key - kluc resp. nazov podla ktoreho vyhladava
///////////
nodePtr searchNodeBySymbol (nodePtr *Root, symbolPackagePtr symbol);
nodePtr searchNodeByKey (nodePtr *Root, string key);

#endif //IAL_Header
