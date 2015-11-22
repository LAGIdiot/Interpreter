#ifndef IAL_Header
#define IAL_Header

#include <stdio.h>

#include "errors.h"
#include "memory_manager.h"
#include "str.h"

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
// struktura binaryTree ( struktura stromu )
///////////
typedef struct binaryTree
{
int data;
struct binaryTree * rChild; //pravy potomok uzlu
struct binaryTree * lChild; //lavy potomok uzlu
} *nodePtr;

/*
///////////
// funkcia createNode ( vytvara uzol, alokuje pamat a rozhoduje o velkosti tokenov, podla nich vytvara laveho/praveho potomka )
//node * tree - koren stromu
//Token *tTokenPtr - hodnota tokenu
///////////
void createNode(node * tree, Token *tTokenPtr);

///////////
// funkcia deleteTree ( vymazava strom a uvolnuje pamat )
//node tree - strom
///////////
void deleteTree(node tree);

///////////
// funkcia node search ( vyhladavy dany token v strome )
//node * tree - strom
//Token *tTokenPtr - hodnota tokenu
///////////
node* search(node * tree, Token *tTokenPtr);

///////////
// funkcia treeCreation ( povodny main, rozhoduje o tom ktora funkcie bude kedy zavolana/mozne vymazat a zahrnut v main )
///////////
void treeCreation();
*/
#endif //IAL_Header
