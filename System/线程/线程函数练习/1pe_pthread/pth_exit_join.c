#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h> 


void *myfunc(void* arg)
{
    
    //打印子线程的id
    printf("child thread id: %lu\n", pthread_self());
    int i;
    for(i = 0; i < 5; i++)
    {
        printf("child i = %d\n", i);
        if(i == 2)
        {
            //子线程退出
            static int number = 100;                       //static 静态存储变量，随着程序的创建而创建，退出而被销毁
            pthread_exit(&number);                         //线程退出
        }
    }
    return NULL;
}

int main(int argc, const char* argv[])
{

    pthread_t pthid;                                       //线程ID
    int i=0;
    int ret = pthread_create(&pthid, NULL, myfunc, NULL);
    if(ret != 0)
    {
        printf("error number %d\n",ret);                   //线程错误号
        printf("%s\n", strerror(ret));                     //打印线程错误号 ——  strerror专门打印错误号的函数

    }

    printf("parent thread id: %lu\n", pthread_self());
    //pthread_exit(NULL);
    i = 5;

    //阻塞等待子线程退出，并且回收其pcb
    void* ptr = NULL;                                      //首先定义空指针，接收退出返回的ID号
    pthread_join(pthid, &ptr);                             //阻塞等待回收pcb
    printf("number = %d\n",*(int*)ptr);                    //强转打印退出号

    while(i--)
    {
        printf("parent i = %d\n",i);
    }

    //pthread_exit(NULL);                                  //主线程退出
    return 0;
}
