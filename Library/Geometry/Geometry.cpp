#include <bits/stdc++.h>

using namespace std;

using Double = long double;

const int MAXN = 2503;
long long salary[MAXN], prod[MAXN];
vector<pair<int, int>> adj[MAXN];
int sz[MAXN];
Double score[MAXN];
vector<Double> dp[MAXN];

void buildSize(int u) {
  sz[u] = 1;
  for (auto &p : adj[u]) {
    int v = p.second;
    buildSize(v);
    p.first = sz[v];
    sz[u] += p.first;
  }
  sort(adj[u].rbegin(), adj[u].rend());
}

void dfs(int u) {
  for (auto &p : adj[u]) {
    int v = p.second;
    dfs(v);
  }
  dp[u].resize(sz[u] + 2, -1e30);
  dp[u][0] = 0;
  dp[u][1] = score[u];
  for (auto child : adj[u]) {
    auto nxt = dp[u];
    for (int j = 0; j <= child.first; ++j) {
      for (int k = 1; dp[u][k] > -1e30; ++k) {
        nxt[j + k] = max(nxt[j + k], dp[u][k] + dp[child.second][j]);
      }
    }
    dp[u] = nxt;
  }
  //    cout << "u "  << u << endl;
  //    for (int i = 0; i <= dp[u].size(); ++i) {
  //        cout << dp[u][i] << ' ';
  //
  //    }
  //    cout << endl;
}

void pre(int n, double x) {
  for (int i = 0; i <= n; ++i) {
    score[i] = prod[i] - x * salary[i];
    dp[i].clear();
  }
}

bool can(int n, int k, double x) {
  pre(n, x);
  dfs(0);
  return dp[0][k + 1] >= 1e-9;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0), cout.precision(3),
      cout << fixed;

  int k, n;
  cin >> k >> n;
  for (int i = 1; i <= n; ++i) {
    int par;
    cin >> salary[i] >> prod[i] >> par;
    adj[par].emplace_back(0, i);
  }
  buildSize(0);
  //    cout << can(n, k, 0.001) << endl;
  //    return 0;

  double l = 0, r = 1e30;
  for (int i = 0; i < 100; ++i) {
    double mid = (l + r) / 2;
    if (can(n, k, mid))
      l = mid;
    else
      r = mid;
  }

  cout << l << '\n';
}