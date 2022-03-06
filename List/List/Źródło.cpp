#include <stdio.h>
#include "List.h"
#include "global.h"
#include <stdlib.h>
#include <time.h>

#define _DEBUG_

void PrintList( ListItem* pList );

void freeInfo( const void* x )
{	
	free( (( LISTINFO* )x)->p );
	free( ( LISTINFO* )x );
}

int CompareInfo( const void* x, const void* y)
{
	LISTINFO* q1 = ( LISTINFO* )x;
	LISTINFO* q2 = ( LISTINFO* )y;
	if ( q1->nKey > q2->nKey )
		return 1;
	if ( q1->nKey < q2->nKey )
		return -1;
	return 0;
}

int main()
{
	
	ListItem* pList = CreateList();
	if ( !pList )
	{
		perror( "B³ad alokacji pList" );
		return 1;
	}

	srand( ( unsigned )time( NULL ) );

	for ( int i = 0; i < 20; i++ )
	{
		LISTINFO* pInfo = ( LISTINFO* )calloc(1, sizeof( LISTINFO ) );
		if ( !pInfo )
		{
			perror( "Blad alokacji pInfo" );
			return i + 1;
		}
		int* pTab = ( int* )calloc( 2, sizeof( int ) );
		if ( !pTab )
		{
			perror( "Blad alokacji pTab" );
			return -(i + 1);
		}
		if ( !InsertFront( pList, pInfo ) )
		{
			return i + 20;
		}
		pInfo->p = pTab;
		pInfo->p[0] = i;
		if ( i == 9 )
		{
			pInfo->nKey = 2000;
		}
		else
			pInfo->nKey = rand() % 50;

#ifndef _DEBUG_
printf( "%d ", pInfo->nKey );
#endif

	}
	printf( "\n" );
//----------------------------------------------PIERWSZE DRUKOWANIE-------------------------------------------------------------------
#ifdef _DEBUG_
	printf( "Drukowanie po stworzeniu: \n" );
	PrintList( pList );
#endif 

//----------------------------------------------SORTOWANIE----------------------------------------------------------------------------
	SortList( pList, CompareInfo );
#ifdef _DEBUG_
	printf( "\nDrukowanie po sortowaniu: \n" );
	PrintList( pList );
#endif 

//----------------------------------------------WYSZUKIWANIE--------------------------------------------------------------------------
	ListItem* pFind = ( ListItem* )calloc( 1, sizeof( ListItem ) );
	ListItem* pPrev= ( ListItem* )calloc( 1, sizeof( ListItem ) );
	LISTINFO* TempInfo = ( LISTINFO* )calloc( 1, sizeof( LISTINFO ) );
	TempInfo->nKey = 2000;
	pFind = Find( pList, TempInfo, &pPrev, CompareInfo );
#ifdef _DEBUG_
	printf( "\nWyszukany element: %d\n", pFind->pInfo->nKey );
#endif 

//----------------------------------------------DODANIE ELEMENTU O KLUCZU 3000--------------------------------------------------------
	TempInfo->nKey = 3000;
	Insert( pPrev, TempInfo );
	
#ifdef _DEBUG_
	printf( "\nDrukowanie po dodaniu: \n" );
	PrintList( pList );
#endif 

//----------------------------------------------USUNIECIE ELEMENTU O KLUCZU 2000------------------------------------------------------
	pFind = Find( pList, TempInfo, &pPrev, CompareInfo );
	free( Remove( pFind ) );

#ifdef _DEBUG_
	printf( "\nDrukowanie po usunieciu: \n" );
	PrintList( pList );
#endif 

//----------------------------------------------ZWOLNIENIE LISTYI DODANIE 2 ELEMENTOW------------------------------------------------

	ClearList( pList, freeInfo );

	for ( int i = 20; i < 22; i++ )
	{
		LISTINFO* pInfo = ( LISTINFO* )calloc( 1, sizeof( LISTINFO ) );
		if ( !pInfo )
		{
			perror( "Blad alokacji pInfo" );
			return i + 1;
		}
		int* pTab = ( int* )calloc( 2, sizeof( int ) );
		if ( !pTab )
		{
			perror( "Blad alokacji pTab" );
			return -( i + 1 );
		}
		if ( !InsertFront( pList, pInfo ) )
		{
			return i + 20;
		}
		pInfo->p = pTab;
		pInfo->p[0] = i;
		pInfo->nKey = rand() % 50;
	}

#ifdef _DEBUG_
	printf( "\nDrukowanie po dodaniu dwoch elementow: \n" );
	PrintList( pList );
#endif 

//----------------------------------------------USUNIECIE LISTY---------------------------------------------------------------------
	RemoveList( &pList, freeInfo  );
	return 0;
}




void PrintList( ListItem* pList )
{
	if ( IsEmpty( pList ) )
	{
		perror( "Lista jest pusta" );
		return;
	}

	ListItem* pTempPrint = pList->pNext;
	int i = 0;
	while ( pTempPrint)
	{
		printf( "Indeks: %d oraz wartosc: %d \n", i++, pTempPrint->pInfo->nKey );
		pTempPrint = pTempPrint->pNext;
	}
	return;
}