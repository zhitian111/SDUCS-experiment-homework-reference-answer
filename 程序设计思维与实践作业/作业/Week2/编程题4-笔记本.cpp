#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;


void solve()
{
    int m;
    cin >> m;
    map<string, bool> dictionary;
    
    for (int i = 0; i < m; i++)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            string word;
            cin >> word;
            if (dictionary.find(word) == dictionary.end())
            {
                dictionary[word] = true;
                cout << "write\n";
            }
            else
            {
                cout << "found\n";
            }

        }
        if (op == 2)
        {
            string word;
            cin >> word;
            if (dictionary.find(word) != dictionary.end())
            {
                dictionary.erase(word);
                cout << "erased\n";
            }
            else
            {
                cout << "not found\n";
            }
        }
        if (op == 3)
        {
            for (auto& word : dictionary)
            {
                cout << word.first << " ";
            }
            cout << endl;
        }
    }
}

int main()
{
    solve();
    return 0;
}