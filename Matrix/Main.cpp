#include <stdio.h>
#include "Matrix.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>

#define _DEBUG_
int f( int x )
{
	static int y = -2;
	return ( ++y, y -= ++x + y );
}

void ReadData( FILE* fin, double** pMatrix, double* b, int nDim );
void DeleteWektor( double** b, int nDim );
#define  min( x, y )  ( ((x) >= (y)) ? (x) : (y) )
int  a = 2;
int  b = 4;
int  c = min( 1, min( a, b ) );
#ifdef _DEBUG_
void PrintWektorB( double* b, int nDim ); // pomocniczo bo cos nie dzialalo przez chwile
#endif
int main( int argc, char* argv[] )
{
	
	int x = 1;
	if ( x = 2 )
		printf( "Szymon nie lubi daniela" );
	printf( "%d", x );
	if( argc == 2 )
	{
		printf( "Uzycie: %s, <plik_we> ", argv[0]);
		return 1;
	}

	FILE* fin = fopen( argv[1], "r" );

		if( !fin )
	{
		printf( "Nie mozna otworzyc pliku: %s ", argv[1] );
		return 2;
	}

	int nDim;
	fscanf( fin, "%d", &nDim );
	double** pMatrix = NULL;


	// sprawdzanie czy sie powiod³o alokowanie pamiec
	if( !CreateMatrix( &pMatrix, nDim ) )
	{
		perror( "Problem z alokwaniem pamieci dla wejsciowej macierzy" );
		return 3;
	}
	double* b  = ( double* )malloc( nDim*sizeof( double ) );


	if( !b )
	{
		perror( "Problem z alokowaniem pamieci dla wejsciowego wektora" );
		return 4;
	}

	memset( b, 0, sizeof( double )* nDim );

	// mozna zamiast dwoch ifów wyzej, jeden : if( !CreateMatrix( &pMatrix, nDim ) || !b  )

	ReadData( fin, pMatrix, b, nDim );
	fclose( fin );

#ifdef _DEBUG_
	printf( "Pierwszy kontrolny wydruk.\n" );
	printf( "Macierz wejsciowa: \n" );
	PrintMatrix( pMatrix, nDim );
	printf( "\n" );
	printf( "Wektor wyrazow wolnych na wejsciu: \n" );
	PrintWektorB( b, nDim );
	printf( "\n" );
#endif


	double det = Det( pMatrix, nDim );

	if( fabs(det) < 1e-16)
	{
		perror( "Nie mozna policzyc ukladu rownan metoda macierzy odwrotnej gdyz det jest rowny zero ( nie mozna dokonac odwrocenia macierzy) " );
		return 7;  // tu chyba return 0 bo wszystko zakonczylo sie pomyslnie ale macierzy nie da sie obrocic
	}
	double** InversedMartix = NULL;

	if( !( CreateMatrix( &InversedMartix, nDim ) ) )
	{
		perror( "Problem z alokwaniem pamieci dla macierzy ktora jest baza dla macierzy odwrtonej" );
		return 5;
	}

	InverseMatrix( InversedMartix, pMatrix, nDim, det );

#ifdef _DEBUG_
	printf( "Drugi kontrolny wydruk.\n" );
	printf( "Wyznacznik to : %lf \n \n", det );
	printf( "Macierz odwrotna: \n" );
	PrintMatrix( InversedMartix, nDim );
	printf( "\n" );
#endif


	double* Res = ( double* )malloc( nDim * sizeof( double ) );

	if( !Res )
	{
		perror( "Problem z alokwaniem pamieci dla wynikowego wektora" );
		return 6;
	}
	memset( Res, 0, sizeof( double ) * nDim );

	LayoutEqu( InversedMartix, b, Res, nDim );
	printf( "\n" );
	printf( "Wektor wynikowy: \n" );
	PrintWektorB( Res, nDim );
	printf( "\n" );

	//-------------------zwalanianie pamieci-----------------------------------
	DeleteMatrix( &pMatrix, nDim );
	DeleteMatrix( &InversedMartix, nDim );
	DeleteWektor( &b, nDim );
	DeleteWektor( &Res, nDim );
	return 0;
}


void ReadData( FILE* fin, double** pMatrix, double* b, int nDim )
{

	for( int i = 0; i < nDim; i++ )
	{
		double* pM = *pMatrix++;
		for( int j = 0; j < nDim; j++ )
			fscanf( fin, "%lf", pM++ ); // macierz g³ówna
		fscanf( fin, "%lf", b++ ); // wektor wyrazów wolnych
	}

}


void PrintWektorB( double* b, int nDim )
{
	for( int i = 0; i < nDim; i++ )
	printf( "%lf \n ", *b++ );

}

void DeleteWektor( double** b, int nDim )
{

	free( *b );
	*b = NULL;
}
