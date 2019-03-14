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
	for(i = 0;i < n;i++)
	{
		cout<<arr[i]._name<<" "<<arr[i]._score<<endl;
	}
}

int main()
{
	stu arr[100];
	int n,i;
	cin >> n;
	for(i = 0;i < n;i++)
	{
		cin>>arr[i]._name>>arr[i]._sex>>arr[i]._age>>arr[i]._score;
	}
	Print(arr,n);
	return 0;
}
