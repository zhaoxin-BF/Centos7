#include<iostream>
#include"Stack.h"
using namespace std;

int main()
{
	Stack s;
    InitStack(&s);

    PushStack(&s, 1);
    PushStack(&s, 2);
    PushStack(&s, 3);
    PushStack(&s, 4);
    PushStack(&s, 5);
    
    PrintStack(&s);
    cout<<TopStack(&s)<<endl;
   
    PrintStack(&s);
    PopStack(&s);
    PrintStack(&s);
	return 0;
}
