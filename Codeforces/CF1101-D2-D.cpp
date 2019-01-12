#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;
// Playing around
const int N = 2e5 + 10;
int n, ans, ar[N], par[N], mark[N];
vector<int> adj[N];
vector<int> st[N];
gp_hash_table<int, int> down[N], up[N];

void solve(int indx) {
  for (int i = 1; i * i <= ar[indx]; i++)
    if (ar[indx] % i == 0) {
      if (i > 1 && !mark[i]) st[indx].push_back(i);
      if (ar[indx] / i > 1 && i * i != ar[indx] && !mark[ar[indx] / i])
        st[indx].push_back(ar[indx] / i);
    }
}

void make_par(int v, int p = 0) {
  par[v] = p;
  for (int i : adj[v])
    if (i != p) make_par(i, v);
}

void make_down(int v) {
  for (int i : st[v])
    down[v][i] = max(down[v][i], 1);

  for (int i : adj[v]) {
    if (i == par[v]) continue;

    make_down(i);

    for (int j : st[v]) {
      if (down[i].find(j) != down[i].end())
        down[v][j] = max(down[v][j], down[i][j] + 1);
    }
  }
}

void make_up(int v) {
  for (int i : st[v])
    up[v][i] = max(up[v][i], 1);

  if (!v) {
    for (int i : adj[v])
      make_up(i);
    return;
  }

  for (int j : st[v]) {
    if (up[par[v]].find(j) != up[par[v]].end()) up[v][j] = up[par[v]][j] + 1;
    if (up[par[v]].find(j) == up[par[v]].end()) continue;

    for (int i : adj[par[v]]) {
      if (i == v || i == par[par[v]]) continue;

      if (down[i].find(j) != down[i].end())
        up[v][j] = max(up[v][j], down[i][j] + 2);
    }
  }

  for (int i : adj[v])
    if (i != par[v]) make_up(i);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);


  mark[1] = 1;
  for (int i = 2; i < N; i++)
    if (!mark[i]) for (int j = 2 * i; j < N; j += i)
      mark[j] = 1;

  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> ar[i], solve(i);
  for (int i = 1; i < n; i++) {
    int v, u;
    cin >> v >> u;
    v--;
    u--;
    adj[v].push_back(u);
    adj[u].push_back(v);
  }

  make_par(0);
  make_down(0);
  make_up(0);

  for (int i = 0; i < n; i++) {
    for (int j : st[i]) {
      ans = max(ans, down[i][j] + up[i][j] - 1);

      if ((adj[i].size() > 2) || (!i && adj[i].size())) {
        int mx1 = 0, mx2 = 0;
        for (int u : adj[i]) {
          if (u == par[i]) continue;

          if (down[u].find(j) != down[u].end()) {
            int tmp = down[u][j];
            if (tmp > mx1) {
              swap(mx1, mx2);
              mx1 = tmp;
            } else if (tmp > mx2) mx2 = tmp;
          }
        }

        ans = max(ans, mx1 + mx2 + 1);
      }
    }
  }

  cout << ans;
}
