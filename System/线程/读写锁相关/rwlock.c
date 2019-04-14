//gcc rwlock.c -lpthread       编译
//./a.out                      运行 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

int number = 0;

//创建读写锁
pthread_rwlock_t lock;

//写线程操作函数
void* write_func(void* argc)
{

    while(1)
    {
        //加写锁
        pthread_rwlock_wrlock(&lock);
        number++;
        printf("==write: %lu, %d\n", pthread_self(), number);
        //解锁
        pthread_rwlock_unlock(&lock);
        usleep(500);
    }
    return 0;
}

void* read_func(void* argc)
{
    while(1)
    {
        //加读锁
        pthread_rwlock_rdlock(&lock);
        printf("==read:  %lu, %d\n", pthread_self(), number);
        //加写锁
        pthread_rwlock_unlock(&lock);
        usleep(500);
    }
    return 0;
}

int main(int argc, const char* argv[])
{
    pthread_t p[8];
    int i;
    pthread_rwlock_init(&lock, NULL);
    //创建三个写线程
    for(i = 0; i<3 ;i++)
    {
        pthread_create(&p[i], NULL, write_func, NULL);
    }

    //创建五个读线程
    for(i = 3; i<8 ;i++)
    {
        pthread_create(&p[i], NULL, read_func, NULL);
    }

    //阻塞回收线程
    for(i = 0; i<8; i++)
    {
        pthread_join(p[i], NULL);
    }

    //释放读写锁资源
    pthread_rwlock_destroy(&lock);

    return 0;
}





