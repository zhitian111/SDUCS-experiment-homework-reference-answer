#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <stack>
using namespace std;

vector<string> splitSubstance(string Expression)
{
    vector<string> Substance;
    auto tem = Expression.begin();
    for (auto i = Expression.begin(); i != Expression.end(); i++)
    {
        if (*i == '+')
        {
            Substance.push_back(string(tem, i));
            tem = i + 1;
        }
        if (i == Expression.end() - 1)
        {
            Substance.push_back(string(tem, i + 1));
        }
    }
    return Substance;
}


pair<vector<string>, vector<string>> subExpressions(string equation)
{
    string reactExpression = string(equation.begin(), find(equation.begin(), equation.end(), '='));
    string prodExpression = string(find(equation.begin(), equation.end(), '=') + 1, equation.end());
    vector<string> Reactants = splitSubstance(reactExpression);
    vector<string> Products = splitSubstance(prodExpression);
    return pair<vector<string>, vector<string>>(Reactants, Products);
}


map<string, size_t> countElements(string Substance)
{
    map<string, size_t> ElementCount;
    size_t coefficient = 1;

    auto start = Substance.begin();
    auto end = start;
    if (Substance[0] >= '0' && Substance[0] <= '9')
    {
        end = find_if(Substance.begin(), Substance.end(), [](char c) { return c < '0' || c > '9'; });
        coefficient = stoull(string(start, end));
    }
    
    for (auto i = end; i != Substance.end(); i++)
    {
        size_t count = 1;
        if (*i >= '0' && *i <= '9')     //解析数字
        {
            auto j = find_if(i, Substance.end(), [](char c) { return c < '0' || c > '9'; });
            count = stoull(string(i, j));
            i = j - 1;
        }
        if (*i == '(')                   //解析括号内的化学式
        {
            stack<char> stack;
            stack.push('(');
            auto j = i + 1;
            while (stack.empty() == false && j != Substance.end())
            {
                if (*j == '(')
                {
                    stack.push('(');
                }
                else if (*j == ')')
                {
                    stack.pop();
                }
                j++;                
            }
            j--;
            auto sub = string(i + 1, j);
            // cout << "括号内元素" << sub << endl;
            auto subCount = countElements(sub);
            size_t tem_coefficient = 1;
            if (j + 1 != Substance.end() && *(j + 1) >= '0' && *(j + 1) <= '9')
            {
                auto k = find_if(j + 1, Substance.end(), [](char c) { return c < '0' || c > '9'; });
                tem_coefficient = stoull(string(j + 1, k));
            }
                
            for (auto p : subCount)
            {
                if (ElementCount.find(p.first) == ElementCount.end())
                {
                    ElementCount[p.first] = p.second * coefficient * tem_coefficient;
                }
                else
                {
                    ElementCount[p.first] += p.second * coefficient * tem_coefficient;
                }
            }
            i = j;
        }
        if (*i >= 'A' && *i <= 'Z')     //解析元素符号
        {
            auto j = i + 1;
            if (*(i + 1) >= 'a' && *(i + 1) <= 'z')
            {
                j++;
            }
            string element = string(i, j);
            if (*j >= '0' && *j <= '9')
            {
                auto k = find_if(j, Substance.end(), [](char c) { return c < '0' || c > '9'; });
                count = stoull(string(j, k));
            }
            
            if (ElementCount.find(element) == ElementCount.end())
            {
                ElementCount[element] = count * coefficient;
            }
            else
            {
                ElementCount[element] += count * coefficient;
            }
            i = j - 1;
        }
    }
    return ElementCount;
}

void UnionMap(map<string, size_t>& target, const map<string, size_t>& source)
{
    for (auto i : source)
    {
        if (target.find(i.first) == target.end())
        {
            target[i.first] = i.second;
        }
        else
        {
            target[i.first] += i.second;
        }
    }
}


map<string, size_t> sumElements(vector<string> Substance)
{
    map<string, size_t> ElementCount;
    for (auto i : Substance)
    {
        UnionMap(ElementCount, countElements(i));
    }
    return ElementCount;
}

bool checkEquation(string equation)
{
    pair<vector<string>, vector<string>> subEx = subExpressions(equation);
    // cout << "反应物质: ";
    // for (auto i : subEx.first)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;
    // cout << "产品物质: ";
    // for (auto i : subEx.second)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;
    map<string, size_t> reactantCount = sumElements(subEx.first);
    // cout << "反应物统计完成" << endl;
    map<string, size_t> productCount = sumElements(subEx.second);
    // cout << "反应物统计" << endl;
    // for (auto i : reactantCount)
    // {
    //     cout << i.first << " " << i.second << endl;
    // }
    // cout << "产品统计" << endl;
    // for (auto i : productCount)
    // {
    //     cout << i.first << " " << i.second << endl;
    // }
    return reactantCount == productCount;
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string equation;
        cin >> equation;
        if (checkEquation(equation))
        {
            cout << "Y" << endl;
        }
        else
        {
            cout << "N" << endl;
        }
    }
}

int main()
{
    solve();
    return 0;
}