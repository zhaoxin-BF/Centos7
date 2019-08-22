#include <iostream>
using namespace std;

void swap(int& a, int& b)
{
    a = a - b;
    b = a + b;
    a = b - a;
}

void Bubble_sort(int* arr, int size)
{
    int i, j;
    for(i = 1;i<size;i++)
    {
        for(j = 0;j<size-i;j++)
        {
            if(arr[j]<arr[j+1])
                swap(arr[j],arr[j+1]);
        }
    }
}

void print(int* arr, int size)
{
    int i;
    for(int i = 0; i< size ;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    int arr[10] = {9,7,5,2,4,8,6,3,1,0};
    Bubble_sort(arr,10);
    print(arr,10);
    return 0;
}
