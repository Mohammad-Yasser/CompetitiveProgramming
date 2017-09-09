#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;

const int N = 1e2;

typedef pair<int, int> Point;

bool valid(Point a, Point b, Point c) {
  if (c == b) return false;
  if (c.first == b.first && (a.second < b.second) == (b.second < c.second))
    return false;
  if (c.second == b.second && (a.first < b.first) == (b.first < c.first))
    return false;
  return true;
}
int n, m, l;
int get(Point a, Point b, Point c) {
  if (!valid(a, b, c)) return 0;
  int left = l - abs(c.first - a.first) - abs(c.second - a.second);

  for (int i = b.first - 1; i <= b.first + 1; ++i) {
    if (c.first != i) continue;
    int res = abs(c.second - b.second) - (i == b.first);
    if (left < res) return 0;
    return res + 1;
  }

  swap(b.first, b.second);
  swap(c.first, c.second);

  for (int i = b.first - 1; i <= b.first + 1; ++i) {
    if (c.first != i) continue;
    int res = abs(c.second - b.second) - (i == b.first);
    if (left < res) return 0;
    return res + 1;
  }

  return 0;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  cin >> n >> m >> l;

  pair<int, int> a, b;
  cin >> a.first >> a.second >> b.first >> b.second;

  int mx = 0;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      mx = max(mx, get(a, b, make_pair(i, j)));
    }
  }

  cout << mx << endl;
}
