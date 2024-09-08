#include <bits/stdc++.h>
//#include <bits/extc++.h>
#pragma GCC optimize("O3")
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#include <ext/pb_ds/assoc_container.hpp>
//#define int long long
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

struct Node {
    vector<pair<int, int>> ans;
};

Node t[4000000];
int a[1000000];

Node merge(Node& a, Node& b) {
    Node res;
    int le = 0, re = 0;
    while (le < a.ans.size() && re < b.ans.size() && res.ans.size() < 20) {
        if (a.ans[le].first == b.ans[re].first) {
            res.ans.push_back({a.ans[le].first, a.ans[le].second + b.ans[re].second});
            le++, re++;
        } else if (a.ans[le].first > b.ans[re].first) {
            res.ans.push_back(a.ans[le]);
            le++;
        } else {
            res.ans.push_back(b.ans[re]);
            re++;
        }
    }
    while (le < a.ans.size() && res.ans.size() < 20) {
        res.ans.push_back(a.ans[le]);
        le++;
    }
    while (re < b.ans.size() && res.ans.size() < 20) {
        res.ans.push_back(b.ans[re]);
        re++;
    }
    return res;
}

void build(int v, int vl, int vr) {
    if (vl == vr) {
        t[v].ans.push_back({a[vl], 1});
        return;
    }
    int m = (vl + vr) / 2;
    build(v * 2, vl, m);
    build(v * 2 + 1, m + 1, vr);
    t[v] = merge(t[v * 2], t[v * 2 + 1]);
}

void update(int v, int vl, int vr, int ind) {
    if (vl == vr) {
        t[v].ans.clear();
        t[v].ans.push_back({a[vl], 1});
        return;
    }
    int m = (vl + vr) / 2;
    if (ind <= m) update(v * 2, vl, m, ind);
    else update(v * 2 + 1, m + 1, vr, ind);
    t[v] = merge(t[v * 2], t[v * 2 + 1]);
}
Node ans;

void get(int v, int vl, int vr, int l, int r) {
    if (vl >= l && vr <= r) {
        ans = merge(ans, t[v]);
        return;
    }
    int m = (vl + vr) / 2;
    if (l <= m) get(v * 2, vl, m, l, r);
    if (r > m) get(v * 2 + 1, m + 1, vr, l, r);
}

auto main() -> signed {
    fastio;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i];
    build(1, 0, n - 1);
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        if (x == 1) {
            int ind, val;
            cin >> ind >> val, ind--;
            a[ind] = val;
            update(1, 0, n - 1, ind);
        } else {
            ans.ans.clear();
            int l, r, k;
            cin >> l >> r >> k;
            l--, r--;
            get(1, 0, n - 1, l, r);
            if (ans.ans.size() < k) {
                cout << "0\n";
            } else {
                cout << ans.ans[k - 1].second << '\n';
            }
        }
    }
}
