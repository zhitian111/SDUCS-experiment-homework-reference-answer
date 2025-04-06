#include <bits/stdc++.h>

using namespace std;

vector<string> formatter(string s)
{
    vector<string> res;
    int depth = 0;
    bool is_start = false;

    auto pos = s.find("BEGIN");
    pos += 5;
    depth = 1;
    res.push_back("BEGIN");
    while (true)
    {
        while (s[pos] == ' ' || s[pos] == '\t')
        {
            pos++;
        }
        if (s[pos] == 'L')
        {
            string tem;
            pos += 4;
            while (s[pos] == ' ' || s[pos] == '\t')
            {
                pos++;
            }
            while (s[pos] != ' ' && s[pos] != '\t')
            {
                tem += s[pos];
                pos++;
            }
            string header = "LOOP ";
            for (int i = 0; i < depth; i++)
            {
                header = "\t" + header;
            }
            depth++;
            res.push_back(header + tem);
        }
        else if (s[pos] == 'O')
        {
            string tem;
            pos += 2;
            while (s[pos] == ' ' || s[pos] == '\t')
            {
                pos++;
            }
            while (s[pos] != ' ' && s[pos] != '\t')
            {
                tem += s[pos];
                pos++;
            }
            string header = "OP ";
            for (int i = 0; i < depth; i++)
            {
                header = "\t" + header;
            }
            res.push_back(header + tem);
        }
        else if (s[pos] == 'E')
        {
            if (depth == 1)
            {
                res.push_back("END");
                break;
            }
            else
            {
                depth--;
                string header = "END";
                for (int i = 0; i < depth; i++)
                {
                    header = "\t" + header;
                }
                res.push_back(header);
                pos+=3;
            }
        }
        // cout << res.back() << endl;
    }
    return res;
}

void solve()
{
    string s;
    struct node
    {
        long long cnt;
        long long depth;
    };

    struct ans_node
    {
        long long factor;
        long long exp;
    };


    stack<node> st;

    vector<ans_node> ans;
    string ss;
    while (getline(cin, s))
    {
        ss += s;
        ss += " ";
    }
    vector<string> code = formatter(ss);

    // for (auto& s : code)
    // {
    //     cout << s << endl;
    // }

    for (long long i = 0; i < code.size(); i++)
    {
        s = code[i];
        if (s.find("BEGIN") != string::npos)
        {
            continue;
        }
        if (s.find("END") != string::npos)
        {
            if (st.empty())
            {
                break;
            }
            else
            {
                long long depth = count(s.begin(), s.end(), '\t');
                if (st.top().depth == depth)
                {
                    st.pop();
                }
            }
        }
        if (s.find("LOOP") != string::npos)
        {
            long long depth = count(s.begin(), s.end(), '\t');
            if (s[s.find("LOOP") + 5] == 'n')
            {
                st.push({ -1, depth });
                continue;
            }
            long long cnt = atoi(s.substr(s.find("LOOP") + 5).c_str());
            st.push({ cnt, depth });
            continue;
        }
        if (s.find("OP") != string::npos)
        {
            stack<node> temp = st;
            long long factor;
            long long exp = 0;

            if (s[s.find("OP") + 3] == 'n')
            {
                factor = 1;
                exp = 1;
                while (!temp.empty())
                {
                    node& t = temp.top();
                    if (t.cnt == -1)
                    {
                        exp++;
                    }
                    if (t.cnt != -1)
                    {
                        factor *= t.cnt;
                    }
                    temp.pop();
                }
                ans.push_back({ factor, exp });
                continue;
            }
            factor = atoi(s.substr(s.find("OP") + 3).c_str());
            while (!temp.empty())
            {
                node& t = temp.top();
                if (t.cnt == -1)
                {
                    exp++;
                }
                if (t.cnt != -1)
                {
                    factor *= t.cnt;
                }
                temp.pop();
            }
            ans.push_back({ factor, exp });
        }
    }

    vector<ans_node> final_ans;
    cout << "Runtime = ";


    for (auto& a : ans)
    {
        bool found = false;
        for (auto& b : final_ans)
        {
            if (a.exp == b.exp)
            {
                found = true;
                b.factor += a.factor;
                break;
            }
        }
        if (!found)
        {
            final_ans.push_back(a);
        }
    }

    if (final_ans.empty())
    {
        cout << "0" << endl;
        return;
    }

    bool zero_mark = true;
    for (auto a : final_ans)
    {
        if (a.factor != 0)
        {
            zero_mark = false;
        }
    }

    if (zero_mark)
    {
        cout << 0 << endl;
        return;
    }

    for (long long i = 0; i < final_ans.size(); i++)
    {
        for (long long j = 0; j < final_ans.size() - i - 1; j++)
        {
            if (final_ans[j].exp < final_ans[j + 1].exp)
            {
                swap(final_ans[j], final_ans[j + 1]);
            }
        }
    }

    bool start = false;

    for (auto& a : final_ans)
    {
        if (start)
        {
            if (a.exp == final_ans[0].exp)
            {
                if (a.factor == 1)
                {
                    if (a.exp == 1)
                    {
                        cout << "n";
                    }
                    if (a.exp == 0)
                    {
                        cout << "1";
                    }
                    if (a.exp > 1)
                    {
                        cout << "n^" << a.exp;
                    }
                }
                if (a.factor == 0)
                {
                    continue;
                }
                if (a.factor > 1)
                {
                    cout << a.factor;
                    if (a.exp == 1)
                    {
                        cout << "*n";
                    }
                    if (a.exp == 0)
                    {
                        continue;
                    }
                    if (a.exp > 1)
                    {
                        cout << "*n^" << a.exp;
                    }
                }
            }
            else
            {
                if (a.factor == 1)
                {
                    if (a.exp == 1)
                    {
                        cout << "+n";
                    }
                    if (a.exp == 0)
                    {
                        cout << "+1";
                    }
                    if (a.exp > 1)
                    {
                        cout << "+n^" << a.exp;
                    }
                }
                if (a.factor == 0)
                {
                    continue;
                }
                if (a.factor > 1)
                {
                    cout << "+" << a.factor;
                    if (a.exp == 1)
                    {
                        cout << "*n";
                    }
                    if (a.exp == 0)
                    {
                        continue;
                    }
                    if (a.exp > 1)
                    {
                        cout << "*n^" << a.exp;
                    }
                }
            }
        }
        else
        {
            if (a.factor == 0)
            {
                continue;
            }
            if (a.factor == 1)
            {
                if (a.exp == 1)
                {
                    cout << "n";
                    start = true;
                }
                if (a.exp == 0)
                {
                    cout << "1";
                    start = true;
                }
                if (a.exp > 1)
                {
                    cout << "n^" << a.exp;
                    start = true;
                }
            }
            if (a.factor > 1)
            {
                cout << a.factor;
                if (a.exp == 1)
                {
                    cout << "*n";
                    start = true;
                }
                if (a.exp == 0)
                {
                    continue;
                }
                if (a.exp > 1)
                {
                    cout << "*n^" << a.exp;
                    start = true;
                }
            }
        }
    }
}


int main()
{
    solve();
    return 0;
}