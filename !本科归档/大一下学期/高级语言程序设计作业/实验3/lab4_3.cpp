#include <iostream>
using namespace std;


class Date {

	private:

		int year;
		int month;
		int day;

	public:

		Date(int y, int m, int d) {
			this->year = y;
			this->month = m;
			this->day = d;
			cout << "构造了一个Date类对象" << endl;
		}
		Date(Date &date) {
			this->year = date.year;
			this->month = date.month;
			this->day = date.day;
			cout << "复制构造了一个Date类对象" << endl;
		}
		~Date() {
			cout << "析构了一个Date类对象" << endl;
		}

		void show() {
			cout << year << "-" << month << "-" << day << endl;
		}

};


class People {

	private:
		int number;
		int sex;
		Date birthday;
		string id;

	public:
		People(int n, int s, Date b, string i): number(n), sex(s), birthday(b), id(i) {
			cout << "构造了一个People类对象" << endl;
		}
		People(People &p): number(p.number), sex(p.sex), birthday(p.birthday), id(p.id) {
			cout << "复制构造了一个People类对象" << endl;
		}
		~People() {
			cout << "析构了一个People类对象" << endl;
		}
		void show();
};

void People::show() {
	cout << "编号：" << this->number << endl;
	cout << "性别：" << this->id << endl;
	cout << "出生日期：";
	this->birthday.show();
	cout << "身份证号：" << this->id << endl;
}


int main() {
	int number;
	int sex;
	int y, m, d;
	string id;
	cout << "输入编号" << endl;
	cin >> number;
	cout << "输入性别(0为女/1为男)" << endl;
	cin >> sex;
	cout << "输入出生年/月/日" << endl;
	cin >> y >> m >> d;
	cout << "输入身份证号" << endl;
	cin >> id;
	Date birthday(y, m, d);
	People people(number, sex, birthday, id);
	people.show();
	return 0;
}