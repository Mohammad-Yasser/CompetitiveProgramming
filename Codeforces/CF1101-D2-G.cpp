#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;
typedef unsigned long long ULong;

// Disclaimer: I've no idea why this works. https://codeforces.com/blog/entry/64438?#comment-483970
// The other intended solution,
// https://github.com/Mohammad-Yasser/CompetitiveProgramming/blob/master/Codeforces/CF1101-D2-G(2).cpp

const int N = 2e5 + 5;
int arr[N];
int n;

bool can(int x) {
  if (n == 0) return false;
  vector<int> piles(x, 0);
  for (int i = 0; i < n; ++i) {
    piles[i % x] ^= arr[i];
  }

  unordered_set<int> st;
  int sz1 = x / 2;
  int sz2 = x - sz1;
  for (int mask = 1; mask < (1 << sz1); ++mask) {
    int xr = 0;
    for (int i = 0; i < sz1; ++i) {
      if ((mask >> i) & 1) {
        xr ^= piles[i];
      }
    }
    if (xr == 0) return false;
    st.insert(xr);
  }

  for (int mask = 1; mask < (1 << sz2); ++mask) {
    int xr = 0;
    for (int i = 0; i < sz2; ++i) {
      if ((mask >> i) & 1) {
        xr ^= piles[sz1 + i];
      }
    }
    if (xr == 0) return 0;
    if (st.count(xr)) return false;
  }

  return true;

}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif
  srand(time(0));
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
    if (arr[i] == 0) {
      --i, --n;
    }
  }

  sort(arr, arr + n);

  for (int i = 32; i >= 1; --i) {
    sort(arr, arr + n);
    if (can(i)) {
      cout << i << endl;
      return 0;
    }
    for (int j = 0; j < 7; ++j) {
      random_shuffle(arr, arr + n);
      if (can(i)) {
        cout << i << endl;
        return 0;
      }
    }
  }

  cout << -1;

}
