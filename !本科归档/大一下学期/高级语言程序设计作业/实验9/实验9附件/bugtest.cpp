#include <iostream>
#include "link.h"
using namespace std;

void disp(LinkedList<int> &list){  	//输出链表
	cout << "List: ";
	list.reset();
	//输出各结点数据，直到链表尾
	while (!list.endOfList()) {
		cout << list.data() << "  ";
		list.next();	//使游标指向下一个结点
	}
	cout << endl;
}

int main() {
	LinkedList<int> list;
         
        cout<<"insertFront Bug"<<endl;
		list.insertFront(6);  //头节点之前插入 
        list.insertAt(7);    //当前节点之前插入 
        disp(list);  //因为insertFront()bug：6，7之间插入0，并且6显示不出。 
        

	
        cout<<"insertAfter Bug"<<endl;
		list.insertAfter(8); 
		disp(list);  //因为insertAfter()bug：导致插入的8，也无法显示 
		
		cout<<"deleteCurrent Bug"<<endl;
		list.deleteCurrent();   //导致尾指针rear节点被提前删除 
		disp(list);  
		

}
