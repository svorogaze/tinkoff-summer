#pragma GCC optimize("O3")
#include <bits/stdc++.h>
//#include <bits/extc++.h>
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

struct seg {
    int r;
    int cv;

    bool operator<(const seg& s) const { return r < s.r; }
    bool operator==(seg& s) { return r == s.r; };
};

template <typename T>
void clearr(T& x) {
    T x2;
    swap(x, x2);
}
int allc[10000000];
pair<int, int> p[10000000];
auto main() -> signed {
    fastio;
    int n, m;
    cin >> n >> m;
    vector<int> sl;
    vector<pair<int, int>> vp(n);
    for (auto& i : vp)
        cin >> i.first >> i.second, sl.push_back(i.first);
    vector<pair<int, int>> vp2(m);
    for (auto& i : vp2)
        cin >> i.first >> i.second;
    sort(all(sl));
    sl.erase(unique(all(sl)), sl.end());
    vector<int> fe(sl.size());
    for (auto& i : vp) {
        i.first = lower_bound(all(sl), i.first) - sl.begin();
        fe[i.first] = i.second;
    }
    for (auto& i : vp2) {
        i.first = lower_bound(all(sl), i.first) - sl.begin();
        i.second = upper_bound(all(sl), i.second) - sl.begin() - 1;
    }
    vector<vector<seg>> segs(sl.size() + 100);
    set<pair<int, int>> st;
    int ind = -1;
    for (auto& i : vp2) {
        ind++;
        if (i.first > i.second || i.first == sl.size())
            continue;
        if (st.find(i) == st.end()) {
            segs[i.first].push_back({i.second, ind});
        }
        st.insert(i);
    }
    vector<int> rem(sl.size() + 100);
    int cp = 0;
    int V = m;
    for (auto& i : allc) i = 0;
    for (int i = 0; i < sl.size(); ++i) {
        sort(all(segs[i]));
        segs[i].erase(unique(all(segs[i])), segs[i].end());
        cp ^= rem[i];
        if (segs[i].size() > 1) {
            for (int j = 1; j < segs[i].size(); ++j) {
                segs[segs[i][j - 1].r + 1].push_back({});
                seg& curs = segs[segs[i][j - 1].r + 1].back();
                curs.r = segs[i][j].r;
                if (V >= 10000000) exit(100);
                p[V] = {segs[i][j - 1].cv, segs[i][j].cv};
                curs.cv = V++;
            }
        }
        if (cp ^ fe[i]) {
            if (segs[i].size() == 0) {
                cout << -1;
                exit(0);
            }
            cp ^= 1;
            rem[segs[i][0].r + 1] ^= 1;
            allc[segs[i][0].cv] ^= 1;
        }
        clearr(segs[i]);
    }
    for (int i = V - 1; i >= m; --i) {
        allc[p[i].first] ^= allc[i];
        allc[p[i].second] ^= allc[i];
    }
    vector<int> ans;
    for (int i = 0; i < m; ++i) {
        if (allc[i]) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << '\n';
    for (auto i : ans) {
        cout << i + 1 << ' ';
    }
}
