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


#if tohle_to_tu_nema_vubec_co_byt_potreba_preimplementovat_a_zakryt

///////////
// funkcia (kmp) find ( algoritmus na vyhladavanie v retazcoch podretazec, vzor, vrati poziciu prveho vyskytu prveho pismenka vzoru )
//char *target - target je cielovy retazec, pole
//int tsize - dlzka cieloveho retazca, pola
//char *pattern - pattern je hladani vzor , pole
//int psize - dlzka vzoru
///////////
int find(char *target, int tsize, char *pattern, int psize);

#endif
///////////
// struktura bKey ( struktura klucu char pre vyhladavanie v strome )
///////////
typedef char *bKey;

///////////
// struktura binaryTree ( struktura stromu )
///////////
typedef struct binaryTree
{
char key;
symbolItemStruct data;
struct binaryTree * rChild; //pravy potomok uzlu
struct binaryTree * lChild; //lavy potomok uzlu
} *nodePtr;

///////////
// funkcia treeInit ( inicializuje strom pred jeho použitím )
//nodePtr* RootPtr - koren stromu ktory sa inicializuje
///////////
void treeInit (noodePtr*)

///////////
// funkcia nodeInsert ( vytvara uzol, alokuje pamat a rozhoduje o velkosti symbolov, podla nich vytvara laveho/praveho potomka )
//nodePtr* Root - uzol podla ktoreho sa vklada dalsi uzol
//bkey key - nazov podla ktoreho sa uklada uzol do stromo
//symbolItemStruct symbol - symbol ktory sa do stromu vklada
///////////
void nodeInsert (nodePtr* , bKey, symbolItemStruct)

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
nodePtr searchNode(nodePtr, bKey);


#endif //IAL_Header
