#include<iostream>
using namespace std;

class Animal 
{
//private:
//	int age;
public:
	int age;
};

class dog :public Animal
{
public:
	void SetAge(int n);
};

void dog::SetAge(int n) 
{
	this->age = n;
}

int main() 
{
	dog doge;
	doge.SetAge(0);
	cout << doge.age;
	return 0;
}