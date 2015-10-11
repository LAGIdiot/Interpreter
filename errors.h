#ifndef ERRORS_Header
#define ERRORS_Header

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

#if DEBUG
	void mistake (int errCode, const char *message);
#else
	void mistake (int errCode);
#endif //DEBUG

#endif //ERRORS_Header
