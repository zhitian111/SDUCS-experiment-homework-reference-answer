#include <iostream>
using namespace std;
class test
{
public:
    test(int a) {};
    test() { test(1); };
};

int main()
{
    test();
    return 0;
}
