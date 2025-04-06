#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <limits>
#include <map>
#include <cstdio>
using namespace std;
#define MOD 1000000007
const size_t BUFFER_SIZE = 1 << 25;
char buffer[BUFFER_SIZE];
int ptr = 0, len = 0;
//快速幂
long long powerMod(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

//快读
inline long long read()
{
    long long x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline long long readInt()
{
    int x = 0;
    while (buffer[ptr] < '0' || buffer[ptr] > '9')
    {
        ptr++;
    }

    while (buffer[ptr] >= '0' && buffer[ptr] <= '9')
    {
        x = x * 10 + (buffer[ptr++] - '0');        
    }
    return x;
}



//1-100质因数分解表计算器
vector<long long> prime_factors(long long n)
{
    vector<long long> factors;
    for (long long i = 2; i <= sqrt(n); i++)
    {
        while (n % i == 0)
        {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1)
    {
        factors.push_back(n);
    }
    return factors;
}

//1-100质因数分解表
//额外信息：1-100中的质数有：2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
std::vector<int> getPrimeFactors(int number) {
    std::vector<int> factors;
    switch(number) {
        case 2: factors = {2}; break;
        case 3: factors = {3}; break;
        case 4: factors = {2, 2}; break;
        case 5: factors = {5}; break;
        case 6: factors = {2, 3}; break;
        case 7: factors = {7}; break;
        case 8: factors = {2, 2, 2}; break;
        case 9: factors = {3, 3}; break;
        case 10: factors = {2, 5}; break;
        case 11: factors = {11}; break;
        case 12: factors = {2, 2, 3}; break;
        case 13: factors = {13}; break;
        case 14: factors = {2, 7}; break;
        case 15: factors = {3, 5}; break;
        case 16: factors = {2, 2, 2, 2}; break;
        case 17: factors = {17}; break;
        case 18: factors = {2, 3, 3}; break;
        case 19: factors = {19}; break;
        case 20: factors = {2, 2, 5}; break;
        case 21: factors = {3, 7}; break;
        case 22: factors = {2, 11}; break;
        case 23: factors = {23}; break;
        case 24: factors = {2, 2, 2, 3}; break;
        case 25: factors = {5, 5}; break;
        case 26: factors = {2, 13}; break;
        case 27: factors = {3, 3, 3}; break;
        case 28: factors = {2, 2, 7}; break;
        case 29: factors = {29}; break;
        case 30: factors = {2, 3, 5}; break;
        case 31: factors = {31}; break;
        case 32: factors = {2, 2, 2, 2, 2}; break;
        case 33: factors = {3, 11}; break;
        case 34: factors = {2, 17}; break;
        case 35: factors = {5, 7}; break;
        case 36: factors = {2, 2, 3, 3}; break;
        case 37: factors = {37}; break;
        case 38: factors = {2, 19}; break;
        case 39: factors = {3, 13}; break;
        case 40: factors = {2, 2, 2, 5}; break;
        case 41: factors = {41}; break;
        case 42: factors = {2, 3, 7}; break;
        case 43: factors = {43}; break;
        case 44: factors = {2, 2, 11}; break;
        case 45: factors = {3, 3, 5}; break;
        case 46: factors = {2, 23}; break;
        case 47: factors = {47}; break;
        case 48: factors = {2, 2, 2, 2, 3}; break;
        case 49: factors = {7, 7}; break;
        case 50: factors = {2, 5, 5}; break;
        case 51: factors = {3, 17}; break;
        case 52: factors = {2, 2, 13}; break;
        case 53: factors = {53}; break;
        case 54: factors = {2, 3, 3, 3}; break;
        case 55: factors = {5, 11}; break;
        case 56: factors = {2, 2, 2, 7}; break;
        case 57: factors = {3, 19}; break;
        case 58: factors = {2, 29}; break;
        case 59: factors = {59}; break;
        case 60: factors = {2, 2, 3, 5}; break;
        case 61: factors = {61}; break;
        case 62: factors = {2, 31}; break;
        case 63: factors = {3, 3, 7}; break;
        case 64: factors = {2, 2, 2, 2, 2, 2}; break;
        case 65: factors = {5, 13}; break;
        case 66: factors = {2, 3, 11}; break;
        case 67: factors = {67}; break;
        case 68: factors = {2, 2, 17}; break;
        case 69: factors = {3, 23}; break;
        case 70: factors = {2, 5, 7}; break;
        case 71: factors = {71}; break;
        case 72: factors = {2, 2, 2, 3, 3}; break;
        case 73: factors = {73}; break;
        case 74: factors = {2, 37}; break;
        case 75: factors = {3, 5, 5}; break;
        case 76: factors = {2, 2, 19}; break;
        case 77: factors = {7, 11}; break;
        case 78: factors = {2, 3, 13}; break;
        case 79: factors = {79}; break;
        case 80: factors = {2, 2, 2, 2, 5}; break;
        case 81: factors = {3, 3, 3, 3}; break;
        case 82: factors = {2, 41}; break;
        case 83: factors = {83}; break;
        case 84: factors = {2, 2, 3, 7}; break;
        case 85: factors = {5, 17}; break;
        case 86: factors = {2, 43}; break;
        case 87: factors = {3, 29}; break;
        case 88: factors = {2, 2, 2, 11}; break;
        case 89: factors = {89}; break;
        case 90: factors = {2, 3, 3, 5}; break;
        case 91: factors = {7, 13}; break;
        case 92: factors = {2, 2, 23}; break;
        case 93: factors = {3, 31}; break;
        case 94: factors = {2, 47}; break;
        case 95: factors = {5, 19}; break;
        case 96: factors = {2, 2, 2, 2, 2, 3}; break;
        case 97: factors = {97}; break;
        case 98: factors = {2, 7, 7}; break;
        case 99: factors = {3, 3, 11}; break;
        case 100: factors = {2, 2, 5, 5}; break;
        default: break;
    }
    return factors;
}

//额外信息：1-100中的质数有：2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
//额外信息：(a x b)%c = (a % c) * (b % c) % c

    struct node
    {
        map<int, long long> cnt;
        node()
        {
            cnt.insert(pair<int, long long>(2, 0));
            cnt.insert(pair<int, long long>(3, 0));
            cnt.insert(pair<int, long long>(5, 0));
            cnt.insert(pair<int, long long>(7, 0));
            cnt.insert(pair<int, long long>(11, 0));
            cnt.insert(pair<int, long long>(13, 0));
            cnt.insert(pair<int, long long>(17, 0));
            cnt.insert(pair<int, long long>(19, 0));
            cnt.insert(pair<int, long long>(23, 0));
            cnt.insert(pair<int, long long>(29, 0));
            cnt.insert(pair<int, long long>(31, 0));
            cnt.insert(pair<int, long long>(37, 0));
            cnt.insert(pair<int, long long>(41, 0));
            cnt.insert(pair<int, long long>(43, 0));
            cnt.insert(pair<int, long long>(47, 0));
            cnt.insert(pair<int, long long>(53, 0));
            cnt.insert(pair<int, long long>(59, 0));
            cnt.insert(pair<int, long long>(61, 0));
            cnt.insert(pair<int, long long>(67, 0));
            cnt.insert(pair<int, long long>(71, 0));
            cnt.insert(pair<int, long long>(73, 0));
            cnt.insert(pair<int, long long>(79, 0));
            cnt.insert(pair<int, long long>(83, 0));
            cnt.insert(pair<int, long long>(89, 0));
            cnt.insert(pair<int, long long>(97, 0));
        }
    };

void solve()
{
    // freopen("F:\\Homework\\程序设计思维与实践作业\\作业\\Week5\\2.in", "r", stdin);
    //freopen("a.out","w",stdout);
    vector<long long> prime_factors_between_1_and_100 = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
    long long n;
    cin >> n;

    vector<node> nodes(n);
    long long m;
    cin >> m;

    len = fread(buffer, 1, BUFFER_SIZE, stdin);

    for (long long i = 0; i < m; i++)
    {
        int l, r;
        int c, b;
        l = readInt();
        r = readInt();
        c = readInt();
        b = readInt();
        if (c == 1)
        {
            continue;
        }
        // vector<int>& factors = prime_factors_between_1_and_100_map[c];
        vector<int> factors = getPrimeFactors(c);
        for (auto& factor : factors)
        {
            nodes[l - 1].cnt[factor] += b;
            if (r < n)
            {
                nodes[r].cnt[factor] -= b;                
            }
        }
    }


    node ans = nodes[0];
    for (auto i : prime_factors_between_1_and_100)
    {
        long long cnt = 0;
        for (auto& j : nodes)
        {
            cnt += j.cnt[i];
            ans.cnt[i] = min(ans.cnt[i], cnt);
        }
    }
    
    // for (auto i : prime_factors_between_1_and_100)
    // {
    //     size_t min_cnt = numeric_limits<size_t>::max();
    //     for (auto j : nodes)
    //     {
    //         min_cnt = min(min_cnt, (size_t)j.cnt[i]);
    //     }
    //     ans.cnt[i] = min_cnt;
    // }
    // for (auto i : prime_factors_between_1_and_100)
    // {
    //     cout << i << '^' << ans.cnt[i] << '*';
    // }
    size_t final_ans = 1;
    for (auto i : prime_factors_between_1_and_100)
    {
        final_ans *= powerMod(i,ans.cnt[i],1000000007);
        final_ans %= 1000000007;
    }
    final_ans %= 1000000007;
    fflush(stdout);
    cout << final_ans << endl;
}

int main()
{
    solve();
    return 0;
}