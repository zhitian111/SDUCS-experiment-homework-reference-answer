#include"client.h"
using namespace std;
int main() {
	CLIENT test1;
	CLIENT test2;
	CLIENT test3;
	cout << "test1`s SeverName is:" << test1.ServerName << endl;
	cout << "test2`s SeverName is:" << test2.ServerName << endl;
	cout << "test3`s SeverName is:" << test3.ServerName << endl;
	cout << "ClientNum is:" << test1.ClientNum << endl;
	test1.ChangeServerName('b');
	cout << "change test1`s SeverName to \"b\"" << endl;
	cout << "test1`s SeverName is:" << test1.ServerName << endl;
	cout << "test2`s SeverName is:" << test2.ServerName << endl;
	cout << "test3`s SeverName is:" << test3.ServerName << endl;
	test2.ChangeServerName('c');
	cout << "change test2`s SeverName to \"c\"" << endl;
	cout << "test1`s SeverName is:" << test1.ServerName << endl;
	cout << "test2`s SeverName is:" << test2.ServerName << endl;
	cout << "test3`s SeverName is:" << test3.ServerName << endl;
	test3.ChangeServerName('d');
	cout << "change test3`s SeverName to \"d\"" << endl;
	cout << "test1`s SeverName is:" << test1.ServerName << endl;
	cout << "test2`s SeverName is:" << test2.ServerName << endl;
	cout << "test3`s SeverName is:" << test3.ServerName << endl;
	return 0;
}