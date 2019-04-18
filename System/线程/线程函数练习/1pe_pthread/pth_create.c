#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h> 


void *myfunc(void* arg)
{
    //int num = (int)arg;
    //int num = *(int*)arg;
    //打印子线程的id
    printf("child thread id: %lu\n", pthread_self());
    return NULL;
}

int main(int argc, const char* argv[])
{

    pthread_t pthid;
    int i;

    pthread_create(&pthid, NULL, myfunc, NULL);

    printf("parent thread id: %lu\n", pthread_self());
    
    for(i=0; i<5; i++)
    {
        printf("i = %d\n",i);
    }
    sleep(2);   
    return 0;
}
