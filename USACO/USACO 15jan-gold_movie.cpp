#ifndef Local
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma comment(linker, "/STACK:1024000000,1024000000")
#endif

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;

const int N = 21;

int memo[1 << N];

inline bool getBit(int mask, int bit) {
  return (mask >> bit) & 1;
}

unordered_map<int, array<int, N>> nxt;

vector<int> shows[N];
int durations[N];

int n, l;

void buildNxt() {
  nxt[0];
  for (int i = 0; i < n; ++i) {
    for (int show : shows[i]) {
      nxt[show + durations[i]];
    }
  }
  for (auto& p : nxt) {
    for (int i = 0; i < n; ++i) {
      int show_ind = upper_bound(shows[i].begin(), shows[i].end(), p.first)
        - shows[i].begin() - 1;
      if (show_ind == -1) {
        p.second[i] = -1;
      } else {
        p.second[i] = shows[i][show_ind] + durations[i];
        if (p.second[i] <= p.first) {
          p.second[i] = -1;
        }
      }
    }
  }

}

int solve(int mask) {
  if (mask == 0) return 0;
  int& res = memo[mask];
  if (res != -1) return res;

  res = 0;

  for (int i = 0; i < n; ++i) {
    if (!getBit(mask, i)) continue;
    int tmp = solve(mask ^ (1 << i));
    tmp = nxt[tmp][i];
    if (tmp != -1) {
      res = max(res, tmp);
    }
  }

  return res;
}

void init() {
  memset(memo, -1, sizeof memo);
  buildNxt();
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cerr.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  freopen("movie.in", "r", stdin);
  freopen("movie.out", "w", stdout);

  cin >> n >> l;

  for (int i = 0; i < n; ++i) {
    cin >> durations[i];
    int c;
    cin >> c;
    shows[i].resize(c);
    for (int& show : shows[i]) {
      cin >> show;
    }
  }

  init();

  int res = -1;

  for (int mask = 0; mask < (1 << n); ++mask) {
    int tmp = solve(mask);
    if (tmp >= l) {
      if (res == -1) {
        res = popCnt(mask);
      } else {
        res = min(res, popCnt(mask));
      }
    }
  }

  cout << res << endl;

}

