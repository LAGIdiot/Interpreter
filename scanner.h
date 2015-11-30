#ifndef SCANNER_Header
#define SCANNER_Header

#include <stdio.h>

#include "errors.h"
#include "token.h"
#include "deque.h"

#define TOKEN_COUNT 30

//Externs
extern FILE * file_p;

//Functions
void Scann(Deque tokenQueue);

#if DEBUG
static const char *tokenNames[TOKEN_COUNT] =
	{"UNDEFINED", "EOF", "SEMICOLN", "STAR", "PLUS", "MINUS", "DEVIDE", "ASSIGN", "EQUEAL", "EQUAL_LESS",
		"EQUAL_GREATER","EQUEAL_NOT", "LESS", "GREATER", "COMMA", "PAR_L", "PAR_R", "BRACE_L", "BRACE_R", "INSERTION",
		"EXTRACTION", "INT", "DOUBLE", "CHAR", "KEYWORLD_STRING", "KEYWORLD_INT", "KEYWORLD_DOUBLE", "KEYWORLD_CHAR", "KEYWORLD_STRING", "KEYWORLD_VOID",
		};
#endif

#endif
