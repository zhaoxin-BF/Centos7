#include<iostream>
#include<set>


using namespace std;

int main()
{
	set<int> s;
	s.insert(3);
	s.insert(4);
	s.insert(5);
	s.insert(6);
	s.insert(7);
	
	//s.erase(3);
	//s.erase(s.find(4));
	

	set<int>::iterator it = s.find(6);
	s.erase(it,s.end());
	it = s.begin(); 
	while(it != s.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
	return 0;
	}
