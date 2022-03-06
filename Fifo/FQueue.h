#ifndef _FQUEUE_H
#define _FQUEUE_H

typedef struct
{
    int n_Key;
} QInfo;

typedef struct tagQFItem // musi byc tu nazwa bo inaczej nie wykrywa wewnatrz strukutry ze ta jest zdefiniowana
{   
    QInfo* pInfo;
    tagQFItem* pNext;
} QFItem;

typedef struct
{
    QFItem* pHead;
    QFItem* pTail;
} QFIFO;

QFIFO* QFCreate();
int QFEmpty( QFIFO* q );
int QFEnqueue( QFIFO* q, QInfo* pInfo );
QInfo* QFDequeue( QFIFO* q );
void  QFClear( QFIFO* q );
void  QFRemove( QFIFO** q );


#endif
