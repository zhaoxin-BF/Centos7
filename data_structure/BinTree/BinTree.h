#ifndef __BINTREE_H
#define __BINTREE_H

#include<iostream>
#include<malloc.h>
using namespace std;

typedef char DataType;

typedef struct BinTree{
  DataType _data;
  struct BinTree* _left;
  struct BinTree* _right;
}Node,*BTNode;

BTNode BuyNode(DataType data);
void CreateBinTree(BTNode* pRoot, DataType array[], size_t size, int* index, DataType invilid);
void PrintBinTree(BTNode pRoot);
#endif

BTNode BuyNode(DataType data)
{
  BTNode NewNode = (Node*)malloc(sizeof(Node));
  NewNode->_data = data;
  NewNode->_left = NULL;
  NewNode->_right = NULL;

  return NewNode;
}

void CreateBinTree(BTNode* pRoot, DataType array[], int size,  size_t* index,DataType invalid)
{
  if((*index < size) && (invalid != array[*index]))
  {
    *pRoot = BuyNode(array[*index]);

    ++(*index);
      CreateBinTree(&(*pRoot)->_left, array,size,index,invalid);

    ++(*index);
      CreateBinTree(&(*pRoot)->_right ,array,size,index,invalid);
  }
}

void PrintBinTree(BTNode pRoot)
{
  if(pRoot)
  {
    cout<<pRoot->_data<<" ";

    PrintBinTree(pRoot->_left);

    PrintBinTree(pRoot->_right);
  }
}

int SizeBinTree(BTNode pRoot)
{
  if(pRoot == NULL)
  {
    return 0;
  }
  return 1+SizeBinTree(pRoot->_left)+SizeBinTree(pRoot->_right);
}
