#include<iostream>
#include<string>


using namespace std;

int main()
{
	string s;
	cin>>s;
	string::iterator it = s.begin();
	while(it != s.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
	return 0;
	}
