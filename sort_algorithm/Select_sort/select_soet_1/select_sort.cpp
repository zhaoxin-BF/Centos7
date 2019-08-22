#include <iostream>
using namespace std;

void print(int* arr, int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void swap(int &a, int &b)
{
    a = a - b;
    b = a + b;
    a = b - a;
}

void select_sort(int* arr, int size)
{
    int i ,j;
    int min;
    for(i=0;i<size;i++)
    {
        min = i;
        for(j=i+1;j<size;j++)
        {
            if(arr[j] < arr[min])
                min = j;
        }
        if(min != i)
            swap(arr[i], arr[min]);
    }
}

int main()
{
    int arr[10] = {0,2,5,8,7,9,6,4,1,3};
    print(arr, 10);
    select_sort(arr, 10);
    print(arr, 10);
    return 0;
}
