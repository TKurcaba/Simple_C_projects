#ifndef _GLOBAL_H
#define _GLOBAL_H

typedef struct QInfo
{
    int n_Key;
    int* pTab; 
} QInfo;

#define QFITEM QInfo    

void freeItem( const void* x );

#endif
