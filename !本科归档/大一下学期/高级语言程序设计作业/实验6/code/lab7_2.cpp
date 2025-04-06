#include<iostream>
using namespace std;

class BaseClass
{
public:
	int Number;
	BaseClass()
	{
		cout << "构造了一个BaseClass对象" << endl;
	}
	~BaseClass()
	{
		cout << "析构了一个BaseClass对象" << endl;
	}
};

class DerivedClass:
	public BaseClass
{
private:
	static int number;
public:
	int getNumber();
	DerivedClass(int n)
	{
		this->Number = n;
		this->number++;
		cout << "构造了一个DerivedClass对象" << endl;
		cout << "当前DerivedClass对象的数量为:" << this->getNumber() << endl;
	}
	~DerivedClass()
	{
		this->number--;
		cout << "析构了一个DerivedClass对象" << endl;
		cout << "当前DerivedClass对象的数量为:" << this->getNumber() << endl;
	}
};

int DerivedClass::number = 0;
int DerivedClass::getNumber()
{
	return number;
}
int main()
{
	DerivedClass class1(0);
	DerivedClass class2(1);
	DerivedClass class3(2);
	return 0;
}