#include "PQueue.h"
#include <stdio.h>

void UpdateDown( PQItem* pPQueue, int l, int p );
void UpdateUp( PQItem* pPQueue, int l, int p );

PQueue* PQInit( int nSize )
{
	if ( nSize < 1 )
		return NULL;
	
	PQueue* Queue = ( PQueue* )calloc( 1, sizeof( PQueue ) );
	if ( !Queue )
		return NULL;
	Queue->pPQueue = ( PQItem* )calloc( nSize, sizeof( PQItem ) );
	if ( !Queue->pPQueue )
		return NULL;
	Queue->nPQSize = nSize;

	return Queue;
}

int PQisEmpty( PQueue* Queue )
{
	return !Queue || !Queue->nPQCurrSize;
}

int PQSize( PQueue* Queue )
{
	return (Queue) ? Queue->nPQCurrSize : PRIOR_ERROR;
}

int PGMaxPrior( PQueue* Queue )
{
	return (!Queue || PQisEmpty(Queue)) ? PRIOR_ERROR: Queue->pPQueue[0].nPrior;
}

int PQEnqueue( PQueue* Queue, PQINFO* info, int Prior )
{
	if ( !Queue )
		return 0;

	if ( PQSize( Queue ) > Queue->nPQSize - 1 )
		return 0;
	int CurrSize = Queue->nPQCurrSize++;
	Queue->pPQueue[CurrSize].nPrior= Prior;
	Queue->pPQueue[CurrSize].pInfo= info;
	if ( CurrSize > 0 )
		UpdateUp( Queue->pPQueue, 0, CurrSize );
	return 1;
}

PQINFO* PQDequeue( PQueue* Queue )
{
	if ( !Queue )
		return NULL;
	
	if ( PQisEmpty( Queue ) )
		return NULL;
	PQINFO* TempItem = Queue->pPQueue[0].pInfo;
	int ix = --Queue->nPQCurrSize;
	if ( ix )
		Queue->pPQueue[0] = Queue->pPQueue[ix];

	memset( Queue->pPQueue + ix, 0, sizeof( PQItem ) );
	if ( ix > 1 )
		UpdateDown( Queue->pPQueue, 0, ix - 1 );
	return TempItem;
}

void PQClear( PQueue* Queue, void( __cdecl* freeInfo )( const void* ) )
{
	if ( !Queue )
	{
		perror( "Kolejka nie istnieje \n" );
		return;
	}
	if ( freeInfo )
	{
		while ( !PQisEmpty( Queue ) )
			freeInfo( PQDequeue( Queue ) );
		return;
	}
	perror( "Nie istnieje funkcja obslugujaca usuwanie informacji" );
	return;
}

void PQRelease( PQueue** Queue, void( __cdecl* freeInfo )( const void* ) )
{
	if ( !Queue || !*Queue)
	{
		perror( "Kolejka nie istnieje \n" );
		return;
	}
	PQClear( *Queue, freeInfo );
	free( (*Queue)->pPQueue  );
	free( *Queue );
	*Queue = NULL;
}

void PQPrint( PQueue* Queue, int position, void( __cdecl* PrintInfo )( const void* ) )
{
	/*//int k = position;
	static int k = position;
	if ( k == 10 )
		return;
	PrintInfo( &Queue->pPQueue[k].pInfo->nKey );
	printf( " o priorytecie (%d), i pod indeksem [%d] \n", Queue->pPQueue[k].nPrior, k++ );
	PQPrint( Queue, k, PrintInfo );
	return;*/
	if ( !Queue )
	{
		perror( "Kolejka nie istnieje \n" );
		return;
	}
	
	if ( position >= Queue->nPQCurrSize )
		return;

	if ( PrintInfo )
		PrintInfo( &Queue->pPQueue[position].pInfo );
	printf( " o priorytecie (%d) pod indeksem [%d] \n", Queue->pPQueue[position].nPrior, position );
	PQPrint( Queue, 2 * position + 1, PrintInfo );
	PQPrint( Queue, 2 * position + 2, PrintInfo );
}

int PQSetPrior( PQueue* Queue, int NewPrior, PQINFO* info, int( __cdecl* CompareInfo )( const void*, const void* ) )
{
	return  PQsetPrior( Queue, NewPrior, PQFind( Queue, info, CompareInfo ) );
}

int PQsetPrior( PQueue* Queue, int NewPrior, int position )
{
	if ( !Queue )
		return PRIOR_ERROR;

	int tempsetPrior = PQgetPrior( Queue, position );
	if ( tempsetPrior != PRIOR_ERROR && tempsetPrior != POS_ERROR )
	{
		Queue->pPQueue[position].nPrior = NewPrior;
		if ( tempsetPrior > NewPrior )
			UpdateDown( Queue->pPQueue, position, PQSize( Queue ) - 1 );
		else
			UpdateUp( Queue->pPQueue, 0, position );
	}
	return tempsetPrior;
}

int PQGetPrior( PQueue* Queue, PQINFO* info, int( __cdecl* CompareInfo )( const void*, const void* ) )
{
	return  PQgetPrior( Queue, PQFind( Queue, info, CompareInfo ) );
}

int PQgetPrior( PQueue* Queue, int position )
{
	if ( !Queue || PQisEmpty( Queue ) )
		return PRIOR_ERROR;

	if ( position >= PQSize( Queue ) || position < 0 )
		return POS_ERROR;

	return Queue->pPQueue[position].nPrior;
}

int PQFind( PQueue* Queue, PQINFO* info, int( __cdecl* CompareInfo )( const void*, const void* ) )
{
	if ( !Queue )
		return  POS_ERROR;

	if ( !CompareInfo )
		return POS_ERROR;
	
	for ( int i = 0;i < PQSize( Queue ); i++ )
		if ( !CompareInfo( info, &Queue->pPQueue[i].pInfo->nKey ) )
			return i;
	return POS_ERROR;	
}


void UpdateDown( PQItem* pPQueue,  int l, int p )
{
	if ( l >= p ) 
		return;
	int i = l;
	PQItem temp = pPQueue[i];
	int j = i * 2 + 1;

	while ( j <= p )
	{
		if (pPQueue[j].nPrior < pPQueue[j + 1].nPrior )
			j++;
		if ( temp.nPrior >= pPQueue[j].nPrior )
			break;
		pPQueue[i] = pPQueue[j];
		i = j;
		j = i * 2 + 1;
	}
	pPQueue[i] = temp;
}

void UpdateUp( PQItem* pPQueue, int l, int p )
{
	
	if ( l >=p )
		return;
	int i = p;
	PQItem temp = pPQueue[i];
	int j = ( i - 1 ) / 2;
	int testzliczanie = 0;
	while (( j >= l) && ( pPQueue[j].nPrior < temp.nPrior ) )
	{
		testzliczanie++;
		pPQueue[i] = pPQueue[j];
		i = j;
		j = ( i + 1 ) / 2 - 1;
	}

	printf( "\n%d\n", testzliczanie );
	pPQueue[i] = temp;
}