#include"Queue.h"

int main()
{
  Queue q;
  InitQueue(&q);
  PushQueue(&q,1);
  PushQueue(&q,2);
  PushQueue(&q,3);
  PushQueue(&q,4);
  
  PopQuene(&q);
  
  cout<<EmptyQueue(&q)<<endl;
  cout<<QueueFront(&q)<<endl;
  cout<<QUeueBack(&q)<<endl;
  cout<<SizeQueue(&q)<<endl;

  PrintQueue(&q);
  return 0;
}
