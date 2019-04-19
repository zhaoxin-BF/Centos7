#include <iostream>
#include <memory>
#include "smart_pointer.h"
using namespace std;

class Dog{
    //省略...
};

//智能指针auto_ptr的使用，不需要调用delete去清理堆栈内存空间
void demo2()
{
    auto_ptr<double> pd(new double);

    *pd = 28.5;

    auto_ptr<Dog> pDog(new Dog());
    smart_pointer<Dog> spDog(new Dog());   //测试自己编写的简易智能指针类


    cout<<*pd<<endl;
}



void demo1()
{
    double d;
    d = 25.5;
    
    double * pd = new double;      //已经创建好了空间，所以可以通过解引用*pd直接复制
    *pd = 25.5;

    //做什么工作
    cout<<d<<std::endl;
    cout<<*pd<<std::endl;

    delete pd;
    return;
}



int main()
{
    demo1();
    demo2();
    return 0;
}
