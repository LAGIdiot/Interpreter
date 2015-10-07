#ifndef ERRORS_H
#define ERRORS_H

enum mistakes {
    ERR_LEX = 1,
    ERR_SYNTAX = 2,
    ERR_SEM_UND = 3,
    ERR_SEM_COMP = 4,
    ERR_SEM_TYP = 5,
    ERR_SEM_OTH = 6,
    ERR_LOAD = 7,
    ERR_INIT = 8,
    ERR_ZERO = 9,
    ERR_RUN_OTH = 10,
    ERR_INTERN = 99
};

void mistake (int param1);

#if DEBUG
void mstk_debug (int param1, int param2, int param3);
#endif

#endif
