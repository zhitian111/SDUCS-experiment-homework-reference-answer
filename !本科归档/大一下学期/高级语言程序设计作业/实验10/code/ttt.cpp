#include <iostream>

// ����һ���Ƚ���
class MyComparator {
public:
    // ���غ������������
    bool operator()(const int& a, const int& b) const {
        return a > b; // �Զ���ȽϹ���
    }
};

// ʹ�ñȽ������ģ��
template <typename T, typename Compare = MyComparator>
class MyClass {
public:
    // ��Ա����
    T data;

    // ���캯�������ܱȽ�����Ϊ����
    MyClass(const T& d, const Compare& cmp = Compare()) : data(d), comparator(cmp) {}

    // �ȽϺ���
    bool compare(const T& other) const {
        return comparator(data, other);
    }

private:
    Compare comparator; // ����Ƚ����ʵ��
};

int main() {
    // ������ʵ����ʹ��Ĭ�ϱȽϹ���
    MyClass<int> myObj(5);

    // ʹ�ñȽϺ���
    std::cout << myObj.compare(3) << std::endl;  // ��� 1��true��

    // ������ʵ����ʹ���Զ���ȽϹ���
    MyClass<int, MyComparator> customObj(5);

    // ʹ�ñȽϺ���
    std::cout << customObj.compare(8) << std::endl;  // ��� 0��false��

    return 0;
}