#include <iostream>
#include <fstream>

// ����һ���Զ������
class MyClass {
public:
    int data;

    // ���캯��
    MyClass(int d) : data(d) {}
};

int main() {
    // �������������
    MyClass arr[] = { MyClass(1), MyClass(2), MyClass(3), MyClass(4), MyClass(5) };

    // ���ļ����Զ����Ʒ�ʽд��
    std::ofstream outfile("output.txt", std::ios::binary);
    if (outfile.is_open()) {
        // ���������������һ����д���ļ�
        outfile.write(reinterpret_cast<const char*>(arr), sizeof(arr));
        outfile.close();
        std::cout << "�������ѳɹ��Զ����Ʒ�ʽд���ļ���\n";
    }
    else {
        std::cerr << "�޷����ļ���\n";
    }

    return 0;
}