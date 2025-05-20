#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void __debug__(T x, string name)
{
    cerr << name << " = " << x << endl;
}
template<typename T> inline void __debug__(T* x, string name, size_t size)
{
    cerr << name << "[" << size << "] = ";
    for (size_t i = 0; i < size; i++)
    {
        cerr << x[i] << " ";
    }
    cerr << endl;
}
#define debug(x) __debug__(x, (#x));
#define adebug(x) __debug__(x, (#x), sizeof(x)/sizeof(x[0]));

unsigned int p_rand = 1;

int myrand()
{
    p_rand = p_rand * 1103515245 + 12345;
    return (unsigned int)(p_rand / 65536) % 100;
}

struct Task
{
    string name;
    long long duration;
    long long index;
};
bool operator<(const Task& a, const Task& b)
{
    return a.duration == b.duration? a.name < b.name : a.duration < b.duration;
}
bool operator>(const Task& a, const Task& b)
{
    return a.duration == b.duration? a.name < b.name : a.duration > b.duration;
}
struct Workshop
{
    string op;
    Task *now = nullptr;
    long long now_end = 0;

    deque<Task> tfq;
    priority_queue<Task, vector<Task>, greater<Task>> sfq;
    priority_queue<Task, vector<Task>, less<Task>> lfq;

    void add(const Task &task)
    {
        if (op == "TF")
        {
            tfq.push_back(task);
        }
        else if (op == "SF")
        {
            sfq.push(task);
        }
        else
        {
            lfq.push(task);
        }
    }

    bool has_job()
    {
        return op == "LF" ? !lfq.empty() : op == "TF" ? !tfq.empty() : !sfq.empty();
    }

    Task get_nxt()
    {
        Task nxt;
        if (op == "TF")
        {
            nxt = tfq.front();
            tfq.pop_front(); 
        }
        else if (op == "SF")
        {
            nxt = sfq.top();
            sfq.pop();
        }
        else
        {
            nxt = lfq.top();
            lfq.pop();
        }
        return nxt;
    }

    ~Workshop()
    {
        if (now)
        {
            delete now;            
        }
    }
};

struct Event
{
    long long end_time;
    long long index;
    string name;

    bool operator>(const Event &other) const
    {
        return end_time == other.end_time? index > other.index : end_time > other.end_time;
    }
};

void solve()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    unordered_map<string, Workshop> workshops;
    workshops.reserve(n); 
    for (long long i = 0; i < n; ++i)
    {
        string name, op;
        cin >> name >> op;
        workshops[name] = {op, nullptr, 0};
    }

    priority_queue<Event, vector<Event>, greater<Event>> events;
    vector<pair<long long, string>> output;
    output.reserve(m); 
    long long global_index = 0;

    for (long long i = 0; i < m; ++i)
    {
        long long t, d, k;
        string s;
        cin >> t >> s >> d >> k;

        vector<string> to_add(k);
        for (long long j = 0; j < k; ++j)
        {
            cin >> to_add[j];
        }

        string wss;
        long long prob = floor(100.0 / k);
        for (long long j = 0; j < k; ++j)
        {
            if (j == k - 1)
            {
                wss = to_add[j];
                break;
            }
            if (prob > myrand())
            {
                wss = to_add[j];
                break;
            }
        }

        Workshop &ws = workshops[wss];
        Task task{s, d, global_index++};

        while (!events.empty() && events.top().end_time <= t)
        {
            Event e = events.top();
            events.pop();

            Workshop &done = workshops[e.name];
            output.emplace_back(e.end_time, done.now->name);
            delete done.now;
            done.now = nullptr;

            if (done.has_job())
            {
                Task nxt = done.get_nxt();
                done.now = new Task(nxt);
                done.now_end = e.end_time + nxt.duration;
                events.push({done.now_end, nxt.index, e.name});
            }
        }

        if (ws.now == nullptr)
        {
            ws.now = new Task(task);
            ws.now_end = t + task.duration;
            events.push({ws.now_end, task.index, wss});
        }
        else
        {
            ws.add(task);
        }
    }

    while (!events.empty())
    {
        Event e = events.top();
        events.pop();

        Workshop &done = workshops[e.name];
        output.emplace_back(e.end_time, done.now->name);
        delete done.now;
        done.now = nullptr;

        if (done.has_job())
        {
            Task nxt = done.get_nxt();
            done.now = new Task(nxt);
            done.now_end = e.end_time + nxt.duration;
            events.push({done.now_end, nxt.index, e.name});
        }
    }

    for (const auto &p : output)
    {
        cout << p.first << " " << p.second << '\n';
    }
}

int main()
{
    solve();
    return 0;
}