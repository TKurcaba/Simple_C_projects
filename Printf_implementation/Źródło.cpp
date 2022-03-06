#include "stdio.h"
#include "stdarg.h"
#include "math.h"
#define DOT '.'

int Printf( const char* sFormat, ... );
int PrintfV( const char* sFormat, va_list arg_list );

void outDec( int x ); // znakowo wypisuje liczbe ca³k
void outChar( char c );  // wypisuje znak // putchar()
void outStr(char* str);// wypisuje znakowo string
void outDouble( double x );  // wypisuje znakowo liczbe double     0.
void outNum( int x ); // wypisuje znakowo liczbe int >0 rekurencyjnie



// zalozyc ze mamy tablice double 4x4
// funckja transpowania macierzy
// void complement(double pTab[n1][n1], double pTab[n][n], int nRow, int nCol)
// wykorzystac dwa razy continue wycina wiersz i kolumne 


int main()
{
	int n = 120;
	char c = 's';
	double x = 1200000.34500012;
	double y = -0.12;
	printf( "%d", 5 ^ 3 );
	double z = -0.5;
	char str[] = "to jest string";
	Printf( "%c %d %s %f", c, n ,str,y);
	return 0;
	// implementacja 
	// zamiana `(~) na '(")
	// do wypisywania mozna jedynie uzyc putchar()
	// 
}


void outChar( char c )
{
	putchar( c );
}

void outDec( int x )
{
	if (x > 0) outNum( x );
	else
	{
		if ( x == 0 )
			putchar('0');
		else
		{
			putchar( '-' );
			outNum( -x );
		}
	}
}


void outStr( char* str)
{
	char c;
	int i = 0;
	while (c = str[i++])
		outChar(c);
}

void outNum( int x )
{
	if( x > 0 ) 
	{
		outNum( x / 10 );
		outChar( x % 10 + 48 );
	}
	
}

void outDouble( double x )
{
	double y = x;
	if( x < 0 )
	{
		outChar( '-' );
		x = -x;
	}
	if( x == 0 )
		outChar( '0' );
	outDec( ( int )x );
	outChar( '.' );
	int z = (x - ( int )x)* pow(10,8);
	outDec( z );
}




int Printf(const char* sFormat, ...)
{
	va_list args;
	va_start(args, sFormat);
	int res = PrintfV(sFormat, args);
	va_end(args);
	return res;

}
int PrintfV(const char* sFormat, va_list arg_list)
{
	int res = 0;
	char c;
	int i = 0;
	while (c = sFormat[i++])
	{
		switch (c)
		{
		case '%': switch (c = sFormat[i++])
		{
		case'c':res++; outChar(va_arg(arg_list, char)); break;
		case'd':res++; outDec(va_arg(arg_list, int)); break;
		case'f':res++; outDouble(va_arg(arg_list, double)); break;
		case's':res++; outStr(va_arg(arg_list, char*)); break;
		default:res++; outChar('%'); outChar(c);
		}
		break;
		case'`':c = '\'';
		default:outChar(c);
		}
	}
	return res;
}
