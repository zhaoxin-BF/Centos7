#include"List.h"

int main()
{
  LNode l;
  InitList(&l);

  PushBack(&l,1);
  PushBack(&l,2);
  PushBack(&l,3);

  PrintList(&l);

  RList(&l);
  PrintList(&l);
}
