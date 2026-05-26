#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

struct Cmp {
    bool operator()(pair<long long, int> a, pair<long long, int> b) const {
        if (a.first != b.first) return a.first > b.first;
        return a.second > b.second;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> t(n), s(n);
    for (int i = 0; i < n; ++i) cin >> t[i] >> s[i];
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, Cmp> pq;
    vector<long long> finish(n);
    long long cur_time = 0;
    long long cur_rem = 0;
    int cur_id = -1;
    int i = 0;
    const long long INF = (long long)4e18;
    while (i < n || cur_id != -1 || !pq.empty()) {
        if (cur_id == -1 && pq.empty()) {
            cur_time = t[i];
            while (i < n && t[i] == cur_time) {
                pq.push({s[i], i + 1});
                ++i;
            }
            auto top = pq.top();
            pq.pop();
            cur_rem = top.first;
            cur_id = top.second;
            continue;
        }
        long long next_arr = (i < n) ? t[i] : INF;
        long long fin_t = (cur_id != -1) ? cur_time + cur_rem : INF;
        if (fin_t < next_arr) {
            cur_time = fin_t;
            finish[cur_id - 1] = cur_time;
            cur_id = -1;
            if (!pq.empty()) {
                auto top = pq.top();
                pq.pop();
                cur_rem = top.first;
                cur_id = top.second;
            }
            continue;
        }
        if (fin_t == next_arr) {
            cur_time = fin_t;
            finish[cur_id - 1] = cur_time;
            cur_id = -1;
            while (i < n && t[i] == cur_time) {
                pq.push({s[i], i + 1});
                ++i;
            }
            if (!pq.empty()) {
                auto top = pq.top();
                pq.pop();
                cur_rem = top.first;
                cur_id = top.second;
            }
            continue;
        }
        cur_rem -= next_arr - cur_time;
        cur_time = next_arr;
        while (i < n && t[i] == cur_time) {
            long long ns = s[i];
            int nid = i + 1;
            ++i;
            if (ns < cur_rem || (ns == cur_rem && nid < cur_id)) {
                pq.push({cur_rem, cur_id});
                cur_rem = ns;
                cur_id = nid;
            } else {
                pq.push({ns, nid});
            }
        }
    }
    for (int k = 0; k < n; ++k) {
        if (k) cout << ' ';
        cout << finish[k];
    }
    cout << '\n';
    return 0;
}
