#include "stack.h"
#include <memory.h>
#include <iostream>

using namespace std;

#define MAXSTACK 10

static char stack[MAXSTACK] = { 0 };
static int nHead = 0; // stack is empty
			   // first empty element on the stack

void push( char c )
{
	if( nHead < MAXSTACK )
		stack[nHead++] = c;
	else
		cout << "Stack overflow!!\n\n";
}

char pop()
{
	char c = top();
	if (c)
		del();
	else
		cout << "Stack underflow!\n\n";
	return c;
}

char top()
{
	if ( !isEmpty() )
		return stack[nHead - 1];
	return 0;
}

void del()
{
	if ( !isEmpty() )
	{
		nHead--;
	
	}
	else
		perror( "ERROR: Stack underflow \n" );
}

int isEmpty()
{
	return !nHead;
}

void EmptyStack()
{
	memset(stack, 0, MAXSTACK * sizeof( char ) );
	nHead = 0;
	// while(!isEmpty()) del();
}
