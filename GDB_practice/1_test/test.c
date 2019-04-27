#include "test.h"
void print51(int n)
{
    if( n < 0)
        return;
    while(n > 0)
    {
        printf("%d ",n);
        n--;
    }
}

void print15(int n)
{
    if(n<0)
        return;
    int i = 1;
    while(i <= n)
    {
        printf("%d ",n);
        i++;
    }
}
