#include <iostream>
#include "link.h"
using namespace std;

void disp(LinkedList<int> &list){  	//�������
	cout << "List: ";
	list.reset();
	//�����������ݣ�ֱ������β
	while (!list.endOfList()) {
		cout << list.data() << "  ";
		list.next();	//ʹ�α�ָ����һ�����
	}
	cout << endl;
}

int main() {
	LinkedList<int> list;
	     cout<<"init:"<<endl;
         list.show();
         
        cout<<"insertFront Bug"<<endl;
		list.insertFront(6);  //ͷ�ڵ�֮ǰ���� 
        list.insertAt(7);    //��ǰ�ڵ�֮ǰ���� 
        disp(list);  //��ΪinsertFront()bug��6��7֮�����0������6��ʾ������ 
        

	
        cout<<"insertAfter Bug"<<endl;
		list.insertAfter(8); 
		disp(list);  //��ΪinsertAfter()bug�����²����8��Ҳ�޷���ʾ 
		
		cout<<"deleteCurrent Bug"<<endl;
		list.deleteCurrent();   //����βָ��rear�ڵ㱻��ǰɾ�� 
		disp(list);  
		
		/*cout<<"deleteFront Bug"<<endl;
		list.reset(0);
		cout<<list.data()<<endl;
		list.deleteFront();
		cout<<list.data()<<endl;  //currPtrδ�� 
         */ 
        
        //disp(list); 
        
        cout<<"clear Bug"<<endl;
        list.reset(1);
        cout<<list.data()<<endl;
        list.clear();
        cout<<list.data()<<endl;

}
