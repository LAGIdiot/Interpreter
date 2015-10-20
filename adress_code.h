enum operatinType{
	OT_ADD
};

typedef struct AC_item{
	int operation;
	void *source1;
	void *source2;
	void *destination;
}AC_item, *AC_itemPtr;

typedef struct AC_listItem{
	AC_itemPtr data;
	struct AC_listItemPtr Next;
	struct AC_listItemPtr Prev;
}AC_listItemStruc, *AC_listItemPtr;

typedef struct AC_table{
	AC_listItemPtr First;
	AC_listItemPtr Last;
	AC_listItemPtr Active;
}AC_table;


void AC_T_Init();
void AC_T_Add(AC_itemPtr itemPtr);
void AC_T_Remove(AC_itemPtr itemPtr);
void AC_T_Destroy();

void AC_T_Activate(AC_itemPtr itemPtr);
void AC_T_ActiveMoveUp();
void AC_T_ActiveMoveDown();

