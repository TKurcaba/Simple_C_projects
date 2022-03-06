#include "dStack.h"
#include <memory.h>
#include <iostream>

using namespace std;

#define MAXSTACK 10

double dstack[MAXSTACK] = { 0 };
int ndHead = 0; 

void dpush( double d )
{
	if ( ndHead < MAXSTACK )
		dstack[ndHead++] = d;
	else	
		cout << "Stack overflow!!\n\n";
}

double dpop()
{
	double x = DBL_MIN;

	if (!disEmpty())
	{
		double x = dtop();
		ddel();
		return x;
	}
	else
	{
		perror( "ERROR" );
		return DBL_MIN;
	}
}

double dtop()
{

	if ( !disEmpty() )
		return dstack[ndHead - 1];
	return 0;
}

void ddel()
{
	if ( !disEmpty() )
	{
		ndHead--;
		dstack[ndHead] = 0;
	}
	else
		perror("ERROR: Stack underflow \n");
}

int disEmpty()
{
	return !ndHead;
}

void dEmptyStack()
{
	memset( dstack, 0, MAXSTACK * sizeof(double) );
	ndHead = 0;
}