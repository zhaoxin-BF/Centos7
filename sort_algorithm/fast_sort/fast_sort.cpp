#include<iostream>

using namespace std;

void Swap(int& a,int& b){
	a = a - b;
	b = a + b;
	a = b - a; 
}

int postion(int* arr,int left,int right){
	
	int tmp = arr[left];
	
	while(left < right){
	
		while(tmp<arr[right] && left < right) 
			right--;
		arr[left] = arr[right];
		
		while(left < right && tmp > arr[left])
			left++;
		arr[right] = arr[left];
		}
	arr[left] = tmp;
	return left;
}

void fast_sort(int* arr, int left, int right){

	if(left < right){
		int pos  = postion(arr,left,right);
		fast_sort(arr,left,pos-1);
		fast_sort(arr,pos+1,right);
		}
}

void Print(int arr[],size_t size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

int main(){
	int arr[10] = {1,4,2,3,5,6,7,9,8,0};
	fast_sort(arr,0,9);
	Print(arr,10);
	return 0;
}
