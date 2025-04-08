#include<iostream>
using namespace std;

class BaseClass
{
public:
	int Number;
	BaseClass()
	{
		cout << "������һ��BaseClass����" << endl;
	}
	~BaseClass()
	{
		cout << "������һ��BaseClass����" << endl;
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
		cout << "������һ��DerivedClass����" << endl;
		cout << "��ǰDerivedClass���������Ϊ:" << this->getNumber() << endl;
	}
	~DerivedClass()
	{
		this->number--;
		cout << "������һ��DerivedClass����" << endl;
		cout << "��ǰDerivedClass���������Ϊ:" << this->getNumber() << endl;
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