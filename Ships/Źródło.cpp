#include "Ruchstatku.h"
#include <stdio.h>
#include <stdlib.h>

#define SHIP_DEPTH 6
#define N 8
#define M 8
#define _DEBUG_


int main(int argc, char* argv[])
{
	if( argc != 2 )
	{
		perror( "Brakuje pliku z glebokosciami w argumentach wywolania funkcji!" );
		return 1;
	}

	int** pDepthTab = createTab( N, M );
	int** pRoot = createTab( N, M );

	if( pRoot == 0 || pDepthTab == 0 )
	{
		perror( "Allocation errors" );
		return 1;
	}
	
	if( readDepthTab( argv[1], pDepthTab, N, M ) )
	{
		
#ifdef _DEBUG_
		printf( "Wydruk kontrolny tablicy glebokosci : \n" );
		printTab( pDepthTab, N, M );
		printf( "\n" );
		//printTab ( pRoot, N, M );
		//printf( "\n" );
#endif

		int x_dest = N - 1;
		int y_dest = M - 1;

		if( !root( pDepthTab, N, M, SHIP_DEPTH, 0, 0, pRoot, x_dest, y_dest ) )
		{
			printf( "Nie ma mozliwosci doplynac do portu!!\n\n" );
			printTab( pRoot, N, M );

		}
		else
		{
			printf( "Brawo statek osiagnal swoj cel, oto jego trasa, gdzie kolejne cyfry oznaczaja kolejnosc poruszania sie po polach \"morza\" : \n" );
			printTab( pRoot, N, M );
		}
	}
	freeTab( &pRoot );
	freeTab( &pDepthTab );

	return 0;
}