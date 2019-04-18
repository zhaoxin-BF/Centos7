#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

//节点结构
typedef struct node
{
    int data;
    struct node* next;
}Node;

//添加一把锁,线程同步，互斥锁
pthread_mutex_t mutex;
//阻塞线程，添加一个条件变量
pthread_cond_t cond;



//永远指向链表头部的指针
Node* head = NULL;

void* producer(void* arg)
{
    while(1)
    {
        Node* pnew = (Node*)malloc(sizeof(Node));
        //节点的初始化,0-999
        pnew->data = rand() % 1000;
        //使用互斥锁保护共享资源
        pthread_mutex_lock(&mutex);
        //指针域初始化
        pnew->next = head;
        head = pnew;
        printf("======= produce: %lu, %d\n", pthread_self(), pnew->data);
        pthread_mutex_unlock(&mutex);
        
        //通知阻塞的消费者线程， 解除阻塞
        pthread_cond_signal(&cond);
        
        sleep(rand() % 3);
    }
    return NULL;
}

void* customer(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        //判断链表是否为空
        if(head == NULL)
        {
            //线程阻塞，（没有数据就阻塞），阻塞代码，并且能够解锁
            pthread_cond_wait(&cond, &mutex);
            //解除阻塞之后，通知对方，对互斥锁做加锁操作

        }
        //链表不为空，删除一个节点，删头结点
        Node* pdel = head;
        head = pdel->next;
        printf("------- customer: %lu, %d\n", pthread_self(), pdel->data);
        free(pdel);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main(int argc, const char* argv[])
{
    pthread_t p1, p2;
    //init
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    
    //创建生产者线程
    pthread_create(&p1, NULL, producer, NULL);
    //创建消费者线程
    pthread_create(&p2, NULL, customer, NULL);
    

    //释放线程资源
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    
    //释放锁资源
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
