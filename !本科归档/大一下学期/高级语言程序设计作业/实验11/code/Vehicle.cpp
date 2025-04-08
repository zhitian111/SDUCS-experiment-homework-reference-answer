#include<iostream>
using namespace std;

class Tire {
public:
	double r;
	double h;
	Tire(double r, double h) :r(r), h(h) {};
};
class Engine {
public:
	int number;
	double out;
	double P;
	Engine(int n, double o, double P) :number(n), out(o), P(P) {};
};

class Vehicle :
	public Tire,
	public Engine
{
private:
	double price;
public:
	Vehicle(double r, double h, int n, double o, double p, double q) :Tire(r, h), Engine(n, o, p), price(q) {};
	void display() { cout << r << endl << h << endl << number << endl << out << endl << P << endl << price << endl; }
};

int main()
{
	Vehicle test(1, 2, 3, 4, 5, 6);
	test.display();
}