#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;
typedef unsigned long long ULong;

// Tutorial here: http://codeforces.com/blog/entry/59696

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  int t;
  cin >> t;

  while (t--) {
    int mn = 1e7;
    Long sum = 0;
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      sum += x;
      mn = min(mn, x);
    }

    bool yav = false;
    if (n & 1) {
      if (sum & 1LL) {
        yav = true;
      }
    } else {
      if (sum % 2 == 1 || mn % 2 == 1) {
        yav = true;
      }
    }

    cout << (yav ? "Yalalov" : "Shin") << endl;
  }

}
