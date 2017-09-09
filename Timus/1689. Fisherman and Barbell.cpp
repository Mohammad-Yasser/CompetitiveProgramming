#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;

const int N = 1e6 + 5;

int cnt[N];
int g, w, b, p;

int get(int beg, int end) {
  if (end <= beg) return 0;

  int res = cnt[end - 1];
  if (beg >= 0) {
    res -= cnt[beg];
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  cin >> g >> w >> b >> p;
  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    ++cnt[x];
  }

  for (int i = 1; i < N; ++i) {
    cnt[i] += cnt[i - 1];
  }

  int mn = N;
  int best = 0;

  for (int i = 0; i + b <= g; ++i) {
    int res = get(i - w, i + p) + get(i + b - p - w, i + b);
    res -= get(i + b - p - w, i + p);

    if (res < mn) {
      mn = res;
      best = i;
    }
  }

  cout << best;

}
