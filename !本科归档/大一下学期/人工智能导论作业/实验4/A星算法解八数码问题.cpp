#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int sum = 0;
int sas = 0;
//״̬����
struct board
{
	int status[3][3];
};

//���λ�ö���
struct zero
{
	int x;
	int y;
};

//�ڵ㶨��
struct node
{
	board status;//��ǰ������״̬
	int f_cost;//��������
	int g_cost;//·������
	int h_cost;//Ԥ�ڴ���
	vector<node*> search_list;//������
	node* front;//���ڵ�
	zero mark;
};

vector<node*> openlist;//openlist
vector<node*> closelist;//closelist
board searchtarget;//�����յ�
vector<node*>::iterator iter;//���������
vector<node> ans;//������

//����node���͵�<
bool operator<(node& node1, node& node2)
{
	return node1.f_cost < node2.f_cost;
}
//����sort�����Ĳ���
bool compare(node*& node1, node*& node2)
{
	//cout << node1->f_cost << endl;
	//cout << node2->f_cost << endl;
	return (node1->f_cost) < (node2->f_cost);
}
//h_cost����
void HCoustCoculate(node &nodes,//��ǰ�ڵ�
	board &taget)//Ŀ��״̬
{
	int sum = 0;
	for (int i = 0; i < 3; i++) 
	{
		for (int j = 0; j < 3; j++)
		{
			if (nodes.status.status[i][j] != taget.status[i][j])
			{
				sum++;
			}
		}
	}
	nodes.h_cost = sum;
	return;
}

//f_cost����
void FCostCoculate(node& nodes) 
{
	HCoustCoculate(nodes, searchtarget);
	nodes.f_cost = nodes.h_cost + nodes.g_cost;
	return;
}

//�ж������ڵ��Ƿ���ͬ
bool CheckNode(node& node1, node& node2)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (node1.status.status[i][j]!=node2.status.status[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

//��һ���ڵ㸴�Ƶ���һ���ڵ�a->b
void CopyNode(node& a, node& b)
{
	b.f_cost = a.f_cost;
	b.g_cost = a.g_cost;
	b.h_cost = a.h_cost;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			b.status.status[i][j] = a.status.status[i][j];
		}
	}
	b.mark.x = a.mark.x;
	b.mark.y = a.mark.y;
}

//�ж��½ڵ��Ƿ���openlist��
bool CheckOpen(node& nodes)
{
	iter = openlist.begin();
	while (iter!=openlist.end())
	{
		if (CheckNode((**iter), nodes)) 
		{
			return true;
		}
		iter++;
	}
	return false;
}

//ˢ��openlist�ظ��ڵ�
void RefreshOpenlist(node& nodes)
{
	iter = openlist.begin();
	while (!CheckNode((**iter),nodes))
	{
		iter++;
	}
	if ((*iter)->g_cost > nodes.g_cost)
	{
		CopyNode(nodes, **iter);
	}
}


//�ж��½ڵ��Ƿ���closelist��
bool CheckClose(node& nodes)
{
	iter = closelist.begin();
	while (iter != closelist.end())
	{
		if (CheckNode(*(*iter), nodes))
		{
			return true;
		}
		iter++;
	}
	return false;
}
//�����������������ݵ�λ��
void Exchange(int& a, int& b)
{
	int c = a;
	a = b;
	b = c;
}


//��������
void SearchListCreate(node& nodes)
{
	sum++;
	int temmark = 1;
	//����
	if (nodes.mark.y > 0)
	{
		node* p = new(node);
		CopyNode(nodes, *p);
		p->mark.y--;
		Exchange(p->status.status[p->mark.x][p->mark.y], p->status.status[p->mark.x][p->mark.y + 1]);
		p->g_cost++;
		p->front = &nodes;
		FCostCoculate(*p);
		if (CheckClose(*p))
		{
			delete(p);
			temmark = 0;
		}
		if (temmark == 1) 
		{
			if (CheckOpen(*p))
			{
				RefreshOpenlist(*p);
			}
			else
			{
				openlist.push_back(p);
			}
			nodes.search_list.push_back(p);
		}
	}
	temmark = 1;
	//����
	if (nodes.mark.y < 2)
	{
		node* p = new(node);
		CopyNode(nodes, *p);
		p->mark.y++;
		Exchange(p->status.status[p->mark.x][p->mark.y], p->status.status[p->mark.x][p->mark.y - 1]);
		p->g_cost++;
		p->front = &nodes;
		FCostCoculate(*p);
		if (CheckClose(*p))
		{
			delete(p);
			temmark = 0;
		}
		if (temmark == 1)
		{
			if (CheckOpen(*p))
			{
				RefreshOpenlist(*p);
			}
			else
			{
				openlist.push_back(p);
			}
			nodes.search_list.push_back(p);
		}
	}
	temmark = 1;
	//����
	if (nodes.mark.x> 0)
	{
		node* p = new(node);
		CopyNode(nodes, *p);
		p->mark.x--;
		Exchange(p->status.status[p->mark.x][p->mark.y], p->status.status[p->mark.x + 1][p->mark.y]);
		p->g_cost++;
		p->front = &nodes;
		FCostCoculate(*p);
		if (CheckClose(*p))
		{
			delete(p);
			temmark = 0;
		}
		if (temmark == 1)
		{
			if (CheckOpen(*p))
			{
				RefreshOpenlist(*p);
			}
			else
			{
				openlist.push_back(p);
			}
			nodes.search_list.push_back(p);
		}
	}
	temmark = 1;
	//����
	if (nodes.mark.x < 2)
	{
		node* p = new(node);
		CopyNode(nodes, *p);
		p->mark.x++;
		Exchange(p->status.status[p->mark.x][p->mark.y], p->status.status[p->mark.x - 1][p->mark.y]);
		p->g_cost++;
		p->front = &nodes;
		FCostCoculate(*p);
		if (CheckClose(*p))
		{
			delete(p);
			temmark = 0;
		}
		if (temmark == 1)
		{
			if (CheckOpen(*p))
			{
				RefreshOpenlist(*p);
			}
			else
			{
				openlist.push_back(p);
			}
			nodes.search_list.push_back(p);
		}
	}
}


//�յ㺯��
bool Complete()
{
	int as = 0;
	iter = openlist.begin();
	if (openlist.empty())
	{
		cout << "openlistΪ��" << endl;
		return false;
	}
	while (iter!=openlist.end())
	{
		if ((**iter).h_cost == 0)
		{
			sas = as;
			return false;
		}
		iter++;
		as++;
	}
	return true;
}

//��������
void Search()
{
	while (Complete())
	{
		sas++;
		sort(openlist.begin(), openlist.end(),compare);
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

		//cout << "��" << sum << "������" << endl;
		//for (int i = 0; i < 3; i++)
		//{
		//	for (int j = 0; j < 3; j++)
		//	{
		//		cout << openlist[0]->status.status[i][j] << " ";
		//	}
		//	cout << endl;
		//}
		SearchListCreate(*openlist[0]);
		closelist.push_back(openlist[0]);
		openlist.erase(openlist.begin());
	}

}
void debug(node& nodes)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << nodes.status.status[i][j] << " ";
		}
		cout << endl;
	}
}
int main() 
{
	//�����ʼ״̬
	cout << "�����ʼ״̬:" << endl;
	node* temp = new(node);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> temp->status.status[i][j];
			if (temp->status.status[i][j] == 0)
			{
				temp->mark.x = i;
				temp->mark.y = j;
			}
		}
	}
	temp->g_cost = 0;
	temp->front = NULL;
	cout << "����Ŀ��״̬:" << endl;
	//���������յ�
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> searchtarget.status[i][j];
		}
	}
	//��ʼ��openlist��closelist
	openlist.push_back(temp);
	FCostCoculate(*temp);
	Search();
	//cout << sas << endl;
	temp = *iter;
	while (temp->front!=NULL)
	{
		ans.push_back(*temp);
		temp = temp->front;
	}
	int tem = 1;
	for (int i = ans.size() - 1; i >= 0; i--)
	{
		cout << "��" << tem++ << "��Ϊ:" << endl;
		debug(ans[i]);
	}
	cout << "���Ϲ�" << tem-1 << "��" << endl;
	return 0;
}