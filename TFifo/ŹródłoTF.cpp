#include "FQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include "Global.h"


void QFPrint( QFIFO* q);


int main()
{

	QFIFO* Queue = QFCreate( 4 );
	if ( !Queue )
		return 1;

	for ( int i = 1;i < 5;i++ )
	{
		QFITEM* Item = ( QFITEM* )calloc( 1, sizeof( QFITEM ) );
		if ( !Item )
		{
			perror( "Blad alokacji Item " );
			return i;
		}
		Item->pTab = ( int* )calloc( 2, sizeof( int ) );
		if ( !Item->pTab )
		{
			perror( "Blad alokacji pTab" );
			return i + 4;
		}
		if ( !QFEnqueue( Queue, Item ) )
		{
			return i + 8;
		}
		Item->n_Key = Item->pTab[0] = i;
	}
	QFPrint( Queue);

	for ( int i = 1; i < 3; i++ )
	{
		QFITEM* Item = ( QFITEM* )calloc( 1, sizeof( QFITEM ) );
		if ( !Item )
		{
			perror( "Blad alokacji Item " );
			return i + 10;
		}
		Item->pTab = ( int* )calloc( 2, sizeof( int ) );
		if ( !Item->pTab )
		{
			perror( "Blad alokacji pTab" );
			return i + 12;
		}
		if ( !QFEnqueue( Queue, Item ) )
		{
			return i + 14;
		}
		Item->n_Key = Item->pTab[0] = 3 + i;
	}
	QFClear( Queue, freeItem );

	for ( int i = 1;i < 4;i++ )
	{
		QFITEM* Item = ( QFITEM* )calloc( 1, sizeof( QFITEM ) );
		if ( !Item )
		{
			perror( "Blad alokacji Item " );
			return i;
		}
		Item->pTab = ( int* )calloc( 2, sizeof( int ) );
		if ( !Item->pTab )
		{
			perror( "Blad alokacji pTab" );
			return i + 4;
		}
		if ( !QFEnqueue( Queue, Item ) )
		{
			return i + 8;
		}
		Item->n_Key = Item->pTab[0] = i+7;
	}

	QFPrint( Queue );
	QFRemove( &Queue, freeItem );
	
	return 0;
}



void freeItem( const void* x  )
{
	free( ((QFITEM*)x)->pTab );
	free( ( QFITEM* )x );
}
void QFPrint( QFIFO* q )
{
	if ( QFEmpty( q ))
	{
		perror( "Blad, kolejka jest pusta " );
		return;
	}

	do
	{
		printf( "%d ", q->pFQItems[q->nHead]->n_Key);
		q->nHead = ( q->nHead + 1 ) % q->nMaxElem;
	} while ( q->nHead != q->nTail );
}
