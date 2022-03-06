#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>


void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim );
void ComplMatrix( double** pTabD, double** pMatrix, int nDim );

	
int CreateMatrix( double*** pMatrix, int nDim )
{
	*pMatrix = ( double** )malloc( nDim * sizeof( double* ) );
	if( !pMatrix )
		return 0;
	memset( *pMatrix, 0, nDim * sizeof( double* ) );
	double** ppMatrix = *pMatrix;
	for( int i = 0; i < nDim; i++ )
	{
		*ppMatrix = ( double* )malloc( nDim * sizeof( double ) );
		if( ( !*ppMatrix ) )
			return 0;
		memset( *ppMatrix++, 0, sizeof( double ) * nDim );
	}

	return 1;

}

void DeleteMatrix( double*** pMatrix, int nDim )
{
	double** pM = *pMatrix;
	for( int i = 0; i < nDim; i++ )
		free( *pM++ );
	free( *pMatrix );
	*pMatrix = NULL;
}


void TransMatrix( double** pMatrix, int nDim )
{
	double** pM2 = pMatrix;
	for( int i = 0; i < nDim - 1; i++ )
	{
		double* pM = *pM2++ + i + 1;
		for( int k = i + 1; k < nDim; k++ )
		{
			double temp = *pM;
			*pM++ = pMatrix[k][i];
			pMatrix[k][i] = temp;
		}
	}
}

void InverseMatrix( double** pInv, double** pMatrix, int nDim, double det )
{
	/*if( fabs(det) < 1e-16)

	{
		perror( "NIE MOZNA OBRÓCIÆ, DET WYNOSI 0!!" );
		return;
	}*/
	// sprawdzanie powyzszego warunku w main
	
	ComplMatrix( pInv, pMatrix, nDim );
	TransMatrix( pInv, nDim );

	// PrintMatrix( pTabPom, nDim );
	/*for ( int i = 0; i< nDim; i++ )
		for( int j = 0; j < nDim; j++ )
		{
			pInv[i][j] = pTabPom[i][j] / det;
		}
	*/


	for( int i = 0; i < nDim; i++ )
	{
		double* pIV = *pInv++;
		
		for( int j = 0; j < nDim; j++ )
			*pIV++ = *pIV / det;
		
	}
}

double Det( double** pMatrix, int nDim )
{
	

	if( nDim == 1 )
		return **pMatrix;

	if( nDim == 2 )
		return pMatrix[0][0] * pMatrix[1][1] - pMatrix[0][1] * pMatrix[1][0];

	

	double** pTabPom = NULL;

	if( !CreateMatrix( &pTabPom, nDim - 1 ) )
	{
		perror( "Alocation problem" );
		return DBL_MIN;
	}

	double det = 0;
	double* pMO = *pMatrix;
	double sign = 1;


	for( int i = 0; i < nDim; i++ )
	{
		Complement( pTabPom, pMatrix, 0, i, nDim );
		det += sign * *pMO++ * Det( pTabPom, nDim - 1 );
		sign = -sign;
	}

	
	DeleteMatrix( &pTabPom, nDim-1 );
	return det;
}

void LayoutEqu( double** pInv, double* pB, double* pRes, int nDim )
{
	
	/*for( int i = 0; i < nDim; i++ )
	{
		double temp = 0;

		for( int j = 0; j < nDim; j++ )
		{
			pRes[i] += pInv[i][j] * pB[j];
		}
	
	}*/
	
	
	for( int i = 0; i < nDim; i++,pRes++ )
	{
		double* x = pB;
		double* pIV = *pInv++;
		for( int j = 0; j < nDim; j++ )
			*pRes +=  *pIV++ * *x++ ;	
	}

}

void PrintMatrix( double** pMatrix, int nDim )
{
	for( int i = 0; i < nDim; i++ )
	{
		double* pM = *pMatrix++;
		for( int j = 0; j < nDim; j++ )
		{
			printf( "%lf ", *pM++ );
		}
		printf( "\n" );
	}
}

void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim )
{
	for( int i = 0; i < nDim; i++ )
	{
		
		double* pTI = *pTabI++;

		if( i == nRow )
			continue;
		double* pTO = *pTabO++; // zeby pomnielo w continue
		for( int j = 0; j < nDim; j++ )
		{
			if( j == nCol )
			{
				pTI++;
				continue;
			}
			*pTO++ = *pTI++;
		}

	}

}

void ComplMatrix( double** pTabD, double** pMatrix, int nDim )
{
	double** pTabPom = NULL;
	if( !CreateMatrix( &pTabPom, nDim ) )
	{
		perror( "Blad alokacjij pamieci ComplMatrix" );
		return;
	}
	for( int i = 0; i < nDim; i++ )
	{
		double* pTD = *pTabD++;
		int coef = ( i % 2 ) ? -1:1;
		for( int j = 0; j < nDim; j++ )
		{
			Complement( pTabPom, pMatrix, i, j, nDim );
			*pTD++ = coef*Det( pTabPom, nDim - 1 );
			coef = -coef;
		}
	}
	DeleteMatrix( &pTabPom, nDim );
}