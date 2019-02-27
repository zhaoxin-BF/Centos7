#include<iostream>
using namespace std;

void Swap(int& a,int& b)
{
  a = a - b;
  b = a + b;
  a = b - a;
}

void bulle_sort(int array[],size_t size)
{
  int i , j;
  for(i = 0;i < size - 1;i++ )
  {
    for(j = 0;j < size-1-i;j++)
    {
      if(array[j] > array[j+1])
      {
        Swap(array[j],array[j+1]);
      }
    }
  }
}

void Print(int array[],size_t size)
{
  int i;
  for(i = 0 ;i < size ;i++ )
  {
    cout<<array[i]<<" ";
  }
  cout<<endl;
}

int main()
{
  int array[10] = {1,3,5,7,8,9,0,6,4,2};
  Print(array,10);
  bulle_sort(array,10);
  Print(array,10);
  return 0;
}
