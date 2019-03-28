#include "SBTree.h"

void testSBTree()
{
    int i = 0;
    SBTree tree = NULL;
    int arr[] = {5,3,4,1,7,8,2,6,0,9,10};
    for(i = 0;i < sizeof(arr)/sizeof(arr[0]);i++)
    {
        Insert_SBTree(&tree,arr[i]);
    }
    InOrder_SBTree(&tree);
    printf("\n");
    Remove_SBTree(&tree,3);
    InOrder_SBTree(&tree);
    printf("\n");
}

int main()
{
    testSBTree();
    return 0;
}
