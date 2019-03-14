#include<iostream>
#include<list>


using namespace std;

int main()
{
	list<int> v;
	int i,n,tmp;
	cin >> n;
	for(i = 0;i < n;i++)
	{
		cin>>tmp;
		v.push_back(tmp);
	}

	list<int>::iterator it = v.begin();
	while(it != v.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
	return 0;
	}
