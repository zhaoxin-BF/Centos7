#include <iostream>
using namespace std;

void insert_sort(int* arr, int size)
{
    int tmp;
    int i, j;
    for(i = 1; i <size ;i++)
    {
        tmp = arr[i];
        j=i;
        while( j>0 &&  arr[j-1] > tmp)
        {
            arr[j] = arr[j-1];
            j--;
        }
        arr[j] = tmp;
    }
}

void print(int *arr, int size)
{
    int i;
    for(i = 0;i <size ;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    int arr[10] = {1,3,5,1,9,7,6,4,0,2};
    insert_sort(arr, 10);
    print(arr, 10);
    return 0;
}
