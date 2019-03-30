#include "Heap.h"

int main()
{
    Heap hp;
    _HPDataType array[] = {12,34,56,76,87,97,46,64,62};
    InitHeap(&hp,array,sizeof(array)/sizeof(array[0]));

    PushHeap(&hp,123);
    Print(&hp);
    
    PopHeap(&hp);
    HeapSort(&hp);
    Print(&hp);
    return 0;
}
