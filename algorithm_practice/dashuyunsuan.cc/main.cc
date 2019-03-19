#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main()
{
	string a , b;
	int crr[101] = {0};
	int arr[101] = {0};
	int brr[101] = {0};
	cin>>a;
	cin>>b;

	int i,j;
	for(j=0,i = a.size()-1; i >=0;i--,j++)
	{
		arr[j] = a[i]-48;
	}
	for(j=0,i = b.size()-1; i >=0;i--,j++)
	{
		brr[j] = b[i]-48;
	}
	int tmp=0;
	int tpp = 0;
	for(i = 0; i < 101; i++)
	{
		tpp = arr[i]+brr[i];
		crr[i] = tmp+tpp%10;
		tmp = tpp/10;
	}
	for(i = 100;i>=0;i--)
	{
		if(crr[i] != 0)
			break;
	}
	for(; i>=0;i--)
	{
		cout<<crr[i];
	}
	cout<<endl;
	return  0;
}
