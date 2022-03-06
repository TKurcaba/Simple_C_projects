#pragma once
typedef struct
{
	int nKey;
	int* p;
} ListInfo;

#define LISTINFO ListInfo
void freeInfo( const void* );
int CompareInfo( const void*, const void* );
