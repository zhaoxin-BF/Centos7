#include "blockqueue.hpp"
using namespace std;

const int num = 5;
//生产者和消费者一个不断push数据进入队列，一个不断读取数据从队列

void* consume_routinue(void* arg)
{
  int data = 0;
  BlockQueue *bqp=(BlockQueue*)arg;
  for(;;)
  {
    bqp->PopData(data);
    cout<<"consume done, data is:"<<data<<endl;
    sleep(1);
  }
}

void* product_routinue(void* arg)
{
  BlockQueue *bqp = (BlockQueue*)arg;

  srand((unsigned long)time(NULL));
  for(;;)
  {
    int data = rand()%100 + 1;
    bqp->PushData(data);
    cout<<"product is done, data is:"<<data<<endl; 
    sleep(1);
  }
}

int main()
{
  BlockQueue *bqp = new BlockQueue(num);

  pthread_t c,p;
  pthread_create(&c, NULL, consume_routinue,(void*)bqp);
  pthread_create(&p, NULL, product_routinue,(void*)bqp);

  pthread_join(&c, NULL);
  pthread_join(&p, NULL);

  delete(bqp);
  return 0;
}
