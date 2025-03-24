#include <iostream>
#include <typeinfo>

union C_DataType {
	char a;
	int b;
	float c;
};

class DataType {
	private:
		C_DataType save;
		char type;
	public:
		DataType(char aa) {
			save.a = aa;
			type = 1;
		}
		DataType(int bb) {
			save.b = bb;
			type = 2;
		}
		DataType(float cc) {
			save.c = cc;
			type = 3;
		}
		void print();
};

void DataType::print() {
	switch (type) {
		case 1:
			std::cout << "char" << ":" << save.a << std::endl;
			break;
		case 2:
			std::cout << "int" << ":" << save.b << std::endl;
			break;
		case 3:
			std::cout << "float" << ":" << save.c << std::endl;
			break;
		default:
			break;
	}
}

int main() {
	DataType aa('e'), bb(16), cc(2.65F);
	aa.print();
	bb.print();
	cc.print();
	return 0;
}