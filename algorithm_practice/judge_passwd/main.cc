#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s;
	
	cout<<"请输入密码：不能小于8位，必须含有大小写字母，数组或其他字符中的三种！"<<endl;
	cin>>s;
	if(s.size()<=8)
	{
		cout<<"INVALID"<<endl;
		return 0;
	}
	int a=0,b=0,c=0,d=0;
	string::iterator it = s.begin();
	while(it != s.end())
	{
		if(d<s.size()-2)
			if(s[d]==s[d+1]&&s[d+2]==s[d])
			{
				cout<<"INVALID"<<endl;
				return 0;
			}

		if('A' >= *it && *it <= 'Z')
		{
			a = 1;
			d++;
		}
		if('a' >= *it && *it <= 'z')
		{
			b = 1;
			d++;
		}
		if('0' <= *it && *it <= '9')
		{
			c = 1;
			d++;
		}
		it++;
	}
	if(d != s.size())
		d = 1;
	cout<<"a = "<<a<<endl;
	cout<<"b = "<<b<<endl;
	cout<<"c = "<<c<<endl;
	cout<<"d = "<<d<<endl;

	if((a+b+c+d)<3)
	{
		cout<<"INVALID"<<endl;
		return 0;
	}
	return 0;
}
