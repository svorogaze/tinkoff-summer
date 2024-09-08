#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define int long long
typedef tree<int, null_type, std::less<>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
#define fastio std::cin.tie(0), std::cout.tie(0), std::ios_base::sync_with_stdio(false)
#define rep(a, b, c, d) for (int a = b; a < c; a += d)
#define INF ((1ll << 62) - 1)
#define all(x) x.begin(), x.end()
#define sz(x) x.size()
#define pb push_back

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> graph_rev;
bool visited[200000];
int ans[200000];
std::vector<int> topsort;
int scc = 1;

void dfs(int v) {
    visited[v] = true;
    for (auto u : graph[v]) {
        if (!visited[u]) dfs(u);
    }
    topsort.pb(v);
}

void SCC(int v) {
    visited[v] = true;
    ans[v] = scc;
    for (auto u : graph_rev[v]) {
        if (!visited[u]) SCC(u);
    }
}
vector<vector<int>> ng;
vector<int> newcost;



signed main() {
    fastio;
    int n, m;
    std::cin >> n >> m;
    vector<int> A(n);
    for (auto& i : A) cin >> i;
    graph.resize(n, {});
    graph_rev.resize(n, {});
    int a, b;
    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b;
        graph[a - 1].pb(b - 1);
        graph_rev[b - 1].pb(a - 1);
    }
    for (int i = 0; i < n; ++i) visited[i] = false, ans[i] = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    std::reverse(all(topsort));
    for (int i = 0; i < n; ++i) visited[i] = false;
    for (auto i : topsort) {
        if (!visited[i]) SCC(i), scc++;
    }
    newcost.resize(scc - 1);
    ng.resize(scc - 1);
    for (int i = 0; i < n; ++i) {
        newcost[ans[i] - 1] += A[i];
        for (auto w : graph[i]) {
            ng[ans[i] - 1].push_back(ans[w] - 1);
        }
    }
    vector<int> dp(n);
    for (int i = 0; i < scc - 1; ++i) {
        dp[i] += newcost[i];
        for (auto w : ng[i]) {
            dp[w] = max(dp[w], dp[i]);
        }
    }
    cout << *max_element(all(dp));
}
