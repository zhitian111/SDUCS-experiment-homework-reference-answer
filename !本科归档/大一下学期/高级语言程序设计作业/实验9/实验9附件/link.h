#ifndef LINK_H_
#define LINK_H_

#include <iostream>
using namespace std;
#include "node.h"

/*
* 在LinkedList的设计中，采用了附加指针front和rear，即链表的结构为front->a1->a2->...->rear
* 只有在析构函数中才删除这两个指针，其余的时间这两个指针都是存在的，其中的数据始终为0，不存储用户数据
*/
template <class T>
class LinkedList {
private:
	Node<T> *front, *rear; //表头和表尾指针
	Node<T> *prevPtr, *currPtr; //当前节点的前指针和当前指针。记录表当前遍历位置的指针，由插入和删除操作更新
	int size; //表中元素个数
	int position; //当前元素(*currPtr)在表中的位置序号。由函数reset使用
    //内部函数 
	Node<T>* newNode(const T& item, Node<T> *ptrNext = NULL); //生成新节点，数据与为item，指针域为prtNext
	void freeNode(Node<T> *p); //释放节点

	void copy(const LinkedList<T>& L); //将链表L复制到当前表（假设当前表为空），被复制构造函数和operator=调用

public:  //外部接口 
	LinkedList(); //构造函数
	LinkedList(const LinkedList<T>& L); //复制构造函数
	~LinkedList(); //析构函数
	LinkedList<T>& operator = (const LinkedList<T>& L); //重载赋值运算符

	int getSize() const; //返回链表中元素个数
	bool isEmpty() const; //链表是否为空

	void reset(int pos = 0); //初始化游标的位置
	void next(); //使游标移动到下一个节点
	bool endOfList() const; //游标是否移动到链尾
	int currentPosition() const; //返回游标当前的位置
	
	void insertFront(const T& item); //在表头节点front之前插入节点 
	void insertRear(const T& item); //在链表尾节点rear之前插入节点
	void insertAt(const T& item); //在当前节点之前插入节点
	void insertAfter(const T& item); //在当前节点之后插入节点

	T deleteFront(); //删除头节点
	void deleteCurrent(); //删除当前节点
	
	T& data(); //返回对当前节点成员数据的引用
	const T& data() const; //返回对当前节点成员数据的常引用

	void clear(); //清空链表：释放所有节点的内存空间，被析构函数和operator=使用
	void show(){
		cout<<"*front:" << front<<endl;
		cout<<" *rear:" << rear <<endl;  //表头和表尾指针
		cout<<"*prevPtr:"<<prevPtr<<" *currPtr:"<<currPtr<<endl;   //记录表当前遍历位置的指针，由插入和删除操作更新
		cout<<"size:"<<size <<"  position:"<<position<<endl;
	}
};

//生成新节点，数据与为item，指针域为prtNext。内部函数 
template <class T>
Node<T>* LinkedList<T>::newNode(const T& item, Node<T> *ptrNext) {
	Node<T> *n = new Node<T>(item, ptrNext);
	return n;
}

//释放节点，内部函数 
template <class T>
void LinkedList<T>::freeNode(Node<T> *p) {
	Node<T>* temp = front;
	while (temp->next != p) {  //从头节点后面的节点开始遍历查找指针p的节点 
		temp = temp->next;
		if (temp == currPtr)   //
			position ++;      //currPtr要动吗？ 
	}
	temp->next = p->next;   //删除节点操作 。若没找到？ 
	
	if (currPtr == p)      //若删除的是当前指针所指结点
		currPtr = currPtr->next;
		
	if (prevPtr == p) {    //若删除的是当前指针的前一个结点
		prevPtr = prevPtr->next;
		currPtr = currPtr->next;
	}
	delete p;
	size --;
	position --;
}

//将链表L复制到当前表（假设当前表为空），被复制构造函数和operator=调用 。内部函数 
template <class T>
void LinkedList<T>::copy(const LinkedList<T>& L) {
	Node<T> *temp = L.front->next, *ptr = front;
	while (temp != L.rear) {
		ptr->next = new Node<T>(temp->getData, NULL); // temp->getData() 
		ptr = ptr->next;
		temp = temp->next;
	}
	ptr->next = rear;
	size = L.getSize();
	position = L.currentPosition();
}

//构造函数
template <class T>
LinkedList<T>::LinkedList() {
	front = new Node<T>();  //指向新建节点，实际建立一个空的头node结点和尾节点 
	rear = new Node<T>();
	front->next = rear;   
	currPtr = rear;   //当前指针指向尾节点 
	prevPtr = front;  //之前指针指向头节点 
	size = 0; //不计算front和rear节点 
	position = 0; //在front下一个元素视为0
}

//复制构造函数
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& L) { 
	clear();  //清空释放当前链表
	copy(L);  //复制链表 
}

//析构函数
template <class T>
LinkedList<T>::~LinkedList() {
	LinkedList::clear();  //清空释放当前链表
	delete front;  //释放头指针所指节点 
	delete rear;   //释放尾指针所指节点
}

//重载赋值运算符
template <class T>
LinkedList<T>& LinkedList<T>::operator = (const LinkedList<T>& L) {
	clear();   //清空释放当前链表
	copy(L);   //复制链表 
}

//返回链表中元素个数
template <class T>
int LinkedList<T>::getSize() const {
	return size;
}

//链表是否为空
template <class T>
bool LinkedList<T>::isEmpty() const {
	return (size == 0);
}

//初始化游标的位置
template <class T>
void LinkedList<T>::reset(int pos) { //移动游标(当前指针currPtr)到pos所指的位置
	if (pos > size) {
		cout << "越界，无法访问" << endl;
		return;
	}
	int i = 0;
	prevPtr = front;
	currPtr = front->next;
	while (i < pos) {
		if (currPtr == rear) {
			cout << "越界，无法访问" << endl;
			return;
		}
		i ++;
		currPtr = currPtr->next;
		prevPtr = prevPtr->next;
	}
	position = pos;  
}

//使游标(当前指针currPtr)移动到下一个节点
template <class T>
void LinkedList<T>::next() {
	if (currPtr == rear) {
		cout << "已经到达链表尾，无法移动" << endl;
		return;
	}
	currPtr = currPtr->next;
	prevPtr = prevPtr->next;
	position ++;
}

//游标是否移动到链尾
template <class T>
bool LinkedList<T>::endOfList() const {
	return (currPtr == rear);
}

//返回游标当前的位置
template <class T>
int LinkedList<T>::currentPosition() const {
	return position;
}

//在表头插入节点,原头节点front之前插入 ，插入之后原头节点的值为空，并且新插入的头结点也不为空，值为item. 
template <class T>
void LinkedList<T>::insertFront(const T& item) {
	Node<T>* n = new Node<T>(item, front); 
	front = n;  //front指向新的节点 
	size ++;
	position ++;
}

//在链表尾节点之前插入节点
template <class T>
void LinkedList<T>::insertRear(const T& item) {
	Node<T>* temp = front;
	while (temp->next != rear)
		temp = temp->next;    //temp移至rear之前 
	Node<T> *n = new Node<T>(item, rear);
	temp->next = n;
	size ++;
}

//在当前节点之前插入节点
template <class T>
void LinkedList<T>::insertAt(const T& item) {
	Node<T>* temp = new Node<T>(item, currPtr);
	prevPtr->next = temp;
	prevPtr = temp;
	size ++;
	position ++;
}

//在当前节点之后插入节点
template <class T>
void LinkedList<T>::insertAfter(const T& item) {
	Node<T>* temp = new Node<T>(item, NULL);
	temp->next = currPtr->next;
	currPtr->next = temp;
	size ++;
}

//删除头节点，实质是删除front->next，并返回被删头节点的值
template <class T>
T LinkedList<T>::deleteFront() {
	if (front->next == rear) {
		cout << "没有节点可以删除" << endl; 
	}
	if (prevPtr == front->next) { //如果当前节点的前节点是被删的头结点front->next 
		prevPtr = prevPtr->next;  //不应该移动？ 应该判断currPtr== front->next
		currPtr = currPtr->next;  //如果position不变，当前位置要下移一位，但下面的position-- ，矛盾 
	}
	Node<T>* temp = front->next; // 被删结点处理 
	T d = temp->getData();
	front->next = temp->next;   //修改头指针 
	delete temp;
	size --;
	if (front->next != rear)  
		position --;    //被删节点在当前节点之前。 
	return d;
}

//删除当前节点
template <class T>
void LinkedList<T>::deleteCurrent() {
	Node<T>* temp = currPtr;
	currPtr = currPtr->next;
	delete temp;
	size --;
}
	
//返回对当前节点成员数据的引用
template <class T>
T& LinkedList<T>::data() {
	return currPtr->getData();
}

//返回对当前节点成员数据的常引用
template <class T>
const T& LinkedList<T>::data() const {
	return currPtr->getData();
}

//清空链表内容：释放所有节点的内存空间，被析构函数和operator=使用
template <class T>
void LinkedList<T>::clear() {
	Node<T>* temp;
	while (front->next != rear) {
		temp = front->next;
		front->next = temp->next;
		delete temp;
	}
	size = 0;
	position = 0;
}

#endif //LINK_H_
