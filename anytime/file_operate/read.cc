#include <iostream>
#include "fstream"
#include <string.h>
using namespace std;


class Teacher
{
    public:
        Teacher()
        {
            age = 33;
            strcpy(name, "33");
        }
        Teacher(int _age, char _name[])
        {
            age = _age;
            strcpy(name, _name);
        }
        void printT()
        {
            cout<<"age:"<<age<<"name:"<<name<<endl;
        }
    protected:
    private:
        int age;
        char name[32];
};

int main()
{
    char fname[] = "/home/zhaoxin/anytime/file_operate/lla.dat";
    ofstream fout(fname, ios::binary);
    if(!fout)
    {
        cout<<"打开失败"<<endl;
        return 0;
    }
    Teacher t1(32, "t32");
    Teacher t2(31, "t31");
    fout.write((char*)&t1, sizeof(t1));
    fout.write((char*)&t2, sizeof(t2));
    fout.close();

    ifstream fin(fname);
    Teacher tmp;

    fin.read((char*)&tmp, sizeof(Teacher));
    tmp.printT();
    
    fin.read((char*)&tmp, sizeof(Teacher));
    tmp.printT();
    
    fin.close();

    return 0;
}
