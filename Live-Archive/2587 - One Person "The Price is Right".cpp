#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;

const int N = 31;

Long memo[N][N];

void build() {

  for (int g = 1; g < N; ++g) {
    for (int l = 0; l < N; ++l) {
      auto& res = memo[g][l];
      res = 1;
      if (g == 1) {
        continue;
      }
      if (l > 0) {
        res += memo[g - 1][l - 1];
      }
      res += memo[g - 1][l];
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  build();

  int cs = 1;

  int g, l;

  while (cin >> g >> l, g) {
    cout << "Case " << cs++ << ": " << memo[g][l] << endl;
  }

}
