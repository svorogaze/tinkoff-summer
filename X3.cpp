#include <bits/stdc++.h>
//#include <bits/extc++.h>
#pragma GCC optimize("O3")
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

vector<int> z_func(vector<int> a, vector<int> b) {
    int os = b.size() + 1;
    b.push_back(-1);
    for (auto i : a) b.push_back(i);
    int n = (int) b.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && b[z[i]] == b[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    z.erase(z.begin(), z.begin() + os);
    return z;
}

auto main() -> signed {
    fastio;
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i : a) cin >> i;
    vector<int> b(n);
    for (auto& i : b) cin >> i;
    if (n == 1) {
        cout << "1\n";
        cout << "0 " << (a[0] ^ b[0]);
        exit(0);
    }
    for (int i = 0; i < n - 1; ++i) {
        a.push_back(a[i]);
    }
    vector<int> cb(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cb[i] = (b[i] ^ b[i + 1]);
    }
    vector<int> ca(a.size() - 1);
    for (int i = 0; i < ca.size(); ++i) {
        ca[i] = (a[i] ^ a[i + 1]);
    }
    auto res = z_func(ca, cb);
    vector<pair<int, int>> vp;
    for (int i = 0; i < n; ++i) {
        if (res[i] == cb.size()) {
            vp.push_back({i, (a[i] ^ b[0])});
        }
    }
    sort(all(vp));
    for (auto i : vp) {
        cout << i.first << ' ' << i.second << '\n';
    }
}
