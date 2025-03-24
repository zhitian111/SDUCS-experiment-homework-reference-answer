#include <iostream>
using namespace std;

class SimpleCircle
{
public:
	SimpleCircle();
	SimpleCircle(int);
	SimpleCircle(const SimpleCircle &);
	~SimpleCircle() {}
	
	void setRadius(int);
	int getRadius() const;
	SimpleCircle operator=(SimpleCircle tem);
private:
	int *itsRadius;
};

SimpleCircle SimpleCircle::operator=(SimpleCircle tem)
{
	int* temp = new int(*tem.itsRadius);
	this->itsRadius = temp;
	return *this;
}


SimpleCircle::SimpleCircle()
{
	itsRadius = new int(5);
}

SimpleCircle::SimpleCircle(int radius)
{
	itsRadius = new int(radius);
}

SimpleCircle::SimpleCircle(const SimpleCircle & rhs)
{
	int val = rhs.getRadius();
	itsRadius = new int(val);
}

int SimpleCircle::getRadius() const
{
	return *itsRadius;
}

void SimpleCircle::setRadius(int radius)
{
	*itsRadius = radius;
}

int main()
{
	SimpleCircle CircleOne, CircleTwo(9); 
	SimpleCircle X, Y;
	X = Y = 2;
	cout << "CircleX: " << X.getRadius() << endl;
	cout << "CircleY: " << Y.getRadius() << endl;
	//cout << "CircleOne: " << CircleOne.getRadius() << endl;
	//cout << "CircleTwo: " << CircleTwo.getRadius() << endl;
	return 0;
}
