#include <cstdio>
#include <vector>
#include <string>
using namespace std;

int maskOf(const string& s) {
    int m = 0;
    for (char c : s)
        m |= 1 << (c - 'A');
    return m;
}

int scoreSingle(char a, char b) {
    return a == b ? 3 : 0;
}

int scoreMulti(const string& correct, const string& student) {
    int mc = maskOf(correct);
    int ms = maskOf(student);
    if ((ms & ~mc) != 0)
        return 0;
    if (ms == mc)
        return 5;
    if (ms > 0)
        return 2;
    return 0;
}

int solve(const vector<char>& key, const vector<char>& stu) {
    int n = (int)key.size();
    int m = (int)stu.size();
    vector<int> dp(m + 1, -1000000000);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        vector<int> ndp = dp;
        for (int j = 0; j < m; j++) {
            if (dp[j] < 0)
                continue;
            ndp[j + 1] = max(ndp[j + 1], dp[j] + scoreSingle(key[i], stu[j]));
        }
        dp.swap(ndp);
    }
    return dp[m];
}

int solve(const vector<string>& key, const vector<string>& stu) {
    int n = (int)key.size();
    int m = (int)stu.size();
    vector<int> dp(m + 1, -1000000000);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        vector<int> ndp = dp;
        for (int j = 0; j < m; j++) {
            if (dp[j] < 0)
                continue;
            ndp[j + 1] = max(ndp[j + 1], dp[j] + scoreMulti(key[i], stu[j]));
        }
        dp.swap(ndp);
    }
    return dp[m];
}

int main() {
    int N;
    scanf("%d", &N);
    vector<char> singleKey(N);
    for (int i = 0; i < N; i++)
        scanf(" %c", &singleKey[i]);
    int M;
    scanf("%d", &M);
    vector<string> multiKey(M);
    for (int i = 0; i < M; i++) {
        char buf[16];
        scanf("%s", buf);
        multiKey[i] = buf;
    }
    int K;
    scanf("%d", &K);
    while (K--) {
        int ni;
        scanf("%d", &ni);
        vector<char> singleStu(ni);
        for (int i = 0; i < ni; i++)
            scanf(" %c", &singleStu[i]);
        int mi;
        scanf("%d", &mi);
        vector<string> multiStu(mi);
        for (int i = 0; i < mi; i++) {
            char buf[16];
            scanf("%s", buf);
            multiStu[i] = buf;
        }
        int ans = solve(singleKey, singleStu) + solve(multiKey, multiStu);
        printf("%d\n", ans);
    }
    return 0;
}
