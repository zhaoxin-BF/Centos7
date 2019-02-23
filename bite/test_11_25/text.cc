#include<iostream>
#include<list>
using namespace std;


int main()
{
  list<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  list<int>::iterator lit = l.begin();
  while( lit != l.end())
  {
    cout << *lit<<" ";
    ++lit;
  }
  cout << endl;
  cout<<"Hello world!"<<endl;
  return 0;
}
