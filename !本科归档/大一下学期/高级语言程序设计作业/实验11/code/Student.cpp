#include <iostream>
#include <fstream>

// 定义一个自定义的类
class MyClass {
public:
    int data;

    // 构造函数
    MyClass(int d) : data(d) {}
};

int main() {
    // 创建类对象数组
    MyClass arr[] = { MyClass(1), MyClass(2), MyClass(3), MyClass(4), MyClass(5) };

    // 打开文件流以二进制方式写入
    std::ofstream outfile("output.txt", std::ios::binary);
    if (outfile.is_open()) {
        // 将整个类对象数组一次性写入文件
        outfile.write(reinterpret_cast<const char*>(arr), sizeof(arr));
        outfile.close();
        std::cout << "类数组已成功以二进制方式写入文件。\n";
    }
    else {
        std::cerr << "无法打开文件。\n";
    }

    return 0;
}