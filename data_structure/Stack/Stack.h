#ifndef __STACK_H
#define __STSCK_H

#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

using namespace std;

typedef int DataType;

typedef struct Stack
{
  DataType* _array;
  int _capacity;
  int _top;
}Stack;

void InitStack(Stack* s);
void PushStack(Stack* s, DataType data);
void PopStack(Stack* s);
void NewCapacity(Stack* s);
int TopStack(Stack* s);
void PrintStack(Stack* s);

#endif

void InitStack(Stack* s){
  s->_capacity = 3;
  s->_top = -1;

  s->_array = (DataType*)malloc(sizeof(DataType)*s->_capacity);
}

void PushStack(Stack* s, DataType data)
{
    s->_top++;
    if(s->_top < s->_capacity)
    {
        s->_array[s->_top] = data;
    }
    else
    {
        NewCapacity(s);
        s->_array[s->_top] = data;
    }
}

void PopStack(Stack* s)
{
    if(s->_top > -1)
    {
        s->_top--;
    }
}

void NewCapacity(Stack* s)
{
    int newcapacity = 2 * s->_capacity;
    DataType* Newarray = (DataType*)malloc(sizeof(DataType) * newcapacity);

    memcpy(Newarray, s->_array, sizeof(DataType)*s->_capacity);
    free(s->_array);

    s->_array = Newarray;
    s->_capacity = newcapacity;
}

int TopStack(Stack* s)
{
    return s->_array[s->_top];
}

void PrintStack(Stack* s)
{
    int n  = s->_top;
    while(n > -1)
    {
        cout<<s->_array[n--]<<" ";
    }
    cout<<endl;
}
