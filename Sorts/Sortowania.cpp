#include <stdio.h>
#include "Sortowania.h"



void Update( int* tab, int l, int p );
void sortuj( int* tab, int l, int p );


void wstawianie( int* tab, int nSize )
{
	
	for( int i = 1; i < nSize; i++ )
	{
		int x = tab[i];
		int j = i - 1;
		while( (j >= 0 ) && ( tab[j] > x ) )
			tab[j + 1] = tab[j--];
			
		tab[j + 1] = x;
	}
}

void wstawianiePolow( int* tab, int nSize )
{


	for( int i = 1; i < nSize; i++ )
	{
		int x = tab[i];
		int l = 0;
		int p = i - 1;		

		while( l <= p )
		{
			int m = ( l + p ) / 2;
			if( x < tab[m] )
				p = m - 1;
			else
				l = m + 1;
		}

		for( int j = i - 1; j >= l; j-- )
			tab[j + 1] = tab[j];

		tab[l] = x;
	}
}
void wybieranie( int* tab, int nSize )
{
	
	for( int i = 0; i < nSize - 1; i++ )
	{
		int k = i;
		int x = tab[i];
		for( int j = i + 1; j < nSize; j++ )
			if( tab[j] < x )
			{
				k = j;
				x = tab[j];
			}
		tab[k] = tab[i];
		tab[i] = x;
	}
}

void babelkowe( int* tab, int nSize )
{
	for( int i = 1; i < nSize; i++ )
	{
		for( int j = nSize - 1; j >= i; j-- )
			if( tab[j - 1] > tab[j] )
			{
				int x = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = x;
			}
	}
}
void mieszane( int* tab, int nSize )
{
	int l = 1;
	int p = nSize - 1;
	int k = nSize - 1;
	do {
		for( int j = p; j >= l; j-- )
			if( tab[j - 1] > tab[j] )
			{
				int x = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = x;
				k = j;
			}
		l = k + 1;
		for( int j = l; j <= p; j++ )
			if( tab[j - 1] > tab[j] )
			{
				int x = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = x;
				k = j;
			}
		p = k - 1;
	} while( l < p );
}
void szybkie( int* tab, int nSize )
{
	sortuj( tab, 0, nSize - 1 );
}

void sortuj( int* tab, int l, int p ) // poniewaz liczba argumentow musi sie zgadzac z innymi funkcjami zeby przypisac do teego samego typu wskaznikowego 
{
	int i = l;
	int j = p;
	int x = tab[( l + p ) / 2];
	do
	{
		while( tab[i] < x )
			i++;
		while( x < tab[j] )
			j--;
		if( i <= j )
		{
			int temp = tab[i];
			tab[i] = tab[j];
			tab[j] = temp;
			i++;
			j--;
		}
	} while( i < j );
	if( l < j )
		sortuj( tab, l, j );
	if( i < p )
		sortuj( tab, i, p );
}


void stogowe( int* tab, int nSize )
{
	int p = nSize - 1;
	
	for ( int l = nSize / 2; l >= 0; l-- )
		Update( tab, l, p );
	
	for ( ; p > 0; p-- )
	{
		int temp = tab[0];
		tab[0] = tab[p];
		tab[p] = temp;
		Update( tab, 0, p-1 );
	}
}

void Update( int* tab, int l, int p )
{
	if ( l >= p )
		return;
	int i = l;
	int x = tab[i];
	int j = 2 * i + 1;
	while( j <= p )
	{
		if( j < p )
			if( tab[j] < tab[j + 1] )
				j++;
		if( x >= tab[j] )
			break;
		tab[i] = tab[j];
		i = j;
		j = 2 * i + 1;
	}
	tab[i] = x;
}