#include<iostream>
using namespace std;

void Swap(int* a,int* b)
{
  *a =*a - *b;
  *b =*a + *b;
  *a =*b - *a;
}

void select_sort(int array[],size_t size)
{
  int i , j ,max;
  for(i = 0; i < size-1; i++)
  {
    max = 0;
    for(j = 1; j < size-i; j++)
    {
      if(array[max] > array[j])
        Swap(&array[max],&array[j]);
      max = j;
    }
  }
}

void Print(int array[],size_t size)
{
  int i;
  for(i = 0;i < size; i++)
  {
    cout<<array[i]<<" ";
  }
  cout<<endl;
}

int main()
{
  int array[10] = {1,3,5,7,9,0,8,6,4,2};
  Print(array,10);
  select_sort(array,10);
  Print(array,10);
  return 0;
}
