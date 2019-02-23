#ifndef __STACK_H
#define __STSCK_H

#include<iostream>
#include<malloc.h>
using namespace std;

typedef int DataType;

typedef struct Stack{
  DataType* _array;
  int _capacity;
  int _top;
}Node,*PNode;

void InitStack(PNode s){
  s->_capacity = 3;
  s->_top = -1;

  s->_array = (DataType*)malloc(sizeof(DataType)*s->_capacity);

}

#endif 
