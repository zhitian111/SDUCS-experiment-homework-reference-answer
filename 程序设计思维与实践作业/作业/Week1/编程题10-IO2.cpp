#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


class LargeInteger
{
private:
    string value;
public:
    string& getValue() { return value; }
};

LargeInteger operator+(LargeInteger& a, LargeInteger& b)
{
    LargeInteger result;
    int size_a = a.getValue().size();
    int size_b = b.getValue().size();
    auto tem_a = a.getValue();
    auto tem_b = b.getValue();
    reverse(tem_a.begin(), tem_a.end());
    reverse(tem_b.begin(), tem_b.end());
    for (int i = 0; i < min(size_a, size_b); i++)
    {
        result.getValue().push_back(tem_a[i] + tem_b[i] - '0');
    }
    // cout <<result.getValue()<<endl;
    if (size_a > size_b)
    {
        result.getValue().insert(result.getValue().end(), tem_a.begin() + size_b, tem_a.end());
    }
    if (size_b > size_a)
    {
        result.getValue().insert(result.getValue().end(), tem_b.begin() + size_a, tem_b.end());
    }
    for (int i = 0;i < result.getValue().size();i++)
    {
        if (result.getValue()[i] > '9')
        {
            result.getValue()[i] -= 10;
            if (i == result.getValue().size() - 1)
            {
                result.getValue().push_back('1');
                break;
            }
            result.getValue()[i + 1] += 1;
        }
    }
    reverse(result.getValue().begin(), result.getValue().end());
    return result;
}

LargeInteger operator-(LargeInteger& a, LargeInteger& b)
{

}

istream& operator>>(istream& in, LargeInteger& a)
{
    in >> a.getValue();
    return in;
}

ostream& operator<<(ostream& out, LargeInteger& a)
{
    out << a.getValue();
    return out;
}

ostream& operator<<(ostream& out, LargeInteger a)
{
    out << a.getValue();
    return out;
}

void solve()
{
    while (true)
    {
        LargeInteger a, b;
        cin >> a >> b;
        if (a.getValue() == string("0") && b.getValue() == string("0"))
        {
            break;
        }
        cout << a + b << endl;
    }
}

int main()
{
    solve();
    return 0;
}