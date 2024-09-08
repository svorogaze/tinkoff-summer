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

struct ST {
    int t[800000];

    ST() {
        for (auto& i : t) i = 0;
    }

    void add(int v, int vl, int vr, int l, int r, int x) {
        if (vl >= l && vr <= r) {
            t[v] += x;
            return;
        }
        int m = (vl + vr) / 2;
        if (l <= m) add(v * 2, vl, m, l, r, x);
        if (r > m) add(v * 2 + 1, m + 1, vr, l, r, x);
    }

    int get(int v, int vl, int vr, int ind) {
        if (vl == vr) {
            return t[v];
        }
        int m = (vl + vr) / 2;
        if (ind <= m) return t[v] + get(v * 2, vl, m, ind);
        return t[v] + get(v * 2 + 1, m + 1, vr, ind);
    }

};


int n;
struct eu {
    vector<vector<int>> g;
    vector<int> sz;
    vector<int> pss;
    int cc = 0;
    ST t;

    int bp[17][100000];
    int tin[100000];
    int tout[100000];
    int tim = 0;
    void dfs(int v, int p) {
        if (p == -1) {
            for (int i = 0; i < 17; ++i) {
                bp[i][v] = v;
            }
        } else {
            bp[0][v] = p;
            for (int i = 1; i < 17; ++i) {
                bp[i][v] = bp[i - 1][bp[i - 1][v]];
            }
        }
        sz[v] = 1;
        tin[v] = tim++;
        pss[v] = cc++;
        for (auto w : g[v]) {
            if (w != p) {
                dfs(w, v);
                sz[v] += sz[w];
            }
        }
        tout[v] = tim++;
    }

    eu(vector<vector<int>> cg) {
        g = cg;
        sz.resize(n);
        pss.resize(n);
        dfs(0, -1);
    }

    void add(int u, int v, int x) {
        if (sz[u] < sz[v]) swap(u, v);
        t.add(1, 0, n - 1, pss[v], pss[v] + sz[v] - 1, x);
    }

    bool isp(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int lca(int u, int v) {
        if (sz[v] > sz[u]) swap(u, v);
        int ve = v;
        for (int i = 16; i >= 0; --i) {
            if (!isp(bp[i][ve], u)) {
                ve = bp[i][ve];
            }
        }
        return bp[0][ve];
    }

    int get(int u, int v) {
        int l = lca(u, v);
        return t.get(1, 0, n - 1, pss[u]) + t.get(1, 0, n - 1, pss[v]) - 2 * t.get(1, 0, n - 1, pss[l]);
    }

};

struct edg {
    int u, v, w;
};

struct qur {
    int u, v, w, ind;
};

auto main() -> signed {
    fastio;
    int q;
    cin >> n >> q;
    map<int, vector<edg>> mp;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, t , w;
        cin >> u >> v >> t >> w;
        u--, v--;
        g[u].push_back(v), g[v].push_back(u);
        mp[t].push_back({u, v, w});
    }
    eu cost(g), cnt(g), sum(g);
    for (auto [t, ve] : mp) {
        for (auto e : ve) {
            cost.add(e.u, e.v, e.w);
        }
    }
    vector<int> ans(q);
    map<int, vector<qur>> mpq;
    for (int i = 0; i < q; ++i) {
        int t, w, u, v;
        cin >> t >> w >> u >> v;
        u--, v--;
        mpq[t].push_back({u, v, w, i});
    }
    for (auto [t, ve] : mpq) {
        for (auto e : mp[t]) {
            cnt.add(e.u, e.v, 1);
            sum.add(e.u, e.v, e.w);
        }
        for (auto qr : ve) {
            int res = cost.get(qr.u, qr.v) - sum.get(qr.u, qr.v) + cnt.get(qr.u, qr.v) * qr.w;
            ans[qr.ind] = res;
        }
        for (auto e : mp[t]) {
            cnt.add(e.u, e.v, -1);
            sum.add(e.u, e.v, -e.w);
        }
    }
    for (auto i : ans) {
        cout << i << '\n';
    }
}
