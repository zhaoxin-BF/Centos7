#include<iostream>
using namespace std;

void Swap(int& a, int& b)
{
  a = a - b;
  b = a + b;
  a = b - a;
}

void insert_sort(int array[], size_t size)
{
  int i, j, tmp = 0;
  for (i = 1; i < size; i++)
  {
    for (j = i - 1; j >= 0; j--)
    {
      if (array[j] > array[i])
        ;
      else
      {
        break;
      }
    }
    tmp = i;
    while (tmp != j + 1)
    {
      Swap(array[tmp], array[tmp - 1]);
      tmp--;
    }
  }
}

void Print(int array[], size_t size)
{
  int i;
  for (i = 0; i < size; i++)
  {
    cout << array[i] << " ";         
  }
  cout << endl;
}

int main()
{
  int array[10] = { 2, 1, 6, 8, 0, 4, 3, 5, 7, 9  };
  Print(array,10);
  insert_sort(array, 10);
  Print(array, 10);
  return 0;
}
