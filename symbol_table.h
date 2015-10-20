enum symbolType{
	ST_INT,
	ST_DOUBLE,
	ST_CHAR,
	ST_STRING
}symbols;

typedef struct symbolItem{
	uint key;
	int sybol;
	struct symbolItemPtr nextItem;
}symbolItem, *symbolItemPtr;

#if DEBUG
typedef struct symbolHead{
	struct symbolItemPtr First;
	int counter;
};
#else
typedef struct symbolHead{
	struct symbolItemPtr First;
};
#endif
