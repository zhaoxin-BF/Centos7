#ifndef __LIST_H
#define __LIST_H 

#include<iostream>
#include<malloc.h>
using namespace std;

typedef int DataType;

typedef struct Node
{
  DataType _data;
  struct Node* _pNext;
}Node,*LNode;

void InitList(LNode* pHead);
LNode BuyNode(DataType data);
#endif 


//初始化链表
void InitList(LNode* pHead)
{
  *pHead = NULL;
}

//创建新节点
LNode BuyNode(DataType data)
{
  LNode NewNode =(Node*)malloc(sizeof(Node));

  NewNode->_data = data;
  NewNode->_pNext = NULL;

  return NewNode;
}

//尾插新的节点
void PushBack(LNode* pHead ,DataType data)
{
  if(*pHead == NULL){
    *pHead = BuyNode(data);
  }
  else{
    LNode pCur = *pHead;
    while(pCur->_pNext)
    {
     pCur = pCur->_pNext;
    }
    pCur->_pNext = BuyNode(data);
  }
}
//打印链表
void PrintList(LNode* pHead)
{
  LNode pCur = *pHead;
  while(pCur)
  {
    cout<<pCur->_data<<"-> ";
    pCur = pCur->_pNext;
  }
  cout<<"NULL"<<endl;
}

//单链表逆至
void RList(LNode* pHead)
{
  LNode p1 = (*pHead)->_pNext;
  LNode p2 = p1;
  (*pHead)->_pNext = NULL;
  while(p1)
  {
    p2 = p1->_pNext;
    p1->_pNext = *pHead;
    *pHead = p1;
    p1 = p2;
  }
}
