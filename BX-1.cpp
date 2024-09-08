#pragma GCC optimize("O3")
#include <bits/stdc++.h>
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
//#include <bits/extc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//#define int long long
using namespace std;
using namespace __gnu_pbds;
using namespace std::chrono;
#define INF (1ll << 30)
#define fastio \
    std::cin.tie(0), std::cout.tie(0), std::ios_base::sync_with_stdio(false)
#define all(x) (x).begin(), (x).end()

int dp[3001][101][101][2];

auto main() -> signed {
    fastio;
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i : a) cin >> i;
    int m;
    cin >> m;
    vector<int> b(m);
    for (auto& i : b) cin >> i;
    sort(all(b));
    reverse(all(b));
    for (auto& i : dp) for (auto& j : i) for (auto& k : j) for (auto& l : k) l = -INF;
    dp[0][0][0][0] = 0;
    int mxr = -INF;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= j; ++k) {
                for (int flag = 0; flag < 2; ++flag) {
                    mxr = max(mxr, dp[i][j][k][flag]);
                    if (i < n) {
                        dp[i + 1][j][k][0] = max(dp[i + 1][j][k][0], dp[i][j][k][flag]);
                    }
                    if (j < m) {
                        dp[i][j + 1][k][0] = max(dp[i][j + 1][k][0], dp[i][j][k][flag]);
                    }
                    if (flag == 0) {
                        if (i < n) {
                            dp[i + 1][j][k][1] = max(dp[i + 1][j][k][1], dp[i][j][k][flag] + a[i]);
                        }
                        if (j < m) {
                            dp[i][j + 1][k + 1][1] = max(dp[i][j + 1][k + 1][1], dp[i][j][k][flag] + b[k]);
                        }
                    }
                }
            }
        }
    }
    cout << mxr;
}
