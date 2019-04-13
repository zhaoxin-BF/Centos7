#include<iostream>
#include<unistd.h>

using namespace std;

int main()
{
  cout<<"job begin"<<endl;
  pid_t id = fork();
  if(id == 0){
    while(1){
      cout<<"child"<<endl;
      sleep(2);
    }
  }
  else{
    while(1){
      cout<<"parent"<<endl;
      sleep(1);
    }
  }
}
