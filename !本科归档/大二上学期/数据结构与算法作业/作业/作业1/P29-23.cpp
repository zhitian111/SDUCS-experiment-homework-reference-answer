#include<iostream>

using namespace std;

/*
��(1)��
�ֶ����㲿��

gcd(20,30) = gcd(30,20) =gcd(20,10) = gcd(10,0) = 10

gcd(112,41) = gcd(41,30) = gcd(30,11) = gcd(11,8) = gcd(8,3) = gcd(3,2) = gcd(2,1) = gcd(1,0) = 1;

*/
/*
��(2)��
�����Ļ�������Ϊgcd(x,y) = x (y=0)��
�ݹ鲿��Ϊgcd(x,y) = gcd(y,x mod y)���ȣ�����a<b����ô��Ȼ����a%b=a��Ҳ�ͻ����gcd(a,b)=gcd(b,a)����Ȼ������
Ȼ����a��b��ʱ��������a=x��b+y,Ҳ�������ǽ���ֽ��Ϊ���̳��Գ�������������ʽ��
�ֽ�Ϊ�̳��Գ�������������ʽ��
����a,b���κ�һ����Լ��d��������d|a,d|x��b�����Ծͻ���d|(a?x��b)
��ô����Ϊa=x��b+y,d|(a?x��b)����d|y������ģ����Ķ��壬��a%b=y����ô��ŷ������㷨��֤�������
*/

//���벿��
unsigned long long gcd(unsigned long long x, unsigned long long y)
{
	if (y == 0)
	{
		return x;
	}
	return gcd(y, x % y);
}
