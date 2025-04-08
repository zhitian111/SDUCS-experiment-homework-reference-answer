#include<iostream>
using namespace std;


template<class T>
class Person {
public:
	T* pet;
	string name;
	Person(string name, T* pet) :name(name), pet(pet) {};
	void display() { cout << name << "has a pet" << pet->getName() << "named" << pet->name << endl; }
};