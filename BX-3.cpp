#include <bits/stdc++.h>
//#include <bits/extc++.h>
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#include <ext/pb_ds/assoc_container.hpp>
#define int long long
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, std::greater<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    indexed_set;
typedef tree<long long, null_type, greater_equal<>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_multiset;
#define fastio \
    std::cin.tie(0), std::cout.tie(0), std::ios_base::sync_with_stdio(false)
#define rep(a, b, c, d) for (int a = b; a < c; a += d)
#define INF ((1ll << 60))
#define all(x) (x).begin(), (x).end()
#define sq(x) ((x) * (x))
//#define sz(x) ((int)(x).size())
//#define pb push_back
//#define x first
//#define y second
#define ld long double
#define MAXN 10000
#define MAXN2 65000
constexpr ld eps = 1e-12;
#define mi long double
template <typename T>
T mbs(T x) {
    if (x < 0)
        return -x;
    return x;
}
struct vec {
    mi x, y;

    vec(ld x, ld y) : x(x), y(y) {}

    vec() {}

    mi operator*(vec b) { return x * b.x + y * b.y; }

    mi operator^(vec b) { return (mi)x * (mi)b.y - (mi)b.x * (mi)y; }

    vec operator+(vec b) { return {x + b.x, y + b.y}; }

    vec operator-(vec b) { return {x - b.x, y - b.y}; }

    vec operator*(mi k) { return {x * k, y * k}; }
};

long double getdist(vec a, vec b) {
    return sqrtl(sq(a.x - b.x) + sq(a.y - b.y));
}

istream& operator>>(istream& in, vec& x) {
    string xx, yy;
    in >> xx >> yy;
    x.x = stoi(xx);
    x.y = stoi(yy);
    return in;
}

struct Line {
    mi a, b, c;
};

Line get_line(vec a, vec b) {
    return {(b.y - a.y), (a.x - b.x),
            (-((b.y - a.y) * a.x + (a.x - b.x) * a.y))};
}

long double get_dist(Line a, vec b) {
    return mbs(a.a * b.x + a.b * b.y + a.c) / sqrtl(a.a * a.a + a.b * a.b);
}

struct segment {
    vec a, b;

    segment() = default;

    segment(vec a, vec b) : a(a), b(b) {}

    long double getd(vec c) {
        long double br = 1e17;
        br = min(getdist(a, c), getdist(b, c));
        if (((c - a) * (b - a) > 0 && (c - b) * (a - b) > 0) ||
            abs(getdist(a, b) - getdist(a, c) - getdist(c, b)) < eps) {
            Line l = get_line(a, b);
            br = min(br, get_dist(l, c));
        }
        return br;
    }
};

auto main() -> signed {
    vector<ld> dists;
    vector<ld> dists2;
    fastio;
    int n, l, k;
    cin >> n >> l >> k;
    vector<int> exs(k);
    for (auto& i : exs)
        cin >> i, i--;
    try {
        vector<vec> ps(n);
        for (auto& i : ps)
            cin >> i.x >> i.y;
        dists.resize(n);
        dists2.resize(n);
        for (int i = 0; i < n; ++i) {
            dists[i] = getdist(ps[i], ps[(i + 1) % n]);
        }
    } catch (...) {
        while (true);
    }
    for (auto& i : exs) {
        if (i < 0 || i >= dists2.size())while (true);
        dists2[i] = dists[i];
    }
    ld evil = 0;
    for (auto& i : dists2)
        evil += i;
    ld min_ans = evil;
    for (int i = 0; i < n; ++i) {
        dists.push_back(dists[i]);
        dists2.push_back(dists2[i]);
    }
    int re = 0;
    ld curp = 0;
    ld curp2 = 0;

    for (int i = 0; i < n; ++i) {
        if (re < i) {
            re = i;
            curp = 0;
            curp2 = 0;
        }
        while (re < dists.size() && curp + dists[re] <= l) {
            curp += dists[re];
            curp2 += dists2[re];
            re++;
        }
        ld cans = curp2;
        if (re < dists2.size() && dists2[re] > 0) {
            cans += l - curp;
        }
        min_ans = min(min_ans, evil - cans);
        curp -= dists[i];
        curp2 -= dists2[i];
    }
    min_ans = max(min_ans, (ld)0);
    cout << fixed << setprecision(10);
    cout << min_ans << '\n';

}
