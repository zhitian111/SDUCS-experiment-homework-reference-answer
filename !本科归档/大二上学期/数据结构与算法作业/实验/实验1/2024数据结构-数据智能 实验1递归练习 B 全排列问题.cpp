/*2024数据结构-数据智能 实验1递归练习 B 全排列问题.cpp*/
#include <iostream>
// #include <chrono>
using namespace std;
class Solution {
public:
    int ans = 0;
    void swap(int &a , int &b)
    {
	    int temp;
	    temp = a;
	    a = b;
	    b = temp;
    } 
    void SubSetValue(int a[], int n, int m)
    {
        if (m == n)
        {
            int sum = 0;
            for (int i = 0; i < n;i++)
            {
                sum = sum + ((i + 1) ^ a[i]);
            }
            ans = ans | sum;
        }
        if (m != n)
        {
            for (int i = m; i < n; i++)
            {
                swap(a[i],a[m]);
	 		    SubSetValue(a,n,m + 1);
	 		    swap(a[i] ,a[m]);
            }
            return;
        }
    }
    void solute()
    {
        int n;
        cin >> n;
        int a[n];
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        // auto start = chrono::high_resolution_clock::now();
        SubSetValue(a, n, 0);
        cout << ans;
        // auto stop = chrono::high_resolution_clock::now();
        // auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start).count();
        // cout << "Elapsed time: " << duration << " ms\n";
    }
};

int main()
{
    Solution ans;
    ans.solute();
    return 0;
}