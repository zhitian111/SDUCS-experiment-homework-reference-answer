//
#include <iostream>
using namespace std;

class SimpleCircle
{
public:
	SimpleCircle();
	SimpleCircle(int);
	SimpleCircle(const SimpleCircle &);
	~SimpleCircle() { 
		delete itsRadius;
		}
	void setRadius(int);
	int getRadius() const;
	
	int * get_addr(){
		return itsRadius;
	}
	
private:
	int *itsRadius;
};

SimpleCircle::SimpleCircle()
{
	itsRadius = new int(5);
}

SimpleCircle::SimpleCircle(int radius)
{
	itsRadius = new int(radius);
}

SimpleCircle::SimpleCircle(const SimpleCircle & rhs)
{	cout<<"in copy constructor"<<endl;
	int val = rhs.getRadius();
	itsRadius = new int(val);
}

int SimpleCircle::getRadius() const
{
	return *itsRadius;
}

int main()
{
	SimpleCircle CircleOne, CircleTwo(9),t3(CircleTwo),t4=CircleTwo;  
	//t4=CircleTwo;  
	cout << "CircleOne: " << CircleOne.getRadius() <<"  "<< CircleOne.get_addr() <<endl;
	cout << "CircleTwo: " << CircleTwo.getRadius() <<"  "<< CircleTwo.get_addr() << endl;
	cout << "t3: " << t3.getRadius() <<"  "<<t3.get_addr() << endl;
	cout << "t4: " << t4.getRadius() <<"  "<<t4.get_addr() <<endl;
	
	return 0;
}
