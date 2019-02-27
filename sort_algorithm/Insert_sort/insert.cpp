#include<iostream>
using namespace std;

void Print(int array[],size_t size)
{
  int i;
  for(i = 0;i < size; i++)
  {
    cout<<array[i]<<" ";
  }
  cout<<endl;
}

void Swap(int& a, int& b)
{
  a = a - b;
  b = a + b;
  a = b - a;
}

void insert_sort(int array[],size_t size)
{
  int i , j , tmp , num;
  for(i = 1;i < size;i++)
  {
    num = i;
    for(j = i;j>0;j--)
    {
      if(array[j-1] <= array[i])
        break;
    }
    tmp = array[num];
    for( ; num > j; num--)
    {
      array[num] = array[num-1];
    }
    array[j] = tmp;
  }
}

int main()
{
  int array[10] = {1,3,5,7,9,2,4,6,8,0};
  Print(array,10);
  insert_sort(array,10);
  Print(array,10);
  return 0;
}
