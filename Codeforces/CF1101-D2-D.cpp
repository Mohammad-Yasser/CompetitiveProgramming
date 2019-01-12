#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;
typedef unsigned long long ULong;

const int N = 2e5 + 5;

vector<int> prime_factors[N];

vector<int> getPrimeFactors(int x) {
  vector<int> res;
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      res.push_back(i);
    }
    while (x % i == 0) {
      x /= i;
    }
  }
  if (x != 1) {
    res.push_back(x);
  }
  return res;
}

void build() {
  for (int i = 2; i < N; ++i) {
    prime_factors[i] = getPrimeFactors(i);
  }
}

int res = 0;
vector<int> adj[N];
int val[N];

vector<pair<int, int>> dfs(int node, int par) {
  map<int, vector<int>> mp;

  for (auto& x : prime_factors[val[node]]) {
    mp[x].push_back(0);
    res = max(res, 1);
  }

  for (int v : adj[node]) {
    if (v == par) continue;
    auto tmp = dfs(v, node);
    for (auto& pr : tmp) {
      if (mp.count(pr.first)) {
        mp[pr.first].push_back(pr.second);
      }
    }
  }

  vector<pair<int, int>> vec;
  for (auto& pr : mp) {
    sort(pr.second.rbegin(), pr.second.rend());
    if (pr.second.size() > 1) {
      res = max(res, pr.second[0] + pr.second[1] + 1);
    }
    vec.emplace_back(pr.first, pr.second[0] + 1);
  }
  return vec;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  build();
  int n;
  cin >> n;

  for (int i = 1; i <= n; ++i) {
    cin >> val[i];
  }

  for (int i = 1; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  dfs(1, -1);
  cout << res << endl;
}
