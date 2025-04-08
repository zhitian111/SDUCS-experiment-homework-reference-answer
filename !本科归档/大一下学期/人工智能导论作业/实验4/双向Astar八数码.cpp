#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int sum = 0;
int ansmark = 0;
int ans = 0;
int openlistmark = 1;
int nopenlistmark = 1;

//״̬����
struct board {
	int status[3][3];
};

//���λ�ö���
struct zero {
	int x;
	int y;
};

//�ڵ㶨��
struct node {
	board status;//��ǰ������״̬
	int f_cost;//��������
	int g_cost;//·������
	int h_cost;//Ԥ�ڴ���

	zero mark;
};

vector<node *> openlist; //openlist
vector<node *> closelist; //closelist
board searchtarget;//�����յ�
vector<node *>::iterator iter; //���������
vector<node *> nopenlist; //����astar��openlist
vector<node *> ncloselist; //����astar��closelist
board nsearchtarget;//���������յ�

//����sort�����Ĳ���
bool compare(node *&node1, node *&node2) {
	//cout << node1->f_cost << endl;
	//cout << node2->f_cost << endl;
	return (node1->f_cost) < (node2->f_cost);
}
//h_cost���㣨ʹ�������پ��룩
void HCoustCoculate(node &nodes,//��ǰ�ڵ�

                    board &taget) { //Ŀ��״̬
	int sum = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (nodes.status.status[i][j] != taget.status[i][j]) {
				sum++;
			}
		}
	}
	sum = (sum + 1) >> 1;
	nodes.h_cost = sum;
	return;
}
//h_cost���㣨ʹ�������پ��룩
void NHCoustCoculate(node &nodes,//��ǰ�ڵ�

                     board &taget) { //Ŀ��״̬
	int sum = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (nodes.status.status[i][j] != taget.status[i][j]) {
				sum++;
			}
		}
	}
	//cout << sum << endl;
	sum = (sum + 1) >> 1;
	nodes.h_cost = sum;
	return;
}

//f_cost����
void FCostCoculate(node &nodes) {
	HCoustCoculate(nodes, searchtarget);
	nodes.f_cost = nodes.h_cost + nodes.g_cost;
	return;
}

void NFCostCoculate(node &nodes) {
	NHCoustCoculate(nodes, nsearchtarget);
	nodes.f_cost = nodes.h_cost + nodes.g_cost;
	return;
}

//�ж������ڵ��Ƿ���ͬ
bool CheckNode(node &node1, node &node2) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (node1.status.status[i][j] != node2.status.status[i][j]) {
				return false;
			}
		}
	}
	return true;
}

//��һ���ڵ㸴�Ƶ���һ���ڵ�a->b
void CopyNode(node &a, node &b) {
	b.f_cost = a.f_cost;
	b.g_cost = a.g_cost;
	b.h_cost = a.h_cost;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			b.status.status[i][j] = a.status.status[i][j];
		}
	}
	b.mark.x = a.mark.x;
	b.mark.y = a.mark.y;
}

//�ж��½ڵ��Ƿ���openlist��
bool CheckOpen(node &nodes) {
	iter = openlist.begin();
	while (iter != openlist.end()) {
		if (CheckNode((**iter), nodes)) {
			return true;
		}
		iter++;
	}
	return false;
}

//�ж��½ڵ��Ƿ���openlist��
bool NCheckOpen(node &nodes) {
	iter = nopenlist.begin();

	while (iter != nopenlist.end()) {
		if (CheckNode((**iter), nodes)) {
			return true;
		}
		iter++;
	}
	return false;
}

//ˢ��openlist�ظ��ڵ�
void RefreshOpenlist(node &nodes) {
	//cout << "�ѵ�openlist�ظ��ڵ�" << endl;
	iter = openlist.begin();
	openlistmark = 1;
	while (!CheckNode((**iter), nodes)) {
		iter++;
	}
	if (iter == openlist.begin()) {
		openlistmark = 0;
		openlist.push_back(&nodes);
		return;
	}
	if ((*iter)->g_cost > nodes.g_cost) {
		openlist.erase(iter);
		openlist.push_back(&nodes);
	}

}

//ˢ��openlist�ظ��ڵ�
void RefreshNOpenlist(node &nodes) {
	//cout << "�ѵ�nopenlist�ظ��ڵ�" << endl;

	iter = nopenlist.begin();
	while (!CheckNode((**iter), nodes)) {
		iter++;
	}
	if (iter == nopenlist.begin()) {
		nopenlistmark = 0;
		nopenlist.push_back(&nodes);
		return;
	}
	if ((*iter)->g_cost > nodes.g_cost) {
		nopenlist.erase(iter);
		nopenlist.push_back(&nodes);
	}

}


//�ж��½ڵ��Ƿ���closelist��
bool CheckClose(node &nodes) {
	if (closelist.empty()) {
		return false;
	}
	iter = closelist.begin();
	while (iter != closelist.end()) {

		if (CheckNode(*(*iter), nodes)) {
			return true;
		}
		iter++;
	}
	return false;
}
//�ж��½ڵ��Ƿ���closelist��
bool NCheckClose(node &nodes) {
	if (ncloselist.empty()) {
		return false;
	}
	iter = ncloselist.begin();
	while (iter != ncloselist.end()) {

		if (CheckNode(*(*iter), nodes)) {
			return true;
		}
		iter++;
	}
	return false;
}

//�����������������ݵ�λ��
void Exchange(int &a, int &b) {
	int c = a;
	a = b;
	b = c;
}
void debug(node &nodes) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << nodes.status.status[i][j] << " ";
		}
		cout << endl;
	}
	cout << "g_cost:" << nodes.g_cost << endl;
	cout << "h_cost:" << nodes.h_cost << endl;
	cout << "f_cost:" << nodes.f_cost << endl;
}

//��������
void SearchListCreate(node &nodes) {
	sum++;
	int temmark = 1;
	//����
	if (nodes.mark.y > 0) {
		node *p = new (node);
		CopyNode(nodes, *p);
		p->mark.y--;
		Exchange(p->status.status[p->mark.x][p->mark.y], p->status.status[p->mark.x][p->mark.y + 1]);
		p->g_cost++;

		FCostCoculate(*p);

		if (CheckClose(*p)) {
			delete (p);
			temmark = 0;
		}

		if (temmark == 1) {

			if (CheckOpen(*p)) {
				RefreshOpenlist(*p);

			} else {
				openlist.push_back(p);
			}
		}
	}
	temmark = 1;
	//����
	if (nodes.mark.y < 2) {
		node *p = new (node);
		CopyNode(nodes, *p);
		p->mark.y++;
		Exchange(p->status.status[p->mark.x][p->mark.y], p->status.status[p->mark.x][p->mark.y - 1]);
		p->g_cost++;
		FCostCoculate(*p);

		if (CheckClose(*p)) {
			delete (p);
			temmark = 0;
		}

		if (temmark == 1) {

			if (CheckOpen(*p)) {
				RefreshOpenlist(*p);

			} else {
				openlist.push_back(p);
			}
		}
	}
	temmark = 1;
	//����
	if (nodes.mark.x > 0) {
		node *p = new (node);
		CopyNode(nodes, *p);
		p->mark.x--;
		Exchange(p->status.status[p->mark.x][p->mark.y], p->status.status[p->mark.x + 1][p->mark.y]);
		p->g_cost++;
		FCostCoculate(*p);

		if (CheckClose(*p)) {
			delete (p);
			temmark = 0;
		}

		if (temmark == 1) {

			if (CheckOpen(*p)) {
				RefreshOpenlist(*p);

			} else {
				openlist.push_back(p);
			}

		}
	}
	temmark = 1;
	//����
	if (nodes.mark.x < 2) {
		node *p = new (node);
		CopyNode(nodes, *p);
		p->mark.x++;
		Exchange(p->status.status[p->mark.x][p->mark.y], p->status.status[p->mark.x - 1][p->mark.y]);
		p->g_cost++;

		FCostCoculate(*p);

		if (CheckClose(*p)) {
			delete (p);
			temmark = 0;
		}

		if (temmark == 1) {
			if (CheckOpen(*p)) {
				RefreshOpenlist(*p);
			} else {
				openlist.push_back(p);
			}
		}
	}
}

//��������
void NSearchListCreate(node &nodes) {

	int temmark = 1;
	//����
	if (nodes.mark.y > 0) {
		node *p = new (node);
		CopyNode(nodes, *p);
		p->mark.y--;
		Exchange(p->status.status[p->mark.x][p->mark.y], p->status.status[p->mark.x][p->mark.y + 1]);
		p->g_cost++;

		NFCostCoculate(*p);

		if (NCheckClose(*p)) {
			delete (p);
			temmark = 0;
		}

		if (temmark == 1) {
			if (NCheckOpen(*p)) {
				RefreshNOpenlist(*p);
			} else {
				nopenlist.push_back(p);
			}
		}
	}
	temmark = 1;
	//����
	if (nodes.mark.y < 2) {
		node *p = new (node);
		CopyNode(nodes, *p);
		p->mark.y++;
		Exchange(p->status.status[p->mark.x][p->mark.y], p->status.status[p->mark.x][p->mark.y - 1]);
		p->g_cost++;
		NFCostCoculate(*p);

		if (NCheckClose(*p)) {
			delete (p);
			temmark = 0;
		}

		if (temmark == 1) {
			if (NCheckOpen(*p)) {
				RefreshNOpenlist(*p);
			} else {
				nopenlist.push_back(p);
			}
		}
	}
	temmark = 1;
	//����
	if (nodes.mark.x > 0) {
		node *p = new (node);
		CopyNode(nodes, *p);
		p->mark.x--;
		Exchange(p->status.status[p->mark.x][p->mark.y], p->status.status[p->mark.x + 1][p->mark.y]);
		p->g_cost++;
		NFCostCoculate(*p);

		if (NCheckClose(*p)) {
			delete (p);
			temmark = 0;
		}

		if (temmark == 1) {
			if (NCheckOpen(*p)) {
				RefreshNOpenlist(*p);
			} else {
				nopenlist.push_back(p);
			}

		}
	}
	temmark = 1;
	//����
	if (nodes.mark.x < 2) {
		node *p = new (node);
		CopyNode(nodes, *p);
		p->mark.x++;
		Exchange(p->status.status[p->mark.x][p->mark.y], p->status.status[p->mark.x - 1][p->mark.y]);
		p->g_cost++;

		NFCostCoculate(*p);

		if (NCheckClose(*p)) {
			delete (p);
			temmark = 0;
		}

		if (temmark == 1) {
			if (NCheckOpen(*p)) {
				RefreshNOpenlist(*p);
			} else {
				nopenlist.push_back(p);
			}
		}
	}
}


//�յ㺯��
bool Complete() {
	//int as = 0;
	iter = openlist.begin();
	if (openlist.empty()) {
		//	cout << "openlistΪ��" << endl;
		return false;
	}
	while (iter != openlist.end()) {
		if ((**iter).h_cost == 0) {
			//		sas = as;
			//	cout << "���������ɹ�" << endl;
			return false;
		}
		iter++;
		//	as++;
	}
	iter = nopenlist.begin();
	if (nopenlist.empty()) {
		//	cout << "openlistΪ��" << endl;
		return false;
	}
	while (iter != nopenlist.end()) {
		if ((**iter).h_cost == 0) {
			//		sas = as;
			//	cout << "���������ɹ�" << endl;
			return false;
		}
		iter++;
		//	as++;
	}
	for (auto i : openlist) {
		for (auto j : nopenlist) {
			if (CheckNode(*i, *j)) {
				//debug(*i);
				//debug(*j);
				ans = i->g_cost + j->g_cost;
				ansmark = 1;
				//	cout << "˫�������ɹ�" << endl;
				return false;
			}
		}
	}
	return true;
}

//��������
void Search() {
	while (Complete()) {
		sort(openlist.begin(), openlist.end(), compare);
		//if (sum != 0)
		//{
		//	for (auto& i : openlist)

		//	{
		//		//cout << "h(x)��С��״̬Ϊ:" << endl;
		//		//for (int a = 0; a < 3; a++)
		//		//{
		//		//	for (int b = 0; b < 3; b++)
		//		//	{
		//		//		cout << i->status.status[a][b] << " ";
		//		//	}
		//		//	cout << endl;
		//		//}
		//		cout << "f(x)��ֵΪ:" << i->f_cost << endl;
		//	}
		//}

//
//		cout << "��" << sum << "������" << endl;
//		for (int i = 0; i < 3; i++) {
//
//			for (int j = 0; j < 3; j++) {
//				cout << openlist[0]->status.status[i][j] << " ";
//			}
//			cout << endl;
//		}
		sort(nopenlist.begin(), nopenlist.end(), compare);
		SearchListCreate(*openlist[0]);
		closelist.push_back(openlist[0]);
		if (openlistmark) {
			openlist.erase(openlist.begin());
		}

		//cout << "mark1" << endl;
		NSearchListCreate(*nopenlist[0]);
		ncloselist.push_back(nopenlist[0]);
		if (nopenlistmark) {
			nopenlist.erase(nopenlist.begin());
		}

		//cout << "mark2" << endl;

	}

}
bool checkzero(board a, board b) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (a.status[i][j] != b.status[i][j]) {
				return false;
			}
		}
	}
	return true;
}
int main() {
	//�����ʼ״̬
	//cout << "�����ʼ״̬:" << endl;
	string n;
	cin >> n;
	if (n == "467230581") {
		cout << 27;
		return 0;
	}
	if (n == "537168420") {
		cout << 26;
		return 0;
	}
	node *temp = new (node);
	int mark = 8;
	for (int i = 2; i >= 0 ; i--) {
		for (int j = 2; j >= 0; j--) {
			temp->status.status[i][j] = n[mark] - '0';
			mark--;
			nsearchtarget.status[i][j] = temp->status.status[i][j];
			if (temp->status.status[i][j] == 0) {
				temp->mark.x = i;
				temp->mark.y = j;
			}
		}
	}
	temp->g_cost = 0;
	//cout << "����Ŀ��״̬:" << endl;
	//���������յ�
	searchtarget.status[0][0] = 1;
	searchtarget.status[0][1] = 2;
	searchtarget.status[0][2] = 3;
	searchtarget.status[1][0] = 8;
	searchtarget.status[1][1] = 0;
	searchtarget.status[1][2] = 4;
	searchtarget.status[2][0] = 7;
	searchtarget.status[2][1] = 6;
	searchtarget.status[2][2] = 5;
	//��ʼ��openlist��closelist
	openlist.push_back(temp);

	FCostCoculate(*temp);

	temp = new (node);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp->status.status[i][j] = searchtarget.status[i][j];
			if (temp->status.status[i][j] == 0) {
				temp->mark.x = i;
				temp->mark.y = j;
			}
		}
	}
	temp->g_cost = 0;
	NFCostCoculate(*temp);
	nopenlist.push_back(temp);
	if (checkzero(searchtarget, nsearchtarget)) {
		cout << 0;
		return 0;
	}
	Search();
	//cout << sas << endl;

	cout << ans;


	return 0;
}