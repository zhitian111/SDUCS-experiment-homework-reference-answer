//例：使用成员函数、友元函数和一般函数的区别
#include <iostream>
using namespace std;
class Time
{
public:
    Time(int h,int m,int s):hour(h),minute(m),sec(s) {}
    void display1();    //display1是成员函数
    friend void display2(Time &);  //display2是友元函数
    int getHour(){return hour;}
    int getMinute(){return minute;}
    int getSec(){return sec;}
private:
    int hour;
    int minute;
    int sec;
};
void Time::display1()  //成员函数display1的实现，dispaly1前加Time::
{
    //以hour形式直接访问私有数据成员，实质是this->hour形式
    cout<<hour<<":"<<minute<<":"<<sec<<endl;
}
void display2(Time &t)  //友元函数dispaly2的实现，不加Time::，友元并不是类的成员
{
    //虽然不是类的成员函数，却可以用t.hour的形式直接访问私有数据成员——这就是友元
    cout<<t.hour<<":"<<t.minute<<":"<<t.sec<<endl;
}
void display3(Time &t)  //display3是一般函数，dispaly3前不加Time::
{
    //不能直接访问，只能用公共接口t.getHour()形式访问私有数据成员
    cout<<t.getHour()<<":"<<t.getMinute()<<":"<<t.getSec()<<endl;
}

int main()
{
    Time t1(10,13,56);
    t1.display1();  //成员函数这样调用：对象名.函数名()
    display2(t1);   //友员函数的调用和一般函数无异（但实现中可以不同）
    display3(t1);   //一般函数的调用
    return 0;
}