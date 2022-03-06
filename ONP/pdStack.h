#ifndef _PDSTACK_H
#define _PDSTACK_H

typedef struct tagdStackItem {
	double         cdKey;
	tagdStackItem* pdNext;
} dStackItem;

void pdpush( double d, dStackItem** pdStack );
double pdpop( dStackItem** pdStack );
double pdtop( dStackItem* pdStack );
void pddel( dStackItem** pdStack );
int pdisEmpty( dStackItem* pdStack );
void pdEmptyStack( dStackItem** pdStack );
dStackItem* dinitStack();

#endif
