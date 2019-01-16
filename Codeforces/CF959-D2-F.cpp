#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;
typedef unsigned long long ULong;

// Hint: Solve the problem if the query was to check whether the desired number is 0 or not.

const int N = (1 << 20);
const int MOD = round(1e9 + 7);
int arr[N];
int first_possible[N];
int redundant[N];

int pw2[N];

void build() {
  pw2[0] = 1;
  for (int i = 1; i < N; ++i) {
    pw2[i] = 2LL * pw2[i - 1] % MOD;
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

  int n, q;
  cin >> n >> q;

  fill(first_possible, first_possible + N, N);
  first_possible[0] = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    redundant[i] = redundant[i - 1];
    if (first_possible[arr[i]] != N) {
      ++redundant[i];
      continue;
    }
    for (int j = 0; j < N; ++j) {
      if (first_possible[j] != N) continue;
      if (first_possible[j ^ arr[i]] != N) {
        first_possible[j] = i;
      }
    }
  }

  while (q--) {
    int l, x;
    cin >> l >> x;
    if (first_possible[x] > l) {
      cout << 0 << endl;
      continue;
    }
    cout << pw2[redundant[l]] << endl;
  }

}
