#include <iostream>

// 定义一个比较类
class MyComparator {
public:
    // 重载函数调用运算符
    bool operator()(const int& a, const int& b) const {
        return a > b; // 自定义比较规则
    }
};

// 使用比较类的类模板
template <typename T, typename Compare = MyComparator>
class MyClass {
public:
    // 成员变量
    T data;

    // 构造函数，接受比较类作为参数
    MyClass(const T& d, const Compare& cmp = Compare()) : data(d), comparator(cmp) {}

    // 比较函数
    bool compare(const T& other) const {
        return comparator(data, other);
    }

private:
    Compare comparator; // 保存比较类的实例
};

int main() {
    // 创建类实例，使用默认比较规则
    MyClass<int> myObj(5);

    // 使用比较函数
    std::cout << myObj.compare(3) << std::endl;  // 输出 1（true）

    // 创建类实例，使用自定义比较规则
    MyClass<int, MyComparator> customObj(5);

    // 使用比较函数
    std::cout << customObj.compare(8) << std::endl;  // 输出 0（false）

    return 0;
}