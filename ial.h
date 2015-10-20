#ifndef IAL_Header
#define IAL_Header

///////////
// funkcia *compute_prefix_function ( urobi si tabulku pismen  a nastavi hodnoty, vytvori pamet pre tabulku )
//char *pattern - pattern je hladani vzor , pole
//int psize - dlzka vzoru
///////////
int *compute_prefix_function(char *pattern, int psize);

///////////
// funkcia kmp ( algoritmus na vyhladavanie v retazcoch podretazec, vzor, vrati poziciu prveho vyskytu prveho pismenka vzoru )
//char *target - target je cielovy retazec, pole
//int tsize - dlzka cieloveho retazca, pola
//char *pattern - pattern je hladani vzor , pole
//int psize - dlzka vzoru
///////////
int kmp(char *target, int tsize, char *pattern, int psize);

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
