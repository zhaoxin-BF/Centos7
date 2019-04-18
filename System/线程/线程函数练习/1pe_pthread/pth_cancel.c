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
    
    while(1)
    {
        int i,j,k;
        i = 10;
        j = 20;
        k = i+j;
        //printf("k = %d\n", k);
        pthread_cancel(pthread_self());              //子线程断点
    }
    return NULL;
}

int main(int argc, const char* argv[])
{

    pthread_t pthid;
    int i;

    int ret = pthread_create(&pthid, NULL, myfunc, NULL);

    printf("parent thread id: %lu\n", pthread_self());
    //sleep(1);
    for(i=0; i<5; i++)
    {
        printf("i = %d\n",i);
    }
    
    return 0;
}
