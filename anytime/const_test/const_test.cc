//c语言中的const是一个冒牌货
//C++语言中const是一个真正的常量

#include <stdio.h>


int main()
{
    const int a = 10;

    int *p = NULL;
    p = (int*)&a;

    *p = 20;

    printf("a:%d\n", a);
    return 0;
}
