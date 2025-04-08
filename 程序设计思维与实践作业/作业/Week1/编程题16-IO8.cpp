#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;


class LargeInteger
{
private:
    string value;
public:
    string& getValue() { return value; }
    void fromHex2Dec();
};

string fromInt2String(int num)
{
    string result;
    do
    {
        result.push_back(num % 10 + '0');
        num /= 10;
    } while (num > 0);
    reverse(result.begin(), result.end());
    return result;
}

void LargeInteger::fromHex2Dec()
{
    int sum = 0;
    for (int i = 0; i < value.size(); i++)
    {
        switch (value[i])
        {
        case 'A':
        case 'a':
            sum += 10 * pow(16, value.size() - i - 1);
            break;
        case 'B':
        case 'b':
            sum += 11 * pow(16, value.size() - i - 1);
            break;
        case 'C':
        case 'c':
            sum += 12 * pow(16, value.size() - i - 1);
            break;
        case 'D':
        case 'd':
            sum += 13 * pow(16, value.size() - i - 1);
            break;
        case 'E':
        case 'e':
            sum += 14 * pow(16, value.size() - i - 1);
            break;
        case 'F':
        case 'f':
            sum += 15 * pow(16, value.size() - i - 1);
            break;
        default:
            sum += (value[i] - '0') * pow(16, value.size() - i - 1);
            break;
        }
    }
    value = fromInt2String(sum);
}

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
        while (result.getValue()[i] > '9')
        {
            result.getValue()[i] -= 10;
            if (i == result.getValue().size() - 1)
            {
                result.getValue().push_back('1');
                continue;
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
    LargeInteger a, b;
    while (cin >> a.getValue())
    {
        a.fromHex2Dec();
        cin >> b.getValue();
        b.fromHex2Dec();
        cout << a + b << endl;
    }
}

int main()
{
    solve();
    return 0;
}