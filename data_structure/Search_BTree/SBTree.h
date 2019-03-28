#ifndef _SBTREE_H__
#define _SBTREE_H__
#include <stdio.h>
#include <malloc.h>

typedef int SBTDataType;

typedef struct SBTreeNode
{
    SBTDataType _data;
    struct SBTreeNode* _left;
    struct SBTreeNode* _right;
}SBTNode,*SBTree;

#endif
SBTree BuySBTreeNode(SBTDataType data)
{
    SBTree node = (SBTree)malloc(sizeof(SBTNode));
    node->_data = data;
    node->_left = NULL;
    node->_right = NULL;
    return node;
}

int Insert_SBTree(SBTree* tree,SBTDataType data)
{
    SBTree parent = NULL,cur;
    if(*tree == NULL)
    {
        *tree = BuySBTreeNode(data);
        return 1;
    }
    cur = *tree;
    while(cur)
    {
        if(cur->_data > data)
        {
            parent = cur;
            cur = cur->_left;
        }
        else if(cur->_data < data)
        {
            parent = cur;
            cur = cur->_right;
        }
        else
            return 0;
    }

    if(parent->_data < data)
    {
        parent->_right = BuySBTreeNode(data);
    }
    else
    {
        parent->_left = BuySBTreeNode(data);
    }
    return 1;
}

SBTree Find_SBTree(SBTree* tree, SBTDataType data)
{
    SBTree cur = *tree;
    while(cur)
    {
        if(cur->_data > data)
            cur = cur->_left;
        else if(cur->_data < data)
            cur = cur->_right;
        else
            return cur;
    }
    return NULL;
}
void InOrder_SBTree(SBTree* tree)
{
    if(*tree == NULL)
    {
        return;
    }
    InOrder_SBTree(&((*tree)->_left));
    printf("%d ",(*tree)->_data);
    InOrder_SBTree(&((*tree)->_right));
}

int Remove_SBTree(SBTree* tree, SBTDataType data)
{
    SBTree cur = *tree;
    SBTree parent = *tree;
    SBTree del = NULL;

    while(cur)
    {
        if(cur->_data > data)
        {
            parent = cur;
            cur = cur->_left;
        }
        else if(cur->_data < data)
        {
            parent = cur;
            cur = cur->_right;
        }
        else
        {
            del = cur;
            if(cur->_left == NULL)
            {
                if(parent->_left == cur)
                    parent->_left = cur->_right;
                else if(parent->_right == cur)
                    parent->_right = cur->_right;
                else
                    *tree = parent->_right;
            }
            else if(cur->_right == NULL)
            {
                if(parent->_left == cur)
                    parent->_left = cur->_left;
                if(parent->_right == cur)
                    parent->_right = cur->_left;
                else
                    *tree = parent->_left;
            }
            else
            {
                parent = cur;
                SBTree sub = cur->_right;
                while(sub->_left)
                {
                    parent = sub;
                    sub = sub->_left;
                }
                del = sub;
                cur->_data = sub->_data;
                if(parent->_left == sub)
                    parent->_left = sub->_right;
                else
                    parent->_right = sub->_right;
            }

            free(del);
            del = NULL;
            return 0;
        }
    }
    return 1;
}
