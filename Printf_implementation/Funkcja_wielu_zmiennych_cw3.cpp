#include<stdio.h>
#include <stdarg.h>
#define DOT '.'

int Printf( const char* sFormat, ... );
int PrintfV( const char* sFormat, va_list arg_list );

void outDec( int );//znakowo wypisuje liczbe calkowita
void outChar( char );//wypisuje znak//putchar()
void outStr( char* );//wypisuje znakowo string
void outDouble( double ); //wypisuje znakowo liczbe double
void outNum( int ); //wypisuje znakowo liczbe int>0

int main() {

	int n = -0;
	char c = '$';
	double x = 120000.340532440;
	double y = -.12;
	double z = -0.5;
	const char* str = "to jest string";

	return 0;
}

int Printf(const char* sFormat,... ) {

	va_list args;//deklaruje
	va_start( args, sFormat );

	char res = PrintfV( sFormat, args );

	va_end( args );

	return res;
}

int PrintfV( const char* sFormat, va_list arg_list) {

	int res = 0;
	int i = 0;
	char c;
	while ( c = sFormat[i++] ) {
		switch ( c ) {
        case '%':
				 switch ( c = sFormat[i++] ) {
				 case'd': outDec( va_arg( arg_list, int ) );       break;
				 case'f': outDouble( va_arg( arg_list, double ) ); break;
				 case's': outStr( va_arg( arg_list, char* ) );     break;
				 case'c': outChar( va_arg( arg_list, char ) );     break;
				 default: outChar( '%' ); outChar( c );/* res--*/;     break;
				 }
				 break;
	    case'`': c== '\'';
		default: outChar( c ); break;
		}

	}
	return res;
}

void outDec( int x ) {
	if ( x > 0 ) outNum( x );
	if ( x == 0 )putchar( '0' );
	else {
		putchar( '-' );
		outNum( x * -1 );
	}
}
void outChar( char c ) {
	putchar( c );
}
void outStr( char* str ) {
	char c;
	int i = 0;
	while ( c = str[i++] )
		outChar( c );
}
void outDouble( double x) {
	if ( x < 0 ) {
		outChar( '-' );
		x *= -1;
	}
	if ( x > 0 && x < 1 ) outChar( 0 );

	outNum( (int)x );
	outChar( '.' );
	//wypisac czsc  ulamkowa

}
void outNum( int x ) {
	if ( x>0  && x/10 ) {
		outChar( x / 10 );
	}
	outChar( x % 10 );
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*Uproszczony printf: %c %d %f %s oraz zamienia "`" na "'"*/

