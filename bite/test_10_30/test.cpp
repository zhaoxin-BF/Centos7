#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>

using namespace std;

void handler(int signo )
{
  cout<<" get a sigon: "<<signo<< "pid :"<<getpid()<<endl;
  sleep(1);
}
int main()
{
  signal(2,handler);
  while(1)
  {
    cout<<"hello "<<endl;
    sleep(1);
  }
  return 0;
}
