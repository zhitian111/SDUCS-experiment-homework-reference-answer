#include <iostream>
using namespace std;

class Tree {
	private:
		int ages;
	public:
		void age();
		void grow(int g);
		Tree(int t): ages(t) {}
};


void Tree::age() {
	cout << "The age of this tree is " << ages << endl;
}

void Tree::grow(int g) {
	this->ages += g;
	this->age();
}

int main() {
	Tree t(12);
	t.age();
	t.grow(4);
	return 0;
}