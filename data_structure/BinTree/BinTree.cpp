#include"BinTree.h"
size_t n = 0;

int main()
{
	BTNode pRoot;
  DataType array[] = {'A','B','C','*','*','*','D','E','*','*','F','*','*'};
  CreateBinTree(&pRoot,array,13,&n,'*');

  cout<<"Middle Souch:";
  PrintBinTree(pRoot);
  cout<<endl;

  int size = SizeBinTree(pRoot);
  cout<<"Size = "<<size<<endl;
	return 0;
}
