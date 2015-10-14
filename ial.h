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



#endif //IAL_Header
