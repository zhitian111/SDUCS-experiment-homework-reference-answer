#include<iostream>
using namespace std;
class Employee {
private:
	string name;
	string address;
	string city;
	int postcode;
public:
	Employee(string n,string a,string c,int p):name(n),address(a),city(c),postcode(p){}
	void change_name(string newname);
	void display();
};

void Employee::change_name(string newname) {
	this->name = newname;
	cout << "�ɹ���������" << endl;
}
void Employee::display() {
	cout << "��Ա������Ϣ���£�" << endl;
	cout << "������" << this->name << endl;
	cout << "�ֵ���ַ��" << this->address << endl;
	cout << "���У�" << this->city << endl;
	cout << "�������룺" << this->postcode << endl;
}

int main() {
	Employee employee("С��", "ɽ����ѧ�ൺУ��", "�ൺ", 123456);
	employee.display();
	employee.change_name("С��");
	employee.display();
	return 0;
}