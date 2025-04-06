//Array.h
#include<iostream>
using namespace std;
//���������п�������������
#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>

//������ģ�嶨��
template <class T>
class Array {
private:
	T* list;	//T����ָ�룬���ڴ�Ŷ�̬����������ڴ��׵�ַ
	int size;	//�����С��Ԫ�ظ�����
public:
	Array(int sz = 50);			//���캯��
	Array(const Array<T>& a);	//�������캯��
	~Array();	//��������
	Array<T>& operator = (const Array<T>& rhs); //����"="ʹ�������������帳ֵ
	T& operator [] (int i);	//����"[]"��ʹArray���������C++��ͨ���������
	const T& operator [] (int i) const;	//"[]"�������const�汾
	operator T* ();	//���ص�T*���͵�ת����ʹArray���������C++��ͨ���������
	operator const T* () const;	//��T*����ת����������const�汾
	int getSize() const;	//ȡ����Ĵ�С
	void resize(int sz);	//�޸�����Ĵ�С
	void insertSort();//ֱ�Ӳ�������
	void selectSort();//ѡ������
	void BubbleSort();//ð������
	int seqSearch(T key);//˳�����
	void show() { for (int i = 0; i < size; i++)cout << list[i] << " "; }
};


//���캯��
template <class T>
Array<T>::Array(int sz) {
	assert(sz >= 0);	//szΪ�����С��Ԫ�ظ�������Ӧ���Ǹ�
	size = sz;	// ��Ԫ�ظ�����ֵ������size
	list = new T[size];	//��̬����size��T���͵�Ԫ�ؿռ�
}

//��������
template <class T>
Array<T>::~Array() {
	delete[] list;
}

//�������캯��
template <class T>
Array<T>::Array(const Array<T>& a) {
	//�Ӷ���xȡ�������С������ֵ����ǰ����ĳ�Ա
	size = a.size;
	//Ϊ���������ڴ沢���г�����
	list = new T[size];	// ��̬����n��T���͵�Ԫ�ؿռ�
	//�Ӷ���X��������Ԫ�ص�������
	for (int i = 0; i < size; i++)
		list[i] = a.list[i];
}

//����"="�������������rhs��ֵ��������ʵ�ֶ���֮������帳ֵ
template <class T>
Array<T>& Array<T>::operator = (const Array<T>& rhs) {
	if (&rhs != this) {
		//����������������С��rhs��ͬ����ɾ������ԭ���ڴ棬Ȼ�����·���
		if (size != rhs.size) {
			delete[] list;		//ɾ������ԭ���ڴ�
			size = rhs.size;	//���ñ�����������С
			list = new T[size];	//���·���n��Ԫ�ص��ڴ�
		}
		//�Ӷ���X��������Ԫ�ص�������
		for (int i = 0; i < size; i++)
			list[i] = rhs.list[i];
	}
	return *this;	//���ص�ǰ���������
}

//�����±��������ʵ������ͨ����һ��ͨ���±����Ԫ�أ����Ҿ���Խ���鹦��
template <class T>
T& Array<T>::operator[] (int n) {
	assert(n >= 0 && n < size);	//����±��Ƿ�Խ��
	return list[n];			//�����±�Ϊn������Ԫ��
}

template <class T>
const T& Array<T>::operator[] (int n) const {
	assert(n >= 0 && n < size);	//����±��Ƿ�Խ��
	return list[n];			//�����±�Ϊn������Ԫ��
}

//����ָ��ת�����������Array��Ķ�����ת��ΪT���͵�ָ�룬
//ָ��ǰ�����е�˽�����顣
//���������ʹ����ͨ�����׵�ַһ��ʹ��Array��Ķ�����
template <class T>
Array<T>::operator T* () {
	return list;	//���ص�ǰ������˽��������׵�ַ
}

template <class T>
Array<T>::operator const T* () const {
	return list;	//���ص�ǰ������˽��������׵�ַ
}

//ȡ��ǰ����Ĵ�С
template <class T>
int Array<T>::getSize() const {
	return size;
}

// �������С�޸�Ϊsz
template <class T>
void Array<T>::resize(int sz) {
	assert(sz >= 0);	//���sz�Ƿ�Ǹ�
	if (sz == size)	//���ָ���Ĵ�С��ԭ�д�Сһ����ʲôҲ����
		return;
	T* newList = new T[sz];	//�����µ������ڴ�
	int n = (sz < size) ? sz : size;	//��sz��size�н�С��һ����ֵ��n
	//��ԭ��������ǰn��Ԫ�ظ��Ƶ���������
	for (int i = 0; i < n; i++)
		newList[i] = list[i];
	delete[] list;		//ɾ��ԭ����
	list = newList;	// ʹlistָ��������
	size = sz;	//����size
}
#endif  //ARRAY_H

template<class T>
void Array<T>::insertSort()//ֱ�Ӳ�������(�Ӵ�С)
{
	for (int i = 0; i < size; i++)
	{
		T tem = list[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (list[j] < tem){
				list[j + 1] = list[j];
			}
			if(list[j]>=tem){
				list[j + 1] = tem;
				break;
			}
			if (j == 0)
			{
				list[j] = tem;
			}
		}
	}
}


template<class T>
void Array<T>::selectSort()//ѡ������(�Ӵ�С)
{
	for (int i = 0; i < size; i++)
	{
		T max = list[i];
		T tem = list[i];
		T mark = i;
		for (int j = i; j < size; j++)
		{
			if (list[j] > max)
			{
				max = list[j];
				mark = j;
			}
		}
		list[i] = max;
		list[mark] = tem;
	}
}

template<class T>
void Array<T>::BubbleSort()//ð������(�Ӵ�С)
{
	for (int i = 0; i < size; i++)
	{
		T tem;
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (list[j] < list[j + 1])
			{
				tem = list[j + 1];
				list[j + 1] = list[j];
				list[j] = tem;
			}
		}
	}
}

template<class T>
int Array<T>::seqSearch(T key)//˳�����
{
	for (int i = 0; i < size; i++)
	{
		if (list[i] == key)
		{
			return i;
		}
	}
}

int main()
{

	Array<int> a(10);
	Array<int> b(10);
	Array<int> c(10);

	for (int i = 0; i < 10; i++)
	{
		a[i] = i;
		b[i] = i;
		c[i] = i;
	}
	a.show();
	cout << endl;
	a.BubbleSort();
	a.show();
	cout << endl;
	b.insertSort();
	b.show();
	cout << endl;
	c.selectSort();
	c.show();
	cout << endl;
	cout << c.seqSearch(1) << endl;
	return 0;
}