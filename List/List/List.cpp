#include "List.h"
#include <stdio.h>
#include <stdlib.h>

ListItem* CreateList()
{
	ListItem* pGuard = ( ListItem* )calloc( 1, sizeof( ListItem ) );
	if ( !pGuard )
		return NULL;
	pGuard->pNext = NULL;
	return pGuard;
}

int InsertFront( ListItem* pList, LISTINFO* pInfo )
{
	return Insert( pList, pInfo );
}

int Insert( ListItem* pAfter, LISTINFO* pInfo )
{
	ListItem* tempInsert = ( ListItem* )calloc( 1, sizeof( ListItem ) );
	if ( !tempInsert )
	{
		perror( "Blad alokacji Insert" );
		return 0;
	}
	tempInsert->pInfo = pInfo;
	ListItem* tempInsert2 = pAfter->pNext;
	pAfter->pNext = tempInsert;
	tempInsert->pNext = tempInsert2;
	return 1;

}

LISTINFO* RemoveFront( ListItem* pList )
{
	return Remove( pList );
}

LISTINFO* Remove( ListItem* pAfter )
{
	if ( IsEmpty( pAfter ) )
	{
		perror( "Blad w Remove" );
		return NULL;
	}
	ListItem* tempRemove = pAfter->pNext;
	LISTINFO* tempInfoRemove = tempRemove->pInfo;
	pAfter->pNext = tempRemove->pNext;
	free( tempRemove );
	return tempInfoRemove;
}

LISTINFO* Front( ListItem* pList )
{
	
	if ( IsEmpty( pList ) )
	{
		printf( "Blad w Front" );
		return NULL;
	}
	return pList->pNext->pInfo;
}

int IsEmpty( ListItem* pList )
{
	return !( pList->pNext );
}

void ClearList( ListItem* pList, void( __cdecl* freeInfo )( const void* ) )
{
	if ( !pList )
	{
		perror( "Lista nie istniejeCL" );
		return;
	}
	while ( !IsEmpty( pList ) )
		freeInfo( RemoveFront( pList ) );
	return;
}
void RemoveList( ListItem** pList, void( __cdecl* freeInfo )( const void* ) )
{
	if ( !pList || !*pList )
	{
		perror( "Lista nie istniejeRL" );
		return;
	}
	ClearList( *pList, freeInfo );
	free( *pList );
	*pList = NULL;
	return;
}

void SortList( ListItem* pList, int( __cdecl* CompareInfo )( const void*, const void* ) )
{
	if ( IsEmpty( pList ) )
	{
		perror( "Blad w SortList" );
		return;
	}
	ListItem* pFirst = pList;
	while ( pFirst->pNext )
	{
		ListItem* pMin = pFirst;
		ListItem* pCurr = pFirst->pNext;
		while ( pCurr->pNext )
		{
			if ( CompareInfo( pCurr->pNext->pInfo, pMin->pNext->pInfo ) == -1 )
				pMin = pCurr;
			pCurr = pCurr->pNext;
		}
		if ( pMin != pFirst )
		{
			pCurr = pMin->pNext->pNext;
			pMin->pNext->pNext = pFirst->pNext;
			pFirst->pNext = pMin->pNext;
			pMin->pNext = pCurr;
		}
		pFirst = pFirst->pNext;
	}
}

ListItem* Find( ListItem* pList, const void* zInfo, ListItem** pPrev, int( __cdecl* CompareInfo )( const void*, const void* ) )
{
	if ( IsEmpty( pList ) )
	{
		perror( "Blad w Find" );
		return NULL;
	}
	ListItem* tempFind = pList->pNext;
	*pPrev = pList;
	while ( tempFind )
	{
		if ( !CompareInfo( tempFind->pInfo, zInfo))
			return tempFind;
		else
		
			*pPrev = tempFind;
			tempFind = tempFind->pNext;
	}
	return *pPrev;
}