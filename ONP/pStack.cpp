#include "pStack.h"
#include <memory.h>
#include <iostream>

// dodatek po wykladzie gdy poszlo info ze zamykaja uczelnie 

StackItem* initStack()
{
	return NULL;
}

/*void initStack( StackItem** pStack )
{
	pStack = NULL;
}
*/
void ppush( char c, StackItem** pStack )
{
	StackItem* ptr = ( StackItem* )malloc( sizeof( StackItem ) );
	if( !ptr )
	{
		perror( "ERROR: allocation(ppush): " );
		return;
	}
	ptr->cKey = c;
	ptr->pNext = *pStack;
	*pStack = ptr;
}

char ptop( StackItem* pStack )
{
	if( !pisEmpty(pStack) )
		return pStack->cKey;
	return 0;
}

void pdel( StackItem** pStack )
{
	if( !pisEmpty( *pStack ) )
	{
		StackItem* ptr = *pStack;
		*pStack = ptr->pNext;
		free( ptr ); // zwolnienie pamieci, wazne!!!
	}
	else
		perror( "Error(pdel)" );
}

char ppop( StackItem** pStack )
{
	
	char c = ptop( *pStack );
	if( c )
		pdel( pStack );
	else
		perror("Stack underflow!(ppop)\n\n");
	return c;
	
}

int pisEmpty( StackItem* pStack )
{
	return !pStack;
}

void pEmptyStack( StackItem** pStack )
{
	while( !pisEmpty( *pStack  ))
		pdel( pStack );
}