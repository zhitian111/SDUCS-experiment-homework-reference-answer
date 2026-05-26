#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

struct Pt {
    double x, y;
};

struct Circle {
    double x, y, r2;
};

static const double SQRT3 = sqrt(3.0);
static const Pt HEX_V[6] = {
    {0.0, 1.0},
    {SQRT3 / 2, 0.5},
    {SQRT3 / 2, -0.5},
    {0.0, -1.0},
    {-SQRT3 / 2, -0.5},
    {-SQRT3 / 2, 0.5},
};
static const double DLX = -SQRT3 / 2;
static const double DLY = -1.5;
static const double DRX = SQRT3 / 2;
static const double DRY = -1.5;

static bool inside(const Circle &c, const Pt &p) {
    double dx = p.x - c.x, dy = p.y - c.y;
    return dx * dx + dy * dy <= c.r2 + 1e-7;
}

static Circle circle_diameter(const Pt &a, const Pt &b) {
    Circle c;
    c.x = (a.x + b.x) * 0.5;
    c.y = (a.y + b.y) * 0.5;
    double dx = a.x - b.x, dy = a.y - b.y;
    c.r2 = (dx * dx + dy * dy) * 0.25;
    return c;
}

static bool circle_three(const Pt &a, const Pt &b, const Pt &c, Circle &out) {
    double ax = a.x, ay = a.y, bx = b.x, by = b.y, cx = c.x, cy = c.y;
    double d = 2.0 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
    if (fabs(d) < 1e-12)
        return false;
    double a2 = ax * ax + ay * ay, b2 = bx * bx + by * by, c2 = cx * cx + cy * cy;
    out.x = (a2 * (by - cy) + b2 * (cy - ay) + c2 * (ay - by)) / d;
    out.y = (a2 * (cx - bx) + b2 * (ax - cx) + c2 * (bx - ax)) / d;
    double dx = out.x - ax, dy = out.y - ay;
    out.r2 = dx * dx + dy * dy;
    return true;
}

// 边界点集 B 确定的最小圆（|B|<=3）
static Circle circle_from_boundary(const vector<Pt> &B) {
    if (B.empty())
        return {0.0, 0.0, 0.0};
    if (B.size() == 1)
        return {B[0].x, B[0].y, 0.0};
    if (B.size() == 2)
        return circle_diameter(B[0], B[1]);
    Circle c;
    circle_three(B[0], B[1], B[2], c);
    return c;
}

// Welzl：期望 O(m)，比赛里常见「最小圆」模板，比枚举 O(m^4) 更短且稳
static Circle welzl(vector<Pt> &p, int n, vector<Pt> &B) {
    if (n == 0 || B.size() == 3)
        return circle_from_boundary(B);
    Circle c = welzl(p, n - 1, B);
    if (inside(c, p[n - 1]))
        return c;
    B.push_back(p[n - 1]);
    c = welzl(p, n - 1, B);
    B.pop_back();
    return c;
}

static double smallest_enclosing_r2(vector<Pt> p) {
    unsigned seed = (unsigned)chrono::steady_clock::now().time_since_epoch().count();
    shuffle(p.begin(), p.end(), default_random_engine(seed));
    vector<Pt> B;
    return welzl(p, (int)p.size(), B).r2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> L(n + 1), R(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> L[i] >> R[i];

    vector<Pt> center(n + 1);
    function<void(int, double, double)> dfs = [&](int u, double cx, double cy) {
        center[u] = {cx, cy};
        if (L[u] != -1)
            dfs(L[u], cx + DLX, cy + DLY);
        if (R[u] != -1)
            dfs(R[u], cx + DRX, cy + DRY);
    };
    dfs(1, 0.0, 0.0);

    vector<Pt> pts;
    pts.reserve((size_t)n * 6);
    for (int u = 1; u <= n; ++u) {
        for (int v = 0; v < 6; ++v) {
            pts.push_back({center[u].x + HEX_V[v].x, center[u].y + HEX_V[v].y});
        }
    }

    double ans = smallest_enclosing_r2(pts);
    cout.setf(ios::fixed);
    cout << setprecision(4) << ans << '\n';
    return 0;
}
