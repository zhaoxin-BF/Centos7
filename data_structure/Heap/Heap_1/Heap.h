#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

typedef int _HPDataType;

typedef struct Heap
{
    _HPDataType* _array;
    int _size;
    int _capacity;
}Heap;

void Swap(_HPDataType *a, _HPDataType *b);
void Adjustdown(_HPDataType* a, int size, int root);
void Adjustup(_HPDataType* a, int size, int child);

void InitHeap(Heap* hp, _HPDataType *array, int n);
void DestoryHeap(Heap* hp);

void PushHeap(Heap* hp, _HPDataType data);
void PopHeap(Heap* hp);

_HPDataType TopHeap(Heap* hp);

int SizeHeap(Heap* hp);
int isEmptyHeap(Heap* hp);

void HeapSort(Heap* hp);
void Print(Heap* hp);

#endif

void Swap(_HPDataType *a,_HPDataType *b)
{
    *a = *a - *b;
    *b = *a + *b;
    *a = *b - *a;
}

void Adjustdown(_HPDataType *a,int size, int root)
{
    int parent = root;
    int child = root*2+1;
    while(child < size)
    {
        if(child+1<size && a[child] < a[child+1])
            child++;
        if(a[parent]<a[child])
        {
            Swap(&a[parent],&a[child]);
            parent = child;
            child = parent*2+1;
        }
        else
            break;
    }
}

void Adjustup(_HPDataType* a, int size, int child)
{
    int parent = (child-1)/2;
    while(child > 0)
    {
        if(a[parent]<a[child])
        {
            Swap(&a[parent],&a[child]);
            child = parent;
            parent = (child-1)/2;
        }
        else
            break;
    }
}

void InitHeap(Heap* hp,_HPDataType *array,int n)
{
    hp->_array = (_HPDataType*)malloc(sizeof(_HPDataType)*n);
    hp->_size = n;
    hp->_capacity = n;
    
    int i;
    for(i = 0;i < n;i++)
    {
        hp->_array[i] = array[i];
    }
    for(i = (n-1)/2; i>=0;i--)
    {
        Adjustdown(hp->_array,hp->_size,i);
    }
}

void DeatoryHeap(Heap* hp)
{
    free(hp->_array);
    hp->_size = 0;
    hp->_capacity = 0;
}

void PushHeap(Heap* hp, _HPDataType data)
{
    if(hp->_capacity == hp->_size)
    {
        hp->_array = (_HPDataType*)realloc(hp->_array, sizeof(_HPDataType)*hp->_capacity * 2);
        hp->_capacity *=2;
    }

    hp->_array[hp->_size] = data;
    hp->_size++;
    Adjustup(hp->_array,hp->_size,hp->_size-1);
}
void PopHeap(Heap* hp)
{
    Swap(&hp->_array[0],&hp->_array[hp->_size-1]);
    hp->_size-=1;
    Adjustdown(hp->_array,hp->_size,0);
}

_HPDataType TopHeap(Heap* hp)
{
    return hp->_array[0];
}

int SizeHeap(Heap* hp)
{
    return hp->_size;
}

int isEmptyHeap(Heap* hp)
{
    if(hp->_size != 0)
        return 1;
    else
        return 0;
}

void  HeapSort(Heap* hp)
{
    int i;
    for(i = 1;i<hp->_size;i++)
    {
        Swap(&hp->_array[0],&hp->_array[hp->_size-i]);
        Adjustdown(hp->_array,hp->_size-i,0);
    }
}

void Print(Heap *hp)
{
    int i;
    for(i=0; i<hp->_size; i++)
    {
        printf("%d ",hp->_array[i]);
    }
    printf("\n");
}

