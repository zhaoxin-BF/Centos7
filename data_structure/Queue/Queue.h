#ifndef __QUEUE_H
#define __QUEUE_H 

#include<iostream>
#include<malloc.h>
using namespace std;

typedef int QDataType;

typedef struct pNode{
  QDataType _data;
  struct pNode* _pNext;
}pNode,*PNode;

typedef struct Queue{
  PNode _phead;
  PNode _pTail;
}Queue;

void InitQueue(Queue* q);
void PushQueue(Queue* q,QDataType data);
void PopQuene(Queue* q);
QDataType QueueFront(Queue* q);
QDataType QUeueBack(Queue* q);
PNode BuyNode(QDataType data);
int SizeQueue(Queue* q);
int EmptyQueue(Queue* q);
void PrintQueue(Queue* q);

#endif 

void InitQueue(Queue* q){
  q->_phead =NULL;
  q->_pTail =NULL;
}

void PushQueue(Queue* q,QDataType data){
  if(q->_phead == NULL)
    q->_phead =q->_pTail = BuyNode(data);
  else{
    q->_pTail->_pNext = BuyNode(data);
    q->_pTail = q->_pTail->_pNext;
  }
}

void PopQuene(Queue* q){
  if(q->_phead != NULL){
    PNode DelNode = q->_phead;
    q->_phead = DelNode->_pNext;
    free(DelNode);
  }
}

QDataType QueueFront(Queue* q){
  return q->_phead->_data;
}

QDataType QUeueBack(Queue* q){
  return q->_pTail->_data;
}

PNode BuyNode(QDataType data){
  PNode NewNode = (pNode*)malloc(sizeof(pNode));
  NewNode->_data = data;
  NewNode->_pNext = NULL;
  return NewNode;
}

int SizeQueue(Queue* q)
{
  int size = 0;
  PNode pCur = q->_phead;
  while(pCur)
  {
    size++;
    pCur = pCur->_pNext;
  }
  return size;
}
int EmptyQueue(Queue* q){
  if(q->_phead == NULL)
    return 1;
  else 
    return 0;
}
void PrintQueue(Queue* q){
  PNode pCur = q->_phead;
  while(pCur)
  {
    cout<<pCur->_data<<" ";
    pCur = pCur->_pNext;
  }
  cout<<endl;
}
