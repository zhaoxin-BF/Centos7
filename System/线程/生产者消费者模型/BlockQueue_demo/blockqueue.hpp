//条件编译
#ifndef _BLOCKQUEUE_H__
#define _BLOCKQUEUE_H__ 

#include <iostream>
#include <queue>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

class BlockQueue{
  private:
    std::queue<int> bq;
    int cap;
    pthread_mutex_t lock;
    pthread_cond_t cond_p;//队列为空通知生产者
    pthread_cond_t cond_c;//队列为满通知消费者
  private:
    void LockQueue()
    {
      pthread_mutex_lock(&lock);
    }
    void UnlockQueue()
    {
      pthread_mutex_unlock(&lock);
    }
    void ConsumeWait()
    {
      pthread_cond_wait(&cond_c,&lock);
    }
    void ProductWait()
    {
      pthread_cond_wait(&cond_p,&lock);
    }

    bool IsFull()
    {
      return bq.size()==cap?true:false;
    }
    bool IsEmpty()
    {
      return bq.size()==0?true:false;
    }
    void SignalConsume()
    {
      pthread_cond_signal(&cond_c);
    }
    void SignalProduct()
    {
      pthread_cond_signal(&cond_p);
    }
  public:
    BlockQueue(int _cap):cap(_cap)
    {
      pthread_mutex_init(&lock,NULL);
      pthread_cond_init(&cond_c,NULL);
      pthread_cond_init(&cond_p,NULL);
    }

    void PopData(int &data)
    {
      LockQueue();
      while(IsEmpty())
      {
        SignalProduct();
        ConsumeWait();
      }
      data = bq.front();
      bq.pop();
      UnlockQueue();
    }

    void PushData(const int &data)
    {
      LockQueue();
      while(IsFull())
      {
        SignalConsume();
        ProductWait();
      }
      bq.push(data);
      UnlockQueue();
    }

    ~BlockQueue()
    {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&cond_c);
      pthread_cond_destroy(&cond_p);
    }
};

#endif 
