#ifndef _MATRIX_H
#define _MATRIX_H

int CreateMatrix( double*** pMatrix, int nDim );
void DeleteMatrix( double*** pMatrix, int nDim );
void TransMatrix( double** pMatrix, int nDim );
void InverseMatrix( double** pInv, double** pMatrix, int nDim, double det );
double Det( double** pMatrix, int nDim );
void LayoutEqu( double** pInv, double* pB, double* pRes, int nDim );
void PrintMatrix( double** pMatrix, int nDim );


#endif
