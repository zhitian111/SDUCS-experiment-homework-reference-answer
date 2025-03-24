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
	cout << "成功更改姓名" << endl;
}
void Employee::display() {
	cout << "该员工的信息如下：" << endl;
	cout << "姓名：" << this->name << endl;
	cout << "街道地址：" << this->address << endl;
	cout << "城市：" << this->city << endl;
	cout << "邮政编码：" << this->postcode << endl;
}

int main() {
	Employee employee("小明", "山东大学青岛校区", "青岛", 123456);
	employee.display();
	employee.change_name("小红");
	employee.display();
	return 0;
}