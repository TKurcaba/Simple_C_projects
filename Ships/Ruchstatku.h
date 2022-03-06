#ifndef _RUCHSTATKU_H
#define _RUCHSTATKU_H

int move( int** pDepthTab, int nRow, int nCol, int nDepth,
    int nextMove, int x, int y, int* px, int* py, int** pRoot );
int root( int** pDepthTab, int nRow, int nCol, int nDepth,
	int x, int y, int** pRoot, int x_dest, int y_dest );
int readDepthTab( char* sFile, int** pTab, int nRow, int nCol );
int** createTab( int nRow, int nCol );
void printTab( int** pRoot, int nRow, int nCol );
void freeTab( int*** pTab );

#endif