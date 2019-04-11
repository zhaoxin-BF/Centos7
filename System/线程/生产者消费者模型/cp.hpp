//hpp是一个头文件，这个头文件有一个特点就是可以把实现也写在里面
//条件编译
#ifndef __CP_HPP__ //如果没有定义cp.hpp
#define __CP_HPP__ //定义cp.hpp

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
        pthread_cond_t cond_p; //队列为空时使用这个信号
        pthread_cond_t cond_c; //队列满的时候使用这个信号
    private:
        void LockQueue()
        {
            pthread_mutex_lock(&lock);
        }
        void UnlockQueue()
        {
            pthread_mutex_unlock(&lock);
        }
        void ProductWait()
        {
            pthread_cond_wait(&cond_p,&lock);
        }
        void ConsumeWait()
        {
            pthread_cond_wait(&cond_c,&lock);
        }
        bool IsFull()
        {
            return bq.size() == cap?true:false;
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
        BlockQueue(int cap_):cap(cap_)  //构造函数，参数列表把cap放进去。
        //上句话的意思相当于：
        //BloclQueue(int cap_)
        //{
        //    cap = cap_;
        //}

        {
            pthread_mutex_init(&lock,NULL);
            pthread_cond_init(&cond_p,NULL);
            pthread_cond_init(&cond_c,NULL);
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
        void PopData(int &data)
        {
            LockQueue();
            while(IsEmpty())
            {
                SignalProduct();
                ConsumeWait();
            }

            //bq.front拿出头部信息，STL中的queue使用pop时，数据会直接抛弃，因此未使用pop
            data = bq.front();
            bq.pop();
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
