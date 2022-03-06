#pragma once

#include "global.h"
#include <memory.h>
#include <stdlib.h>
#include <limits.h>

#define PRIOR_ERROR INT_MIN
#define POS_ERROR -1

typedef struct 
{
	PQINFO* pInfo;
	int nPrior; 
} PQItem;       


typedef struct 
{
	PQItem* pPQueue; 
	int nPQSize; 
	int nPQCurrSize; 
} PQueue;


PQueue* PQInit( int nSize );
int PQisEmpty( PQueue* Queue );
int PQSize( PQueue* Queue ); 
int PGMaxPrior( PQueue* Queue );
int PQEnqueue( PQueue* Queue, PQINFO* info, int Prior );
PQINFO* PQDequeue( PQueue* Queue ); 
void PQClear( PQueue* Queue, void( __cdecl* freeInfo )( const void* ) ); 
void PQRelease( PQueue** Queue, void( __cdecl* freeInfo )( const void* ) );
void PQPrint( PQueue* Queue, int position, void( __cdecl* PrintInfo )( const void* ) );
int PQSetPrior( PQueue* Queue, int NewPrior, PQINFO*  info, int( __cdecl* CompareInfo )( const void*, const void* ) );
int PQsetPrior( PQueue* Queue, int NewPrior, int position );
int PQGetPrior( PQueue* Queue, PQINFO* info, int( __cdecl* CompareInfo )( const void*, const void* ) );
int PQgetPrior( PQueue* Queue , int position);
int PQFind( PQueue* Queue, PQINFO* info, int( __cdecl* CompareInfo )( const void*, const void* ) );	