#include "pdStack.h"
#include <stdio.h>
#include <iostream>




dStackItem* dinitStack()
{
	return 0;
}

void pdpush( double d, dStackItem** pdStack )
{
	dStackItem* dptr = ( dStackItem* )malloc( sizeof( dStackItem ) );
	if( !dptr )
	{
		perror( "ERROR: allocation(pdpush): " );
		return;
	}
	dptr->cdKey = d;
	dptr->pdNext = *pdStack;
	*pdStack = dptr;
}

double pdpop( dStackItem** pdStack )
{
	if( !pdisEmpty(*pdStack) )
	{
		double x = pdtop( *pdStack );
		pddel( pdStack );
		return x;
	}
	perror( "ERROR(pdpop)" );
	return DBL_MIN;
	
}

double pdtop( dStackItem* pdStack )
{
	if( !pdisEmpty( pdStack ) )
	{
		return pdStack->cdKey;
	}
	else
	{
		perror( "Error(pdtop)" );
		return DBL_MIN;
	}
}

void pddel(dStackItem** pdStack )
{
	if( !pdisEmpty( *pdStack ) )
	{
		dStackItem* x = *pdStack;
		*pdStack  = x->pdNext;
		free( x );
	}
	else
		perror( "Stack underflow!(pddel)" );
}

int pdisEmpty( dStackItem* pdStack )
{
	return !pdStack;
}

void pdEmptyStack( dStackItem** pdStack )
{
	while( !pdisEmpty( *pdStack ) )
		pddel( pdStack );
}