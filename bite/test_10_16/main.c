#include<stdio.h>
#include"add.h"
#include"sub.h"
int main()
{
  printf("1+100 = %d\n",add(1,100));
  printf("1-100 = %d\n",sub(1,100));
  return 0;
}
