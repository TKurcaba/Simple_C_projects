#include "onpfun.h"
#include "stack.h"
#include <stdio.h>
#include <math.h>
#include "dstack.h"
#include "pdStack.h"
#include "pStack.h"
#include <iostream>

#define DOT '.'

void skipSpaces() 
{
	char c;
	while ((c = getchar()) == ' ');
	// while( isspace( c= getchar() );
	ungetc(c, stdin); 
}

int isDigit(char c)
{
	return (c >= '0') && (c <= '9');
}

// dla kalkulatora 
double getNum()
{
	char c;
	double num = 0;
	int sign = 0;

	skipSpaces();

	if ( (c = getchar() ) == '-')
		sign = 1;
	else if(c != '+')
		ungetc(c, stdin);

	while( isDigit( c = getchar() ) )
		num = num * 10 + c - '0';
	if (c == DOT)
	{
		double coef = 0.1;
		while( isDigit( getchar() ) )
		{
			num += ( c - '0' ) * coef;
			coef *= 0.1;

		}
	}
	ungetc(c, stdin);
	if (sign)
		num = -num;
	return num;
}

// dla stosu znakowego, mozna bylo uzyc tego wyzej ale zrobilem dwie oddzielne funkcje,  co jest w sumie nie potrzebne ale zachowam dla 
int getNum1()
{
	char c;
	int num = 0;

	skipSpaces();
	while( isDigit( c = getchar() ) )
		num = num * 10 + c - '0';


	ungetc( c, stdin );
	return num;
}

int prior(char cOper)
{
	switch (cOper)
	{
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	}
	return 0;
}

int isOper(char cOper)
{
	switch (cOper)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':return 1;
	}
	return 0;
}

char getOper() 
{
	skipSpaces();
	return getchar();
}

// do wypisywania w konwencji ONP
void onp()
{
	char c;
	skipSpaces();
	StackItem* pStack = initStack();
	
	printf( " %d", getNum1() );

	while( isOper( c = getOper() ) )
	{
		while( prior( c ) <= prior( ptop( pStack ) ) )
			putchar( ppop( &pStack ) );
		ppush( c, &pStack );
		printf( " %d", getNum1() );
	}

	while( !pisEmpty( pStack ) )
		printf( " %c", ppop( &pStack ) );

}

// dzialanie na dwoch najblizszych skladnikach na stosie
double evalONP( char cOper, double arg1, double arg2 )
{
	switch( cOper )
	{
	case '+': return arg1 + arg2;
	case '-': return arg1 - arg2;
	case '*': return arg1 * arg2;
	case '/': 
		if( fabs( arg2 ) > 1e-15 )
			return arg1 / arg2;
		perror( "ERROR: Devision by 0!!" );
		return DBL_MIN;
	case '^':return pow( arg1, arg2 );
	}
	return 0;
}

// kalkulator wykorzystujacy zalozenia ONP
double calcONP()
{
	char c;
	StackItem* pStack = initStack();
	dStackItem* pdStack = dinitStack();
	skipSpaces();
	pdpush( getNum(), &pdStack );
	while(  isOper( c = getOper() ) ) 
	{
	while( prior( c )<= prior( ptop( pStack ) ) )
	{
		double d = pdpop( &pdStack );
		pdpush ( evalONP( ppop(&pStack), pdpop(&pdStack), d ), &pdStack );
	}
	ppush( c, &pStack );
	pdpush( getNum(),&pdStack );

	}
while( !pisEmpty(pStack) )
{
	double d = pdpop(&pdStack);
	pdpush( evalONP( ppop( &pStack ), pdpop( &pdStack ), d ), &pdStack );

}
	
return pdpop(&pdStack);

}
