#include<iostream>
using namespace std;
class  vehicle
{
public:
	virtual void Run();
	virtual void Stop();
};
void vehicle::Run()
{
	cout << "run a vehicle" << endl;
}
void vehicle::Stop()
{
	cout << "stop a vehicle" << endl;
}

class bicycle :
	virtual public vehicle
{
public:
	virtual void Run();
	virtual void Stop();
};
void bicycle::Run()
{
	cout << "run a bicycle" << endl;
}
void bicycle::Stop()
{
	cout << "stop a bicycle" << endl;
}
class motorcar :
	virtual public vehicle
{
public:
	virtual void Run();
	virtual void Stop();
};
void motorcar::Run()
{
	cout << "run a motorcar" << endl;
}
void motorcar::Stop()
{
	cout << "stop a motorcar" << endl;
}
class motorcycle :
	public bicycle,
	public motorcar
{
public:
	void Run();
	void Stop();
};
void motorcycle::Run()
{
	cout << "run a motorcycle" << endl;
}
void motorcycle::Stop()
{
	cout << "stop a motorcycle" << endl;
}
int main()
{
	motorcycle a;
	a.Run();
	a.Stop();
	a.bicycle::Run();
	a.bicycle::Stop();
	a.motorcar::Run();
	a.motorcar::Stop();
	a.vehicle::Run();
	a.vehicle::Stop();
	return 0;
}