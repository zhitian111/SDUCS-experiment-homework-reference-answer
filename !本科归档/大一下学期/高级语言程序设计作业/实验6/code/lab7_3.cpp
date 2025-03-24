#include<iostream>
using namespace std;

class vehicle
{
public:
	int MaxSpeed;
	int Weight;
	void run();
	void stop();
	vehicle() {};
};
void vehicle::run()
{
	cout << "start running a vehicle" << endl;
}
void vehicle::stop()
{
	cout << "stop running a vehicle" << endl;
}

class bicycle:
	//public vehicle
	virtual public vehicle
{
public:
	int Height;
	bicycle(int s, int w, int h)
	{
		MaxSpeed = s;
		Weight = w;
		Height = h;
	}
	int getMaxSpeed() { return MaxSpeed; }
	int getWeight() { return Weight; }

};

class motorcar :
	//public vehicle
	virtual public vehicle
{
public:
	int SeatNum;
	motorcar(int s, int w, int n)
	{
		MaxSpeed = s;
		Weight = w;
		SeatNum = n;
	}
	int getMaxSpeed() { return MaxSpeed; }
	int getWeight() { return Weight; }

};

class motorcycle :
	public bicycle,
	public motorcar
{
public:
	motorcycle(int s, int w, int n, int h) :
		bicycle(s,w,h),
		motorcar(s,w,n)
	{
		cout << "构造了一个motocycle对象" << endl;
	}
	int getMaxSpeed() { return motorcar::getMaxSpeed(); }
	int getWeight() { return bicycle::getWeight(); }
	~motorcycle(){}
};

int main()
{
	motorcycle moto(1, 2, 3, 4);
	cout << moto.Height << endl << moto.getMaxSpeed() << endl << moto.SeatNum << endl << moto.getWeight() << endl;
	return 0;
}