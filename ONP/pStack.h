#ifndef _PSTACK_H
#define _PSTACK_H


typedef struct tagStackItem {
	char        cKey;
	tagStackItem* pNext;
} StackItem;


void ppush( char c, StackItem** pStack );
char ppop( StackItem** pStack );
char ptop( StackItem* pStack );
void pdel( StackItem** pStack );
int pisEmpty(StackItem* pStack);
void pEmptyStack( StackItem** pStack );
StackItem* initStack();
// void initStack( StackItem** pStack );

#endif



