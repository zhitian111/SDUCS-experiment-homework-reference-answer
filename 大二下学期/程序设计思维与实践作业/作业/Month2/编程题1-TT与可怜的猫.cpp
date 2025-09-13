#include <bits/stdc++.h>

using namespace std;

void solve()
{
    long long T;
    cin >> T;
    for (long long i = 1; i <= T; i++)
    {
        long long n;
        cin >> n;
        vector<string> msg;
        vector<long long> likeness;
        map<long long, bool> likeness_index;
        map<long long, long long> count;
        long long top_like = 0;
        bool top = false;
        for (long long j = 1; j <= n; j++)
        {
            string operation;
            cin >> operation;
            if (operation.find("Add") != string::npos)
            {
                long long u;
                cin >> u;
                if (likeness_index.find(u) == likeness_index.end())
                {
                    likeness.push_back(u);
                    likeness_index[u] = true;
                    count[u] = 0;
                    msg.push_back("success");
                }
                else
                {
                    msg.push_back("same likeness");
                }
                continue;
            }
            if (operation.find("Close") != string::npos)
            {
                long long u;
                cin >> u;
                if (likeness_index.find(u) != likeness_index.end())
                {
                    likeness.erase(find(likeness.begin(), likeness.end(), u));
                    likeness_index.erase(u);
                    msg.push_back("close " + to_string(u) + " with " + to_string(count[u]));
                    count.erase(u);
                    if (top_like == u)
                    {
                        top = false;
                    }
                }
                else
                {
                    msg.push_back("invalid likeness");
                }
                continue;
            }
            if (operation.find("Chat") != string::npos)
            {
                long long w;
                cin >> w;
                if (likeness.empty())
                {
                    msg.push_back("empty");
                }
                else
                {
                    if (top == false)
                    {
                        count[likeness.front()] += w;
                        msg.push_back("success");
                    }
                    else
                    {
                        count[top_like] += w;
                        msg.push_back("success");
                    }
                }
                continue;
            }
            if (operation.find("Rotate") != string::npos)
            {
                long long x;
                cin >> x;
                if (x < 1 || x > likeness.size())
                {
                    msg.push_back("out of range");
                }
                else
                {
                    likeness.insert(likeness.begin(), likeness[x - 1]);
                    likeness.erase(likeness.begin() + x);
                    msg.push_back("success");
                }
                continue;
            }
            if (operation.find("Prior") != string::npos)
            {
                if (likeness.empty())
                {
                    msg.push_back("empty");
                }
                else
                {
                    auto it = max_element(likeness.begin(), likeness.end());
                    long long u = *it;
                    likeness.erase(it);
                    likeness.insert(likeness.begin(), u);
                    msg.push_back("success");
                }
                continue;
            }
            if (operation.find("Choose") != string::npos)
            {
                long long u;
                cin >> u;
                if (likeness_index.find(u) != likeness_index.end())
                {
                    msg.push_back("success");
                    auto it = find(likeness.begin(), likeness.end(), u);
                    likeness.erase(it);
                    likeness.insert(likeness.begin(), u);
                }
                else
                {
                    msg.push_back("invalid likeness");
                }
                continue;
            }
            if (operation.find("Top") != string::npos)
            {
                long long x;
                cin >> x;
                if (likeness_index.find(x) != likeness_index.end())
                {
                    top_like = x;
                    top = true;
                    msg.push_back("success");
                }
                else
                {
                    msg.push_back("invalid likeness");
                }
                continue;
            }
            if (operation.find("Untop") != string::npos)
            {
                if (top == true)
                {
                    top = false;
                    msg.push_back("success");
                }
                else
                {
                    msg.push_back("no such person");
                }
            }
        }
        if (top == true && count[top_like] > 0)
        {
            msg.push_back("Bye " + to_string(top_like) + ": " + to_string(count[top_like]));
            likeness.erase(find(likeness.begin(), likeness.end(), top_like));
            likeness_index.erase(top_like);
            count.erase(top_like);
            top = false;
        }
        
        for (auto& j : likeness)
        {
            if (count[j] > 0)
            {
                msg.push_back("Bye " + to_string(j) + ": " + to_string(count[j]));
            }
        }
        
        for (long long j = 0; j < msg.size(); j++)
        {
            cout << "OpId #" << j + 1 << ": " << msg[j] << "." <<endl;
        }
    }
}

int main()
{
    solve();
    return 0;
}