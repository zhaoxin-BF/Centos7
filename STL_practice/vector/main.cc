#include<iostream>
#include<vector>


using namespace std;

int main()
{
	vector<int> v;
	int i,n,tmp;
	cin >> n;
	for(i = 0;i < n;i++)
	{
		cin>>tmp;
		v.push_back(tmp);
	}

	vector<int>::iterator it = v.begin();
	while(it != v.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
	return 0;
	}
