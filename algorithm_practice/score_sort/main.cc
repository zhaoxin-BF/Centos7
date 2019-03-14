#include<iostream>
#include<stdio.h>
#include<string>
#include<stdlib.h>

#define MAXLINE 100;

using namespace std;

typedef struct student
{
	string _name;
	string _sex;
	int _age;
	int _score;
}stu;

void Print(stu *arr,int n)
{
	int i;
	cout<<endl;
	cout<<"Puts:"<<endl;
	for(i = 0;i < n;i++)
	{
		cout<<arr[i]._name<<" "<<arr[i]._score<<endl;
	}
	cout<<endl;
}

int main()
{
	stu arr[100];
	int n,i;
	cout<<"Please input number:"<<endl;
	cin >> n;
	for(i = 0;i < n;i++)
	{
		cin>>arr[i]._name>>arr[i]._sex>>arr[i]._age>>arr[i]._score;
	}
	
	int k,j;
	stu tmp;

	for(k = 1;k < n; k++)
	{
		for(j = 0; j < n-k; j++)
		{
			if(arr[j]._score > arr[j+1]._score)
			{
				tmp = arr[i];
				arr[i] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
	}

	Print(arr,n);
	return 0;
}
