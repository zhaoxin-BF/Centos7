#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
	char arr[100];
	int i, n, count = 0;
	char tmp;
	for(i = 0; i < 100;)
	{
		if((tmp = getchar()) == '\n')
			break;
		else
		{
			if(tmp == '0')
				count++;
			else if(tmp != ' ')
			{
				arr[i] = tmp;
				i++;
			}
		}
	}
	n = i;
	for(i = 0; i < n;i++)
	{
		cout<<arr[i]<<" ";
	}
	for(i = 0;i < count;i++)
	{
		cout<<"0"<<" ";
	}
	cout<<endl;
	return 0;
}
