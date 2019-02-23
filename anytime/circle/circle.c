#include<stdio.h>
int main()
{
  double r,h;
  printf("please input r and h:");
  scanf("%lf%lf",&r,&h);
  printf("Z = %2.2f\n",2*3.14*r);
  printf("M = %2.2f\n",3.14*r*r);
  printf("BM = %2.2f\n",4*3.14*r*r);
  printf("QV = %2.2f\n",4*3.14*r*r*r/3.0);
  printf("ZV = %2.2f\n",3.14*r*r*h);
  printf("nihaoa\n");
  return 0;
}
