#include<iostream>
using namespace std;


class CException 
{
public:
	virtual void Reason();
	void fn1();
	CException() { type = 0; };
	int type;
};
void CException::Reason()
{
	cout << "error code:" <<typeid(*this).name()<<" "<< type << "." << endl;
}
void CException::fn1()
{
	type = 1;
	throw CException();
}

class OutOfRange:
	virtual public CException
{
public:
	OutOfRange() {};
	~OutOfRange(){};
	virtual void fn1() { type = 1; throw OutOfRange(); };
};

class LogicError :
	virtual public CException
{
public:
	virtual void fn1() { type = 1; throw LogicError(); };

	LogicError() {};
	~LogicError() {};
};

int main()
{
	CException ce;
	OutOfRange of;
	LogicError le;
	try
	{
		int a, b;
		cin >> a >> b;
		if (b == 0)
		{
			le.fn1();
		}
		if (a > 1000000000 || b > 1000000000)
		{
			of.fn1();
		}
		cout << (float)a / b;
	}
	catch (OutOfRange)
	{
		of.Reason();
	}
	catch (LogicError)
	{
		le.Reason();
	}
	return 0;
}