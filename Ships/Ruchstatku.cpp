#include "Ruchstatku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

typedef enum { UP = 1, RIGHT, DOWN, LEFT } Directions;



int move( int** pDepthTab, int nRow, int nCol, int nDepth,
    int nextMove, int x, int y, int* px, int* py, int** pRoot )
{
	/*switch( nextMove )
	{
	case UP: *py = y + 1;*px = x; break;
	case RIGHT: *px = x + 1; *py = y; break;
	case DOWN: *py = y - 1; *px = x; break;
	case LEFT: *px = x - 1; *py = y; break;
	}*/ 
	switch( nextMove ) 
	{
	case UP: *px = x-1; *py = y ; break;
	case RIGHT: *py = y+1; *px = x ; break;
	case DOWN: *px = x+1; *py = y ; break;
	case LEFT: *py = y-1; *px = x ; break;
	default: perror( "Zly kierunek" ); return 0; 
	}
	if ( *px < 0 || *px >= nRow || *py < 0 || *py >= nCol )
		return 0;
	if ( ( pDepthTab[*px][*py] <= nDepth ) || ( pRoot[*px][*py] != 0 ) )
		return 0;
	
	return 1;

}

int root( int** pDepthTab, int nRow, int nCol, int nDepth,
	int x, int y, int** pRoot, int x_dest, int y_dest )
{
	static int k = 1;

	pRoot[x][y] = k++;

	if ( x == x_dest && y == y_dest )
		return 1;

	int px = x;
	int py = y;

	for ( int i = UP; i <= LEFT; i++ )
		if ( move( pDepthTab, nRow, nCol, nDepth, i, x, y, &px, &py, pRoot ) )
			if ( root( pDepthTab, nRow, nCol, nDepth, px, py, pRoot, x_dest, y_dest ) )
				return 1;

	pRoot[x][y] = 0;
	k--;
	return 0;

}


int readDepthTab( char* sFile, int** pTab, int nRow, int nCol )
{
	 FILE * fin = fopen( sFile, "r" );
	 if( !fin )
	 {
		 printf( "Nie mozna otworzyc pliku: %s ", sFile );
		 return 0;
	 }

	for( int i = 0; i < nRow; i++ )
	{
		int* pT = *pTab++;
		for( int j = 0; j < nCol; j++ )
		{

			fscanf( fin, "%d", pT++ );
		}
		
	}
	fclose( fin );
	return 1;
}

int** createTab( int nRow, int nCol )
{
	int** tab = ( int** )malloc( nRow * sizeof( int* )  );
	if ( !tab )
		return 0;
	

	memset( tab, 0, sizeof( int* ) * nRow );

	int* pTab = ( int* )malloc( nRow * nCol * sizeof( int ) );
	if ( !pTab )
	{
		free( pTab );
		return 0;
	}
	memset( pTab, 0, sizeof( int ) * nRow * nCol );

	int** pT = tab;
	for( int i =0; i < nRow; i++ )
	{	
		*pT++ = pTab;
		pTab += nCol;
		
	}
				
	return tab;
}
/*
int** createTab( int nRow, int nCol )
{
	int** tab = ( int** )malloc( nRow* sizeof( int* )  );
	int* pTab = ( int* )malloc( nRow * nCol * sizeof( int ) );
	int** pT = tab;
	for( int i = 0; i < nRow; i++ )
	{
		*pT = pTab + i * nCol;
		memset( *pT++, 0, sizeof( int ) * nCol );
	}

	return tab;
}	*/

void printTab( int** pRoot, int nRow, int nCol )
{
	for( int i = 0; i < nRow; i++ )
		{
			int* pR = *pRoot++;
			
			for( int j = 0; j < nCol; j++ )
			{
				printf( "%d ", *pR++ );
			}
			printf( "\n" );
		}
}

void freeTab( int*** pTab )
{
	free( **pTab );
	free( *pTab );
	
	*pTab = NULL;
}