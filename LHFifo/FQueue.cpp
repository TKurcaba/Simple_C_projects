#include "FQueue.h"
#include <stdlib.h>
#include <stdio.h>

void  QFDel( QFIFO* q );

// kreowanie dynamiczne kolejki
QFIFO* QFCreate()
{
	QFIFO* que = ( QFIFO* )calloc( 1, sizeof( QFIFO ) );
	if ( !que )
	{
		perror( "Blad alokacji" );
		return NULL;
	}
	
	que->pHead = que->pTail = ( QFItem* )calloc( 1, sizeof( QFItem ) );
	if ( !que->pHead )
	{
		perror( "Blad alokacji" );
		return NULL;
	}
	return que;
}

// zwraca 1 gdy kolejka pusta, w przeciwnym wypadku 0
int QFEmpty( QFIFO* q )
{
	return ( !q || !q->pHead );

}

// wstawienie elementu do kolejki i zwrocenie 1 gdy OK i 0 gduy blad alokacji

int QFEnqueue( QFIFO* q, QInfo* pInfo )
{
	if ( !q )
	{
		perror( "Kolejka nie istnieje" );
		return 0;
	}
	QFItem* pItem = ( QFItem* )calloc( 1, sizeof( QFItem ) );
	if ( !pItem )
	{
		perror( "Blad alokacji pItem" );
		return 0;
	}
	q->pTail->pNext = pItem;
	q->pTail = pItem;
	pItem->pInfo = pInfo;
	
	return 1;

}

// usuniecie elementu z kolejki i zwrocenie wskaznika do tego elementu (NULL - kolejka pusta)
QInfo* QFDequeue( QFIFO* q )
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
	QInfo* tempDeq =  q->pHead->pNext->pInfo;
	QFDel( q );
	return tempDeq;

}


// czyszczenie kolejki, kolejke mozna uzywac dalej
void  QFClear( QFIFO* q )
{
	if ( !q )
	{
		perror( "Kolejka nie istnieje" );
		return;
	}
	while ( !QFEmpty( q ) )
	{
		free( QFDequeue( q ) );
	}
	return;
}

// czyszczenie kolejki i usuniecie wszystkich struktur danych, wyzerowanie kolejki
void  QFRemove( QFIFO** q )
{
	if ( !q || !*q )
	{
		perror( "Kolejka nie istnieje" );
		return;
	}
	QFClear( *q );
	free( ( *q )->pHead );
	free( *q );
	*q = NULL;
}

// funkcja prywatna modulu  - tylko usuniecie elemenu z listy (nie info)
void  QFDel( QFIFO* q )
{
	if ( !q )
	{
		perror( "Kolejka nie istnieje" );
		return;
	}
	if ( !QFEmpty( q ) )
	{ 
	QFItem* tempDel = q->pHead->pNext;
	q->pHead->pNext = tempDel->pNext;
	free( tempDel );
	if ( QFEmpty( q ) )
		q->pTail = q->pHead;
	}
}