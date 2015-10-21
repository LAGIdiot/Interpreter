#ifndef SA_Header
#define SA_Header

#include <stdio.h>

#include "errors.h"
#include "str.h"

enum SA_tree_id_type{
	PROTOTYP,
	FUNCTION,
	MAIN
};

typedef struct SA_tree_root{

};

typedef struct SA_tree_node{
	int type;
	string key; //nazev funkce
	string data; //zde je ulozen navratovy typ a typ parametru funkce
};

void parse();

#endif //SA_Header
