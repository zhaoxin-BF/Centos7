#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h> 


void *myfunc(void* arg)
{
    printf("child thread id: %lu\n", pthread_self());
    return NULL;
}

int main(int argc, const char* argv[])
{

    pthread_t pthid;
    int i;
    
    //初始化线程属性
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    //设置分离
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    //创建线程的时候设置线程分离
    int ret = pthread_create(&pthid, &attr, myfunc, NULL);
    if(ret != 0)
    {
        printf("error number: %d\n", ret);
        //打印错误信息
        printf("%s\n", strerror(ret));
    }
    printf("parent thread id: %lu\n", pthread_self());
    
    for(i=0; i<5; i++)
    {
        printf("i = %d\n",i);
    }
    //释放资源
    sleep(1);
    pthread_attr_destroy(&attr);
    return 0;
}
