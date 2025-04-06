//7_7.cpp
#include <iostream>
using namespace std;

class Base0 {	//定义基类Base0
public:
    int var0;
    virtual void fun0() { cout << "Member of Base0" << endl; }
};

class Base1: virtual public Base0 {	//定义派生类Base1
public:	//新增外部接口
    int var1;
};

class Base2: virtual public Base0 {	//定义派生类Base2
public:	//新增外部接口
    int var2;
};

class Derived: public Base1, public Base2 {	//定义派生类Derived
public:	//新增外部接口
    int var;
    void fun() { cout << "Member of Derived" << endl; }
    Derived(int d) { var0 = d; }
};

int main() {	//程序主函数
    Derived d(1);	//定义Derived类对象d
    cout << d.var0 << "  " << d.Base1::var0 << "  " << d.Base2::var0 << endl;

    d.var0 = 2;	//直接访问虚基类的数据成员
    d.fun0();	//直接访问虚基类的函数成员
    cout << d.var0 << "  " << d.Base1::var0 << "  " << d.Base2::var0 << endl;

    d.Base1::var0 = 1;
    d.Base2::var0 = 3;
    cout << d.var0 << "  " << d.Base1::var0 << "  " << d.Base2::var0 << endl;
    return 0;
}
