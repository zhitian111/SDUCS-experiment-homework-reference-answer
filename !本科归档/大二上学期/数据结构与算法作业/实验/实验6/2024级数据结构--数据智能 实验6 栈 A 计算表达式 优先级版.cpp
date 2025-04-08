/*2024级数据结构--数据智能 实验6 栈 A 计算表达式 优先级版.cpp*/
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
    Stack(): size(2000), top(-1) { data = new T[size]; }
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

int priority(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) { len++; }
    return len;
}

void Solution::solute()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Stack<char> op;
        Stack<char> back;
        char c[2500];
        char back_char[2500];
        int index = 0;
        cin >> c;
        for (int i = 0; i < strlen(c); i++)
        {
            //如果是数字，直接加入后缀表达式
            if (c[i] <= '9' && c[i] >= '0')
            {
                back.push(c[i]);
                back_char[index++] = c[i];
                continue;
            }
            else
            {
                //如果是（，直接压入栈
                if (c[i] == '(')
                {
                    op.push(c[i]);
                }
                //如果是），弹出栈直到遇到（
                else if (c[i] == ')')
                {
                    while (op.Top() != '(')
                    {
                        char op_char = op.Top();
                        op.pop();
                        back.push(op_char);
                        back_char[index++] = op_char;
                    }
                    op.pop();
                }
                else
                {
                    //如果是操作符，如果栈顶运算符的优先级小于当前运算符的优先级，或者栈为空或者栈顶是（，则直接压入栈
                    if (op.empty() || priority(c[i]) > priority(op.Top()) || op.Top() == '(')
                    {
                        op.push(c[i]);
                    }
                    //否则，弹出栈直到栈顶运算符优先级小于当前运算符优先级，或者遇到（，然后将当前运算符压入栈
                    else
                    {
                        while (!op.empty() && priority(c[i]) <= priority(op.Top()))
                        {
                            char op_char = op.Top();
                            op.pop();
                            back.push(op_char);
                            back_char[index++] = op_char;
                        }
                        op.push(c[i]);

                    }
                }
            }
        }
        //弹出栈剩余的运算符
        while (!op.empty())
        {
            char op_char = op.Top();
            op.pop();
            back.push(op_char);
            back_char[index++] = op_char;
        }
        back.display();
        // for (int i = 0; i < strlen(back_char); i++)
        // {
        //     cout << back_char[i] <<' ';
        // }

        Stack<double> ans;

        for (int i = 0; i < index; i++)
        {
            if (back_char[i] <= '9' && back_char[i] >= '0')
            {
                ans.push(back_char[i] - '0');
            }
            else
            {
                double num1 = ans.Top();
                ans.pop();
                double num2 = ans.Top();
                ans.pop();
                switch (back_char[i])
                {
                case '+':
                    ans.push(num2 + num1);
                    break;
                case '-':
                    ans.push(num2 - num1);
                    break;
                case '*':
                    ans.push(num2 * num1);
                    break;
                case '/':
                    ans.push(num2 / num1);
                    break;
                    // case '^':
                        // ans.push(pow(num2, num1));
                        // break;
                default:
                    break;
                }
            }
        }
        printf("%.2f\n", ans.Top());
    }

}

int main()
{
    Solution solute;
    solute.solute();
    return 0;
}