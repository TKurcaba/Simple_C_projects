#include "PQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20
#define _DEBUG_

void freeInfo( const void* );
void PrintTab( const void* );
int CompareInfo( const void*, const void* );

void freeInfo( const void* x )
{
	free( (( PQINFO* )x)->pTab );
	free( ( PQINFO* )x );
}

void PrintTab( const void* x )
{
	PQINFO* q = ( PQINFO* )x;
	printf( "%d ", q->nKey );
}

int CompareInfo( const void* x, const void* y )
{
	if ( x == NULL && y == NULL )
		return 0;
	if ( !x )
		return 1;
	if ( !y )
		return -1;
	PQINFO* q1 = ( PQINFO* )x;
	PQINFO* q2 = ( PQINFO* )y;
	if ( q1->nKey > q2->nKey )
		return 1;
	if ( q1->nKey < q2->nKey )
		return -1;
	return 0;
}

int main()
{
	PQueue* Queue = PQInit( SIZE );
	srand( unsigned( time( NULL ) ) );
	for ( int i = 0; i < 6; i++ )
	{
		PQINFO* pInfo = ( PQINFO* )calloc( 1, sizeof( PQINFO ) );
		if ( !pInfo )
		{
			perror( "Blad alokacji pInfo" );
			return i + 1;
		}
		pInfo->pTab = ( int* )calloc( 2, sizeof( int ) );
		if ( !pInfo->pTab )
		{
			perror( "Blad alokacji pTab" );
			return i;
		}
		int prior = i+2;
		pInfo->nKey  = i;
		PQEnqueue( Queue, pInfo, prior );	
	}
	printf( "\n" );
	PQPrint( Queue, 0, PrintTab );
	printf( "\n Informacja o najwiekszym priorytecie: " );
	PrintTab( &PQDequeue( Queue )->nKey );
#ifdef _DEBUG_
	printf( "\n Po usunieciu informacji o najwiekszym priorytecie kolejka wyglada tak: \n" );
	PQPrint( Queue, 0, PrintTab );
#endif
	for ( int i = 0; i < 4; i++ )
	{
		PQINFO* pInfo = ( PQINFO* )calloc( 1, sizeof( PQINFO ) );
		if ( !pInfo )
		{
			perror( "Blad alokacji pInfo" );
			return i + 6;
		}
		//int prior = rand() % 50;
		int prior = 9; // zobaczmy co sie stanie jak dodamy info o takich samych priorytetach
		pInfo->nKey = i+6;
		PQEnqueue( Queue, pInfo, prior );
	}
#ifdef _DEBUG_
	printf( "\n Po dodaniu dwoch nowych informacji kolejka wyglada tak: \n" );
	PQPrint( Queue, 0, PrintTab );
#endif
	printf( "\n Priorytet informacji pod indeksem 5: %d\n", PQGetPrior( Queue, Queue->pPQueue[5].pInfo, CompareInfo ) );
	PQSetPrior( Queue, 1, Queue->pPQueue[1].pInfo, CompareInfo );
#ifdef _DEBUG_
	printf( "\n Po zamianie priorytetu elementu pod indeksem 1, kolejka wyglada tak: \n" );
	PQPrint( Queue, 0, PrintTab );
#endif
	PQRelease( &Queue, freeInfo );
	return 0;
}