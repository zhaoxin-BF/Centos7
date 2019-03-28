#include <stdio.h>

#define MAX 100

void Swap(int *a,int *b)
{
    *a = *a - *b;
    *b = *a + *b;
    *a = *b - *a;
}

void maopao(int arr[],int n)
{
    int i,j;
    for(i = 1; i < n; i++)
    {
        for(j = 0; j < n-i; j++)
        {
            if(arr[j] > arr[j+1])
                Swap(&arr[j],&arr[j+1]);
        }
    }
}

void Print(int arr[], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main()
{
    int arra[MAX];
    int arrb[MAX];
    char c;
    int i,j;
    for(i = 0;;i++)
    {
        scanf("%d%c",&arra[i],&c);
        if(c == '\n')
            break;
    }
    for(i = 0;;i++)
    {
        scanf("%d%c",&arrb[i],&c);
        if(c == '\n')
            break;
    }
    int size = i+1;
    i = j = 0;
    while((i+j) < size-1)
    {
        if(arra[i] < arrb[j])
            i++;
        else
            j++;
    }
    for(j = 0;i<size;i++,j++)
    {
        Swap(&arra[i],&arrb[j]);
    }
    printf("Putout.......\n");
    //printf("i = %d\n",i);
    //printf("j = %d\n",j);
    
    maopao(arra,size);
    maopao(arrb,size);
    
    Print(arra,size);
    Print(arrb,size);
    return 0;
}
