#include "FQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include "Global.h"

void  QFDel( QFIFO* q );

// kreowanie dynamiczne kolejki (struktury i tablicy)
QFIFO* QFCreate( int nSize )  // nSize  - rozmiar tablicy
{
	if ( nSize <= 0 )
	{
		perror( "Wielkosc tablicy musi byc nieujemna" );
		return NULL;
	}
	QFIFO* q = ( QFIFO* )calloc( 1, sizeof( QFIFO ));
	if ( !q )
	{
		perror( "Problem alokacji q w QFCreate" );
		return NULL;
	}
	q->pFQItems = ( QFITEM** )calloc( nSize, sizeof( QFITEM* ) );
	if ( !q->pFQItems )
	{
		perror( "Problem alokacji pFQItems w QFCreate" );
		return NULL;
	}
	q->nMaxElem = nSize;	
	return q;

}
// zwraca 1 gdy kolejka pusta, w przeciwnym wypadku 0
int QFEmpty( QFIFO* q )
{
	return ( !q || !(q->nHead) );
}

// wstawienie elementu do kolejki
int QFEnqueue( QFIFO* q, QFITEM* pItem )
{
	if ( !q )
	{
		perror( "Kolejka nie istnieje" );
		return 0;
	}

	if ( q->nMaxElem == q->nNoElem )
	{
		printf( "kolejka jest pelna" );
		return 0;
	}
	q->pFQItems[q->nTail] = pItem;
	q->nTail = ( q->nTail + 1 ) % q->nMaxElem;
	q->nNoElem++;
	return 1;

}	

// usuniecie elementu z kolejki i zwrocenie wskaznika do tego elementu
QFITEM* QFDequeue( QFIFO* q )
{
	if ( !q )
	{
		perror( "Kolejka nie istnieje" );
		return NULL;
	}
	if ( QFEmpty( q ) )
	{
		printf( "Kolejka jest pusta" );
		return NULL;
	}
	QFITEM* tempDeq = q->pFQItems[q->nHead];
	QFDel( q );
	return tempDeq;
}

// czyszczenie kolejki, kolejke mozna uzywac
void QFClear( QFIFO* q, void( __cdecl* freeInfo )( const void* ) )
{
	if ( !q )
	{
		perror( "Kolejka nie istnieje" );
		return ;
	}
	while ( !QFEmpty(q) )
		freeInfo( QFDequeue(q) );

	q->nHead = 0;
	q->nTail = 0;
}

// czyszczenie kolejki i usuniecie wszystkich struktur danych, wyzerowanie wskaznika
void QFRemove( QFIFO** q , void( __cdecl* freeInfo )( const void*  ) )
{
	if ( !q || !*q )
	{
		perror( "Kolejka nie istnieje" );
		return;
	}
	QFClear( *q, freeInfo );
	free( ( *q )->pFQItems );
	free( *q );
	*q = NULL;
}


void  QFDel( QFIFO* q )
{
	if ( !q )
	{
		perror( "Kolejka nie istnieje" );
		return;	
	}
	if ( QFEmpty( q ) )
	{
		printf( "Kolejka jest pusta del" );
		return;
	}
	q->pFQItems[q->nHead] = NULL;
	q->nHead = ( q->nHead + 1 ) % q->nMaxElem;
	q->nNoElem--;
}

//  - wstawia NULL do pozycji tablicy, skad pobierany jest element
//  - przesuwa cyklinie indeks glowy kolejki
//  - zmniejsza ilosc elementow w kolejce
