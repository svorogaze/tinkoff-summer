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
constexpr int mod = (int)(998244353);
struct mint {
    signed x = 0;

    mint(int _x) : x() { x = _x % mod; }

    mint() { x = 0; }

    mint operator*(const mint b) const { return ((long long)x * b.x) % mod; }

    mint operator+(const mint b) const {
        int r = x + b.x;
        if (r >= mod)
            r -= mod;
        return r;
    }

    mint operator-(const mint b) const {
        int r = x - b.x;
        if (r < 0)
            r += mod;
        return r;
    }

    mint& operator=(const mint b) {
        x = b.x;
        return *this;
    }

    mint& operator+=(const mint b) { return *this = *this + b; }

    mint& operator-=(const mint b) { return *this = *this - b; }

    mint& operator*=(const mint b) { return *this = *this * b; }

    [[nodiscard]] mint bp(int p) const {
        mint res(1);
        mint a = *this;
        while (p) {
            if (p % 2) {
                res *= a;
                p--;
            } else {
                a *= a;
                p /= 2;
            }
        }
        return res;
    }

    mint operator/(const mint b) const { return *this * b.bp(mod - 2); }

    mint& operator/=(const mint b) { return *this = *this / b; }

    bool operator==(const mint b) { return x == b.x; }
};

istream& operator>>(istream& in, mint& x) {
    in >> x.x;
    return in;
}

ostream& operator<<(ostream& out, mint& x) {
    out << x.x;
    return out;
}

auto main() -> signed {
    fastio;
    int n;
    cin >> n;
    vector<pair<int, int>> vp(n);
    for (auto& i : vp) cin >> i.first >> i.second, i.second += i.first;
    vector<int> dists;
    for (auto i : vp) dists.push_back(i.first), dists.push_back(i.second);
    dists.push_back(-INF);
    dists.push_back(INF);
    dists.push_back(INF + 1);
    sort(all(dists)), dists.erase(unique(all(dists)), dists.end());
    for (auto& i : vp)  i.first = lower_bound(all(dists), i.first) - dists.begin(), i.second = lower_bound(all(dists), i.second) - dists.begin();
    vector<int> gr(dists.size(), -1);
    for (auto& i : vp) gr[i.first] = i.second;
    vector<int> stack;
    for (int i = dists.size() - 1; i >= 0; --i) {
        if (gr[i] == -1) continue;
        if (!stack.empty()) {
            int le = -1, re = stack.size();
            while (re - le > 1) {
                int m = (le + re) / 2;
                if (stack[m] >= gr[i]) le = m;
                else re = m;
            }
            if (re != stack.size()) gr[i] = gr[stack[re]];
        }
        while (!stack.empty() && gr[stack.back()] <= gr[i]) {
            stack.pop_back();
        }
        stack.push_back(i);
    }
    mint res;
    vector<mint> dp(dists.size());
    dp[0] = 1;
    mint pref = 0;
    for (int i = 1; i < dists.size(); ++i) {
        pref += dp[i - 1];
        res += dp[i - 1];
        if (gr[i] != -1) {
            dp[gr[i] - 1] += pref;
        }
    }
    cout << res;
}
