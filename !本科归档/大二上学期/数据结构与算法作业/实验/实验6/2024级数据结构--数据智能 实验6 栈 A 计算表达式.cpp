/*2024级数据结构--数据智能 实验6 栈 A 计算表达式.cpp*/
#include <iostream>
#define debug cout << "debug" << endl;
using namespace std;

template<class T>
class Stack {
private:
    T* data;
    int top;
    int size;
public:
    Stack(int size) :size(size), top(-1), data(new T[size]) {}
    Stack(): size(2500), top(-1) { data = new T[size]; }
    ~Stack() { delete[] data; }
    T Top() { return data[top]; }
    int getSize() { return size; }
    void push(T val) {
        if (full()) { return; }
        data[++top] = val;
    }
    void pop() {
        if (empty()) { return; }
        data[top--].~T();
    }
    void display() {
        for (int i = 0; i <= top; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    bool empty() { return top == -1; }
    bool full() { return top == size - 1; }
};

class Solution {
public:
    void solute();
};



size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) { len++; }
    return len;
}

double coculate(char op, double a, double b)
{
    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
    // switch (op)
    // {
    // case '+': cout<< a + b << endl; return a + b;
    // case '-': cout<< a - b << endl; return a - b;
    // case '*': cout<< a * b << endl; return a * b;
    // case '/': cout<< a / b << endl; return a / b;
    // default: return 0;
    // }
}

void one_shoot(Stack<char>& exception, Stack<double>& value)
{
    if (exception.empty()) { return; }
    if (value.empty()) { return; }
    if (exception.Top() == '(') { return; }
    double b = value.Top();
    value.pop();
    double a = value.Top();
    value.pop();
    char op = exception.Top();
    exception.pop();
    if (op == '*' || op == '/')
    {
        if (exception.empty() || exception.Top() == '(' || exception.Top() == '+' || exception.Top() == '-')
        {
            value.push(coculate(op, a, b));            
            return;
        }
        else
        {
            value.push(a);
            one_shoot(exception, value);
            double ans = coculate(op, value.Top(), b);
            value.pop();
            value.push(ans);
        }
    }
    else
    {
        if (exception.Top() == '+' || exception.Top() == '-' || exception.Top() == '(' || exception.empty())
        {
            if (op == '+')
            {
                if (exception.Top() == '+' || exception.Top() == '(' || exception.empty())
                {
                    value.push(a + b);
                }
                else if (exception.Top() == '-')
                {
                    value.push(a - b);
                }
            }
            else if (op == '-')
            {
                if (exception.Top() == '+' || exception.Top() == '(' || exception.empty())
                {
                    value.push(a - b);
                }
                else if (exception.Top() == '-')
                {
                    value.push(a + b);
                }
            }
        }
        else
        {
            value.push(a);
            one_shoot(exception, value);
            if (op == '+')
            {
                if (exception.Top() == '+' || exception.Top() == '(' || exception.empty())
                {
                    double ans = value.Top() + b;
                    value.pop();
                    value.push(ans);
                }
                else if (exception.Top() == '-')
                {
                    double ans = value.Top() - b;
                    value.pop();
                    value.push(ans);
                }
            }
            else if (op == '-')
            {
                if (exception.Top() == '+' || exception.Top() == '(' || exception.empty())
                {
                    double ans = value.Top() - b;
                    value.pop();
                    value.push(ans);
                }
                else if (exception.Top() == '-')
                {
                    double ans = value.Top() + b;
                    value.pop();
                    value.push(ans);
                }
            }
        }
    }
}

void Solution::solute()
{
    char exp[2000];
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> exp;
        Stack<char> exception;
        Stack<double> value;
        for (int j = 0; j < strlen(exp); j++)
        {
            if (exp[j] == '(') { exception.push(exp[j]); }
            else if (exp[j] == ')')
            {
                while (exception.Top() != '(')
                {
                    one_shoot(exception, value);
                }
                exception.pop();
            }
            else if (exp[j] == '+' || exp[j] == '-' || exp[j] == '*' || exp[j] == '/')
            {
                exception.push(exp[j]);
            }

            else if (exp[j] >= '0' && exp[j] <= '9')
            {
                value.push(double(exp[j] - '0'));
            }
        }
        while (!exception.empty()&&value.getSize()>=2)
        {
            one_shoot(exception, value);
        }
        printf("%.2f\n", value.Top());
    }
}

int main()
{
    Solution solution;
    solution.solute();
    return 0;
}