#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM 5

int queue[NUM]; //全局数组实现环形队列

sem_t blank_number, product_number;//空格子信量，产品信号量

void* producer(void *arg)
{
  int i=0;
  while(1)
  {
    sem_wait(&blank_number);//生产这将空格字数--，为0则阻塞
    queue[i] = rand()%1000+1;
    printf("+++Product%lu---%d\n",pthread_self(),queue[i]);
    sem_post(&product_number);//生产者将产品数++，
    
    i = (i+1)%NUM;//实现环形队列
    sleep(rand()%1);
  }
}

void* consumer(void *rag)
{
  int i = 0;
  while(1)
  {
    sem_wait(&product_number);
    printf("---Consumer%lu+++%d\n",pthread_self(),queue[i]);
    queue[i] = 0;
    sem_post(&blank_number);

    i = (i+1)%NUM;
    sleep(rand()%3);
  }
}

int main()
{
  pthread_t pid, cid;

  sem_init(&blank_number,0,NUM);
  sem_init(&product_number,0,0);
  
  pthread_create(&pid, NULL, producer, NULL);
  pthread_create(&cid, NULL, consumer, NULL);
  
  pthread_join(pid, NULL);
  pthread_join(cid, NULL);

  sem_destroy(&blank_number);
  sem_destroy(&product_number);

  return 0;

}
