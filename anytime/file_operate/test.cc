#include <iostream>
#include "fstream"

using namespace std;

int main()
{
    char ch;
    char fname[] = "/home/zhaoxin/anytime/file_operate/3.txt";
    //ofstream fout(fname, ios::out); //文件不存在，则创建文件，默认为此种情况不追加
    ofstream fout(fname, ios::app);   //在文件中追加
    if(!fout)
    {
        cout<<"打开文件失败"<<endl;
        return 0;
    }
    fout<<"hello 1111"<<endl;
    fout<<"hello 2222"<<endl;
    fout<<"hello 3333"<<endl;
    fout.close();

    //读文件
    ifstream fin(fname, ios::in);
    while(fin.get(ch))
    {
        cout<<ch;
    }
    fin.close();
    
    cout<<"程序运行完毕"<<endl;
    return 0;
}
