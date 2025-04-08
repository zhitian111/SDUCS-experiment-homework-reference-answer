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
			cout << "������һ��Date�����" << endl;
		}
		Date(Date &date) {
			this->year = date.year;
			this->month = date.month;
			this->day = date.day;
			cout << "���ƹ�����һ��Date�����" << endl;
		}
		~Date() {
			cout << "������һ��Date�����" << endl;
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
			cout << "������һ��People�����" << endl;
		}
		People(People &p): number(p.number), sex(p.sex), birthday(p.birthday), id(p.id) {
			cout << "���ƹ�����һ��People�����" << endl;
		}
		~People() {
			cout << "������һ��People�����" << endl;
		}
		void show();
};

void People::show() {
	cout << "��ţ�" << this->number << endl;
	cout << "�Ա�" << this->id << endl;
	cout << "�������ڣ�";
	this->birthday.show();
	cout << "���֤�ţ�" << this->id << endl;
}


int main() {
	int number;
	int sex;
	int y, m, d;
	string id;
	cout << "������" << endl;
	cin >> number;
	cout << "�����Ա�(0ΪŮ/1Ϊ��)" << endl;
	cin >> sex;
	cout << "���������/��/��" << endl;
	cin >> y >> m >> d;
	cout << "�������֤��" << endl;
	cin >> id;
	Date birthday(y, m, d);
	People people(number, sex, birthday, id);
	people.show();
	return 0;
}