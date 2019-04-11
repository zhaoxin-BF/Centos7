#include "cp.hpp"
using namespace std;

const int num = 32;
//生产者和消费者两个线程一个不断的Push数据，一个不断的Pop数据

void* consume_routinue(void* arg)
{
    int data = 0;
    BlockQueue *bqp = (BlockQueue*)arg;
    for(;;)
    {
        bqp->PopData(data);
        cout<<"consume done,data is :"<<data<<endl;
        //上一句的data没有加*是因为C++的引用。
    }
}

void* product_routinue(void* arg)
{
    BlockQueue *bqp = (BlockQueue*)arg;
    srand((unsigned long)time(NULL));
    //利用系统时间生成一系列的随机数。
    //srand原型srand(unsigned seed)
    for(;;)
    {
        int data = rand()%100+1;
        //100~1的随机数
        bqp->PushData(data);
        cout<<"Product is done, data is :"<<data<<endl;
        sleep(1);
    }
}

int main()
{
    BlockQueue *bqp = new BlockQueue(num);
    //C++中的new不需要判断，因为new失败的时候，程序会抛出异常。
    pthread_t c,p;
    pthread_create(&c,NULL,consume_routinue,(void*)bqp);
    pthread_create(&p,NULL,product_routinue,(void*)bqp);

    pthread_join(&c,NULL);
    pthread_join(&p,NULL);
    delete(bqp);
    return 0;
}
