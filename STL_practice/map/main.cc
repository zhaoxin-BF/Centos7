#include<iostream>
#include<map>


using namespace std;

int main()
{
	map<char,int> m;
	m['a'] = 20;
	m['d'] = 60;
	m['b'] = 40;
	m['c'] = 10;

	map<char,int>::iterator itt = m.find('c');
	//cout<<it->first<<" "<<it->second<<endl;
	
	m.erase(itt,m.end());
	m.clear();
	
	cout<<m.size()<<endl;
	map<char,int>::iterator it = m.begin();
	while(it != m.end())
	{
		cout<<it->first<<" "<<it->second<<endl;
		it++;
	}

	/*vector<int>::iterator it = v.begin();
	while(it != v.end())
	{
		cout<<*it<<" ";
		++it;
	}*/
	cout<<endl;
	return 0;
	}
