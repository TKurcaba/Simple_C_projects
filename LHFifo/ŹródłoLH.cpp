#include "FQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void QFPrint( QFIFO* q, int ile);


int main()
{

	QFIFO* Queue = QFCreate();


	for ( int i = 1;i < 5;i++ )
	{
		QInfo* Info = ( QInfo* )calloc( 1, sizeof( QInfo ) );
		if ( !Info )
		{
			perror( "Blad alokacji Info " );
			return i;
		}
		if ( !QFEnqueue( Queue, Info ) )
		{
			perror( "Blad alokacji w QFEnqueue" );
			return i + 5;
		}
		Info->n_Key = i;
	}

	QFPrint( Queue, 3 );

	for ( int i = 1;i < 3;i++ )
	{
		QInfo* Info = ( QInfo* )calloc( 1, sizeof( QInfo ) );
		if ( !Info )
		{
			perror( "Blad alokacji Info " );
			return i + 10;
		}
		if ( !QFEnqueue( Queue, Info ) )
		{
			perror( "Blad alokacji w QFEnqueue" );
			return i + 15;
		}
		Info->n_Key = i;

	}
	QFClear( Queue );
	for ( int i = 1;i < 4;i++ )
	{
		QInfo* Info = ( QInfo* )calloc( 1, sizeof( QInfo ) );
		if ( !Info )
		{
			perror( "Blad alokacji Info " );
			return i + 10;
		}
		if ( !QFEnqueue( Queue, Info ) )
		{
			perror( "Blad alokacji w QFEnqueue" );
			return i + 15;
		}
		Info->n_Key = i + 4;

	}
	QFPrint( Queue, 1 );
	printf( "\n" );
	QFRemove( &Queue );
	return 0;
}

void QFPrint( QFIFO* q, int ile )
{
	if ( QFEmpty( q ) )
	{
		perror( "Blad, kolejka jest pusta " );
		return;
	}

	for ( int i = 0; i < ile; i++ )
	{
		printf( "%d ", QFDequeue( q )->n_Key );
	}
}