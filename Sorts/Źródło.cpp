#include <stdio.h>
#include "Sortowania.h"
#include <stdlib.h>
#include <memory.h>
#include <time.h>

#define SIZEC 50
#define _DEBUG_ // kontrolne wydruki
#define SIZEP 10

typedef void( *typNaSort )( int*, int ); // nazwy chyba niekonieczne, tylko typy

int CreateTab( int** pTab, int nSize );
void DeleteTab(int** pTab, int nSize );
void PrintTab( int* pTab, int nSize);
void FillTab( int* pTab, int nSize );

int main( int argc,  char* argv[] )
{
	if( argc != 2)
	{
		perror( "W wierszu polecen podaj wielkosc tablicy ktora bedziemy sortowac" );
		return 3;
	}

	int size = atoi( argv[1] );
	
	int* pTab = NULL;
	if( !CreateTab( &pTab, size ) )
	{
		perror( "Allocation error" );
		return 1;
	}
	FillTab( pTab, size );
#ifndef _DEBUG_
	PrintTab( pTab, SIZEC);
#endif

	int* pTab2 = NULL;
	if( !CreateTab( &pTab2, size ) )
	{
		DeleteTab( &pTab, size );
		perror( "Allocation error" );
		return 2;
	}

	typNaSort pSortTab[] = {
		wstawianiePolow,
		wstawianie,
		wybieranie,
		babelkowe,
		mieszane,
		szybkie,
		stogowe
	};
	const char* TabNazw[] = { "przez wstawiania z elementami wyszukiwania Polowkowego ","przez wstawianie", 
		"przez wybieranie", "babelkoweego","mieszaneego", "szybkiego", "stogowegp" };

	int liczbaSortowan = sizeof( pSortTab ) / sizeof( typNaSort );

	for( int i = 0; i < liczbaSortowan; i++ )
	{
		
		memcpy( pTab2, pTab, sizeof(int) * size );
		
		clock_t start = clock();
		pSortTab[i]( pTab2, size );
		clock_t koniec = clock();

#ifdef _DEBUG_
		//printf( "Przed sortowaniem: \n" );
		//PrintTab( pTab2, 50 );
		printf( "\n Po sortowaniu: \n" );
		PrintTab( pTab2, ( size < SIZEC ) ? size : SIZEC );
		printf( "\n" );
#endif

		printf( "Czas dla sortowania %s wyniosl: %.50lf \n", TabNazw[i], ( double )( koniec - start ) / CLK_TCK );

	}


	DeleteTab( &pTab, size );
	DeleteTab( &pTab2, size );

	return 0;
}



int CreateTab( int** pTab, int nSize )
{
	*pTab = ( int* )malloc( nSize * sizeof( int ) );
	if( !pTab )
		return 0; 
	
	memset( *pTab, 0, nSize * sizeof( int ) );
	return 1; 

}

void DeleteTab( int** pTab, int nSize )
{
	
	free( *pTab );
	*pTab = NULL;
}

void FillTab( int* pTab, int nSize )
{
	srand( (unsigned int)time( NULL ) );
	for( int i = 0; i < nSize; i++ )
	{
		*pTab++ = rand() % nSize;
		
	}
}
void PrintTab( int* pTab, int nSize) 
{

	for ( int i = 0; i < nSize; i++ )
	{
	printf( "%d ", *pTab++ );
	if ( !( ( i + 1 ) % SIZEP ) )
		printf( "\n" );
	}
}