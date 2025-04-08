#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int sum = 0;
int sas = 0;
//状态定义
struct board
{
	int status[3][3];
};

//零点位置定义
struct zero
{
	int x;
	int y;
};

//节点定义
struct node
{
	board status;//当前数码盘状态
	int f_cost;//搜索代价
	int g_cost;//路径代价
	int h_cost;//预期代价
	vector<node*> search_list;//搜索表
	node* front;//父节点
	zero mark;
};

vector<node*> openlist;//openlist
vector<node*> closelist;//closelist
board searchtarget;//搜索终点
vector<node*>::iterator iter;//定义迭代器
vector<node> ans;//定义结果

//重载node类型的<
bool operator<(node& node1, node& node2)
{
	return node1.f_cost < node2.f_cost;
}
//传入sort函数的参数
bool compare(node*& node1, node*& node2)
{
	//cout << node1->f_cost << endl;
	//cout << node2->f_cost << endl;
	return (node1->f_cost) < (node2->f_cost);
}
//h_cost计算
void HCoustCoculate(node &nodes,//当前节点
	board &taget)//目标状态
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

//f_cost计算
void FCostCoculate(node& nodes) 
{
	HCoustCoculate(nodes, searchtarget);
	nodes.f_cost = nodes.h_cost + nodes.g_cost;
	return;
}

//判断两个节点是否相同
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

//将一个节点复制到另一个节点a->b
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

//判断新节点是否在openlist里
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

//刷新openlist重复节点
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


//判断新节点是否在closelist里
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
//交换数组中两个数据的位置
void Exchange(int& a, int& b)
{
	int c = a;
	a = b;
	b = c;
}


//搜索表创建
void SearchListCreate(node& nodes)
{
	sum++;
	int temmark = 1;
	//左移
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
	//右移
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
	//上移
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
	//下移
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


//终点函数
bool Complete()
{
	int as = 0;
	iter = openlist.begin();
	if (openlist.empty())
	{
		cout << "openlist为空" << endl;
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

//搜索函数
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
		//		//cout << "h(x)最小的状态为:" << endl;
		//		//for (int a = 0; a < 3; a++)
		//		//{
		//		//	for (int b = 0; b < 3; b++)
		//		//	{
		//		//		cout << i->status.status[a][b] << " ";
		//		//	}
		//		//	cout << endl;
		//		//}
		//		cout << "f(x)的值为:" << i->f_cost << endl;
		//	}
		//}

		//cout << "第" << sum << "次搜索" << endl;
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
	//输入初始状态
	cout << "输入初始状态:" << endl;
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
	cout << "输入目标状态:" << endl;
	//输入搜索终点
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> searchtarget.status[i][j];
		}
	}
	//初始化openlist和closelist
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
		cout << "第" << tem++ << "步为:" << endl;
		debug(ans[i]);
	}
	cout << "综上共" << tem-1 << "步" << endl;
	return 0;
}