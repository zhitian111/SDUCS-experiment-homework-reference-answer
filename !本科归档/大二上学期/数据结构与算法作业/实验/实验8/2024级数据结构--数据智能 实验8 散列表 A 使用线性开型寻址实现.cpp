/*2024级数据结构--数据智能 实验8 散列表 A 使用线性开型寻址实现.cpp*/
#include <iostream>

using namespace std;

template<class T>
class hashTable
{
private:
    T divisor;
    int size;
    T* table;
    bool* used;
public:
    hashTable(int size, T& divisor);
    void find(T& key);
    void insert(T& key);
    void erase(T& key);
    void display();
};

template<class T>
void hashTable<T>::display()
{
    for (int i = 0; i < size; i++)
    {
        cout << table[i] << " ";
    }
    cout << endl;
}

template<class T>
hashTable<T>::hashTable(int size, T& divisor)
{
    this->size = size;
    this->divisor = divisor;
    table = new T[size];
    for (int i = 0; i < size; i++)
    {
        table[i] = -1;
    }
    used = new bool[size];
    for (int i = 0; i < size; i++)
    {
        used[i] = false;
    }
}

template<class T>
void hashTable<T>::insert(T& key)
{
    int index = key % size;
    while (index < size)
    {
        if (used[index] == false)
        {
            table[index] = key;
            used[index] = true;
            cout << index << endl;
            return;
        }
        if (table[index] == key)
        {
            cout << "Existed" << endl;
            return;
        }
        index++;
        index = index % divisor;
    }
}

template<class T>
void hashTable<T>::find(T& key)
{
    int index = key % size;
    while (index < size)
    {
        if (used[index] == false)
        {
            cout << -1 << endl;
            return;
        }
        if (table[index] == key)
        {
            cout << index << endl;
            return;
        }
        index++;
        index = index % divisor;
    }
}


template<class T>
void hashTable<T>::erase(T& key)
{
    int s = key % divisor;
    int j = s;
    int b = 0;
    do
    {
        if (table[j] == key)
        {
            table[j] = -1;
            used[j] = false;
            b = 1;
            break;
        }
        else
        {
            j = (j + 1) % divisor;
        }
    } while (j != s && used[j] == true);
    if (b == 0)
    {
        cout << "Not Found" << endl;
        return;
    }
    s = j;
    j = (j + 1) % divisor;
    int k = s;
    int sum = 0;
    for (int i = j; i != (j + divisor - 1) % divisor; i = (i + 1) % divisor)
    {
        if (used[i] == false)
        {
            break;
        }
        int x2 = table[i];
        if (i == (x2 % divisor) || ((x2 % divisor) > s) && i > (x2 % divisor))
        {
            continue;
        }
        else
        {
            if (i < s && i>(x2 % divisor))
            {
                continue;
            }
            else if ((x2 % divisor) > s && s > i)
            {
                continue;
            }
            else
            {
                int a = i;
                sum++;
                while (used[(a + divisor - 1) % divisor] == true)
                {
                    a = (a + divisor - 1) % divisor;
                }
                table[(a + divisor - 1) % divisor] = x2;
                used[(a + divisor - 1) % divisor] = true;
                used[i] = false;
                s = i;
            }
        }
    }
    cout << sum << endl;
}




// template<class T>
// void hashTable<T>::erase(T& key)
// {
//     int index = key % size;
//     while (index < size)
//     {
//         if (index == 0 && table[index] == 1)
//         {
//             cout << "Not Found" << endl;
//             return;
//         }
//         if (table[index] == key && index == 0)
//         {
//             table[index] = 1;
//             int i = index;
//             int sum = 0;
//             int tem_index = index;
//             while (i < size)
//             {
//                 i = (i + 1) % divisor;
//                 if (i == key % divisor)
//                 {
//                     break;
//                 }
//                 if (table[i] == divisor && i != 0)
//                 {
//                     continue;
//                 }
//                 if (table[i] == 1 && i == 0)
//                 {
//                     continue;
//                 }
//                 if (table[i] != divisor && i != 0)
//                 {
//                     if (table[i] % divisor != i)
//                     {
//                         sum++;
//                         table[tem_index] = table[i];
//                         if (i == 0)
//                         {
//                             table[i] = 1;
//                         }
//                         if (i != 0)
//                         {
//                             table[i] = divisor;
//                         }
//                         tem_index = i;
//                     }
//                 }
//             }
//             cout << sum << endl;
//             return;
//         }
//         if (table[index] == key && index != 0)
//         {
//             table[index] = divisor;
//             int i = index;
//             int sum = 0;
//             int tem_index = index;
//             while (i < size)
//             {
//                 i = (i + 1) % divisor;
//                 if (i == key % divisor)
//                 {
//                     break;
//                 }
//                 if (table[i] == divisor && i != 0)
//                 {
//                     break;
//                 }
//                 if (table[i] == 1 && i == 0)
//                 {
//                     break;
//                 }
//                 if (table[i] != divisor && i != 0)
//                 {
//                     if (table[i] % divisor != i)
//                     {
//                         sum++;
//                         table[tem_index] = table[i];
//                         if (i == 0)
//                         {
//                             table[i] = 1;
//                         }
//                         if (i != 0)
//                         {
//                             table[i] = divisor;
//                         }
//                         tem_index = i;
//                     }
//                 }
//             }
//             cout << sum << endl;
//             return;
//         }
//         if (table[index] == divisor && index != 0)
//         {
//             cout << "Not Found" << endl;
//             return;
//         }
//         index++;
//         index = index % divisor;
//     }
//     cout << "Not Found" << endl;
// }
class Solution
{
public:
    void solve();
};

void Solution::solve()
{
    int D, m;
    cin >> D >> m;
    hashTable<int> table(D, D);
    for (int i = 0; i < m; i++)
    {
        int op, x;
        cin >> op >> x;
        if (op == 0)
        {
            table.insert(x);
            // table.display();
        }
        else if (op == 1)
        {
            table.find(x);
            // table.display();
        }
        else if (op == 2)
        {
            table.erase(x);
            // table.display();
        }
    }
}

int main()
{
    Solution solution;
    solution.solve();
    return 0;
}
