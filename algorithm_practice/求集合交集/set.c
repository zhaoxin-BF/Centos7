#include <stdio.h>

int main()
{
    int a[4], b[4], c[4];
    int i,j,k = 0;
    printf("请输入集合A的元素：\n");
    for(i =0;i<4;i++)
    {
        scanf("%d",&a[i]);
    }
    printf("请输入集合B的元素：\n");
    for(j =0;j<4;j++)
    {
        scanf("%d",&b[j]);
    }
    
    for(i = 0;i<4;i++)
    { 
        for(j = 0;j<4;j++)
        {
            if(a[i] == b[j])
            {
                c[k] = a[i];
                k++;
            }
        }
    }

    printf("C的交集有%d个，分别为：",k);
    
    for(i = 0;i < k;i++)
    {
        printf("%d ",c[i]);
    }

    printf("\n");
    return 0;
}
