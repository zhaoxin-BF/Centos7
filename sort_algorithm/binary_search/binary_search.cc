#include <iostream>

using namespace std;

int binary(int *arr,int size,int key)
{
	int low = 0;
	int high = size-1;
	int mid;

	while(low <= high)
	{
		if(arr[low] == key)
			return low;
		if(arr[high] == key)
			return high;

		mid = (low+high)/2;
		if(arr[mid] == key)
			return mid;
		if(arr[mid]<key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	if(low>high)
		return -1;
}

int main()
{
	int arr[] = {1,2,3,4,5,6,7,8,9,10};
	int ret = binary(arr,10,10);
	cout<<ret<<endl;
}
