#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
    a = a - b;
    b = a + b;
    a = b - a;
}

int position(int* arr, int left, int right)
{
    int mid = arr[left];
    while(left < right)
    {
        while(left < right && arr[right] >= mid) right--;
            arr[left] = arr[right];
        while(left < right && arr[left] <= mid) left++;
            arr[right] = arr[left];
    }
    arr[left] = mid;
    return left;
}

void fast_sort(int* arr, int left, int right)
{
    if(left < right)
    {
        int mid = position(arr, left, right);
        fast_sort(arr, left, mid-1);
        fast_sort(arr, mid+1, right);
    }
}

void print(int* arr, int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    int arr[10] = {5, 8, 5, 9, 1, 2, 3, 6, 4, 0};
    print(arr, 10);
    fast_sort(arr, 0, 9);
    print(arr, 10);
    return 0;
}
