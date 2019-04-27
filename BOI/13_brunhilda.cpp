#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))

typedef long long Long;

const int N = 1e7 + 5;

vector<int> ks;

int cost[N];

int lcm = 1;

void build() {
  cost[0] = 0;

  for (int x = 1; x < lcm;) {
    int nxt_x = x;
    int nxt_k = -1;
    for (int k : ks) {
      if (x - nxt_x >= k) break;
      if (nxt_x != x && cost[nxt_x] <= cost[max(0, x - k + 1)]) break;
      if (x / k * k < nxt_x) {
        nxt_x = x / k * k;
        nxt_k = k;
      }
    }
    while (x < lcm && x != nxt_x + nxt_k) {
      cost[x] = 1 + cost[nxt_x];
      ++x;
    }
  }
}

int main() {
  srand(time(0));
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  memset(cost, -1, sizeof cost);

  int m, q;
  cin >> m >> q;

  ks.resize(m);
  for (int& k : ks) {
    cin >> k;
    lcm = min(1LL * N, 1LL * k * lcm);
  }

  reverse(ks.begin(), ks.end());
  build();
  while (q--) {
    int x;
    cin >> x;
    if (x < lcm) {
      cout << cost[x] << endl;
    } else {
      cout << "oo" << endl;
    }
  }

}
