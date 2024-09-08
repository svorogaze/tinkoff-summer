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
constexpr int mod = 998244353;
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

mint fact[1000001];
bool calcedf = false;

void calcf() {
    if (calcedf) return;
    calcedf = true;
    fact[0] = 1;
    for (int i = 1; i <= 1000000; ++i) {
        fact[i] = fact[i - 1] * i;
    }
}

mint cnk(int n, int k) {
    if (!calcedf) {
        calcf();
    }
    return fact[n] / (fact[k] * fact[n - k]);
}



istream& operator>>(istream& in, mint& x) {
    in >> x.x;
    return in;
}

ostream& operator<<(ostream& out, mint& x) {
    out << x.x;
    return out;
}

int dst(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}
vector<int> ans;
int n;
vector<pair<int, int>> vp;
bool check(int v) {
    if (find(all(ans), v) != ans.end()) return true;
    ans.push_back(v);
    map<int, vector<int>> mp;
    for (int i = 0; i < n; ++i) {
        if (v != i) {
            mp[dst(vp[i], vp[v])].push_back(i);
        }
    }

    for (auto i : ans) {
        if (i != v && mp.begin()->first != dst(vp[i], vp[v])) {
            return false;
        }
    }
    for (auto i : mp.begin()->second) {
        if (!check(i)) {
            return false;
        }
    }
    return true;
}
mint dp[101][101];
auto main() -> signed {
    fastio;
    cin >> n;
    vp.resize(n);
    for (auto& i : vp) cin >> i.first >> i.second;
    vector<vector<int>> mns;
    if (n == 1) {
        cout << 1;
        exit(0);
    }
    for (int i = 0; i < n; ++i) {
        ans.clear();
        if (check(i)) {
            sort(all(ans));
            mns.push_back(ans);
        } else {
            mns.push_back({i});
        }
    }
    sort(all(mns));
    mns.erase(unique(all(mns)), mns.end());
    dp[0][0] = 1;
    for (int i = 0; i < mns.size(); ++i) {
        for (int j = 0; j < n; ++j) {
            if (j + mns[i].size() <= n) {
                dp[i + 1][j + mns[i].size()] += dp[i][j];
            }
            if (mns[i].size() != 1) dp[i + 1][j + 1] += dp[i][j];
        }
    }
    mint res;
    calcf();
    for (int i = 1; i <= n; ++i) {
        res += dp[mns.size()][i] * (fact[n] / fact[n - i]);
    }
    cout << res;
}
