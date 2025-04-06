/*2024数据结构-数据智能 实验2 排序算法 A 排序算法.cpp*/
#include<iostream>
using namespace std;

template<class T>
class Solution
{
private:
    void swap(T& a, T& b)
    {
        T c;
        c = a;
        a = b;
        b = c;
    }
public:
    //名次排序
    void rankSort();
    //及时终止的选择排序
    void chooseSort();
    //及时终止的冒泡排序
    void bubbleSort();
    //插入排序
    void insertSort();
};


template<class T>
void Solution<T>::rankSort()
{
    int n;
    cin >> n;
    T data[n];
    T result[n];
    for (int i = 0;i < n;i++)
    {
        cin >> data[i];
    }
    int rank[n];
    int cnt[n];
    for (int i = 0;i < n;i++)
    {
        rank[i] = 0;
        cnt[i] = 0;
    }

    for (int i = 0;i < n;i++)
    {
        for (int j = 0;j < n;j++)
        {
            if (data[i]>data[j])
            {
                rank[i]++;
            }
            if (data[i]==data[j])
            {
                cnt[i]++;
            }
            
        }
    }
    for (int i = 0;i < n;i++)
    {
        for (int j = 0; j < cnt[i]; j++)
        {
            result[rank[i] + j] = data[i];
        }
        
    }

    for (int i = 0;i < n;i++)
    {
        cout << result[i] << " ";
    }
}

template<class T>
void Solution<T>::chooseSort()
{
    int n;
    cin >> n;
    T data[n];
    for (int i = 0;i < n;i++)
    {
        cin >> data[i];
    }
    for (int i = 0; i < n;i++)
    {
        int min_index = i;
        int min_num = data[i];
        for (int j = i; j < n; j++)
        {
            if (data[j] < min_num)
            {
                min_index = j;
                min_num = data[j];
            }
        }
        swap(data[i], data[min_index]);
        bool mark = 1;
        for (int j = 0;j < n-1;j++)
        {
            if (data[j]>data[j+1])
            {
                mark = 0;
            }
        }
        if (mark)
        {
            break;
        }
        
    }
    for (int i = 0;i < n;i++)
    {
        cout << data[i] << " ";
    }
}

template<class T>
void Solution<T>::bubbleSort()
{
    int n;
    cin >> n;
    T data[n];
    for (int i = 0;i < n;i++)
    {
        cin >> data[i];
    }

    for (int i = 0;i < n;i++)
    {
        bool mark = 1;
        for (int j = 0;j < n - i - 1;j++)
        {
            if (data[j] > data[j + 1])
            {
                swap(data[j], data[j + 1]);
                mark = 0;
            }
        }
        if (mark)
        {
            break;
        }
    }

    for (int i = 0;i < n;i++)
    {
        cout << data[i] << " ";
    }
}

template<class T>
void Solution<T>::insertSort()
{
        int n;
    cin >> n;
    T data[n];
    for (int i = 0;i < n;i++)
    {
        cin >> data[i];
    }

    for (int i = 0; i < n; i++)
    {
        T temp = data[i];
        for (int j = i - 1;j >= 0;j--)
        {
            if (data[j]>temp)
            {
                data[j + 1] = data[j];
            }
            else
            {
                data[j + 1] = temp;
                break;
            }
            if (j == 0)
            {
                data[j] = temp;
                break;
            }
            
        }

    }


    
    for (int i = 0;i < n;i++)
    {
        cout << data[i] << " ";
    }
}

int main()
{
    Solution<int> test;
    // test.rankSort();
    // test.chooseSort();
    // test.bubbleSort();
    test.insertSort();
    return 0;
}