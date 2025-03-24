// 考察静态成员，复制构造函数 、对象指针、引用、
// 留一个对象没有释放，产生内存泄漏。 

#include <iostream>
using namespace std;

class Object   //C++中没有像java中的根类Object，此处为自己定义的一个类。
{  
  public:
	static int count;  //静态成员，统计对象的个数。
	
	Object(){            //构造方法 
		count++;         //统计个数累计。 
		id=count;        //对象编号 
		cout<<"in Constructor. this:"<<this<<", id:"<<id<<endl;  //测试用，输出每建一个对象的指针和编号

	} 
	
	Object(const Object &ob){   //复制构造函数。如果自己写复制构造函数，则复制成员的任务需要自己完成。默认系统自动复制 
		count++;
		id=count;        // id不需要复制，而是累计编号 
		cout<<"in Copy constructor:Object(Object &ob) this:"<<this<<", ob:"<<&ob<<", id:"<<id<<endl; //输出自身指针和被复制对象指针及自身id 

	}

	~Object(){
		cout<<"Remove:"<<this<<", id:"<<this->id<<endl;  //输出被删除的对象指针和编号 
		count--;
	}

	int getId(){
		return id;
	}
	
	private:
	int id;  // 成员变量，代表对象编号。

};

int Object::count=0;  // 静态成员在类外初始化

void exec()
{
   Object *a=new Object, &b(*new Object(*a));// 请注释此句的含义 
 
   cout<<"In exec:after(a,b),count="<<Object::count<<endl;
   cout<<"exec:a id:"<<a->getId()<<endl;
   cout<<"exec:b id:"<<b.getId()<<endl;
   
   Object c,&cc(c);
   cout<<"In exec:after c, count="<<Object::count<<endl;
   
   delete a;
   cout<<"after delete a, count="<<Object::count<<endl;
   
  
}

int main()
{
	exec();

	cout<<"return main, after exec, count:"<<Object::count<<endl;   
	
	return 0;           
}
