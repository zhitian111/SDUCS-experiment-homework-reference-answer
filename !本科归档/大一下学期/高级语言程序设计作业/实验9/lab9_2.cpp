#include"link.h"
using namespace std;



int main()
{
	LinkedList<int> A;
	LinkedList<int> B;
	A.insertAfter(1);
	A.insertAfter(2);
	A.insertAfter(3);
	A.insertAfter(4);
	A.insertAfter(5);
	cout << "A����" << endl;
	A.display();
	B.insertAfter(6);
	B.insertAfter(7);
	B.insertAfter(8);
	B.insertAfter(9);
	B.insertAfter(10);
	cout << "B����" << endl;
	B.display();
	A.addAfter(B);
	cout << "AB���Ӻ�" << endl;
	A.display();
	return 0;
}
