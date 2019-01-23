#include <bits/stdc++.h>
using namespace std;

#define popCnt(x) (__builtin_popcountll(x))
#define getMSB(x) (__builtin_clzll(x))

typedef long long Long;
typedef unsigned long long ULong;

const int M = 41;
const int MX = 1 << 21;

Long enemy[M];
int e2[M];
int comp[MX];
bool invalid[MX];

int memo[MX];
int m;

int solve(int mask) {
  if (mask == 0) return 0;
  int& res = memo[mask];
  if (res != -1) return res;
  res = 0;
  for (int i = 0; i < 23; ++i) {
    if ((~mask >> i) & 1) continue;
    int fr = i + 20;
    res = max(res, 1 + solve(mask & ~e2[fr]));
  }
  return res;
}

void build() {
  for (int i = 0; i < m; ++i) {
    enemy[i] |= (1LL << i);
  }
  for (int mask = 0; mask < MX; ++mask) {
    Long c = (((1LL << m) - 1) ^ mask);
    for (int i = 0; i < 20; ++i) {
      if ((~mask >> i) & 1) continue;
      int fr = i;
      if (fr >= m) {
        invalid[mask] = true;
        break;
      }
      c &= (~enemy[fr]);
      if (((Long(mask)) & enemy[fr]) != (1LL << i)) {
        invalid[mask] = true;
        break;
      }
    }
    for (int i = 20; i < M; ++i) {
      if (i >= m) break;
      if ((c >> i) & 1LL) {
        comp[mask] |= (1 << (i - 20));
      }
    }
  }

  for (int i = 20; i < m; ++i) {
    for (int j = 20; j < m; ++j) {
      if ((enemy[i] >> j) & 1LL) {
        e2[i] |= (1 << (j - 20));
      }
    }
  }
}

unordered_map<string, int> cmprs;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  int n;
  cin >> n >> m;

  unordered_set<int> curr;
  while (n--) {
    int x;
    cin >> x;
    if (x == 1) {
      for (int x : curr) {
        for (int y : curr) {
          enemy[x] |= (1LL << y);
        }
      }
      curr.clear();
    } else {
      string s;
      cin >> s;
      if (cmprs.count(s) == 0) {
        cmprs[s] = (int) cmprs.size() - 1;
      }
      curr.insert(cmprs[s]);
    }
  }

  for (int x : curr) {
    for (int y : curr) {
      enemy[x] |= (1LL << y);
    }
  }

  build();
  memset(memo, -1, sizeof memo);

  int res = 0;
  for (int mask = 0; mask < (1 << 20); ++mask) {
    if (invalid[mask]) continue;
    res = max(res, popCnt(mask) + solve(comp[mask]));
  }

  cout << res;
}
