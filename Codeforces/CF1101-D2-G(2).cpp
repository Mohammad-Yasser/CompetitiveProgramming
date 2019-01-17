#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;
typedef unsigned long long ULong;

// If you cannot solve or understand the solution, solve SPOJ XMAX first.
// Learn the xor gaussian elimination technique. You can see my comments here: 
// https://github.com/Mohammad-Yasser/CompetitiveProgramming/blob/master/SPOJ/XMAX.cpp

bool isSet(Long n, int b) {
  return (n >> b) & 1LL;
}

void printRow(int x) {
  cout << bitset<5>(x).to_string() << endl;
}

void printMat(const vector<Long>& mat) {
  for (auto& x : mat) {
    printRow(x);
  }
}

vector<Long> getRREF(const vector<Long>& mat) {
  vector<Long> res = mat;
  int rank = 0;
  for (int row = 0, col = 63; row < res.size() && col >= 0; --col) {
    for (int i = row; i < res.size(); ++i) {
      if (isSet(res[i], col)) {
        swap(res[row], res[i]);
        break;
      }
    }
    if (!isSet(res[row], col)) continue;
    ++rank;
    for (int i = 0; i < res.size(); ++i) {
      if (i == row) continue;
      if (isSet(res[i], col)) {
        res[i] ^= res[row];
      }
    }

    ++row;
  }

  return res;
}

int getRank(const vector<Long>& mat) {
  int res = 0;
  for (auto& x : mat) {
    res += (x != 0);
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

  int n;
  cin >> n;

  vector<Long> mat;
  int acc_xor = 0;
  while (n--) {
    int x;
    cin >> x;
    acc_xor ^= x;
    mat.push_back(acc_xor);
  }

  if (acc_xor == 0) {
    cout << -1;
    return 0;
  }

  cout << getRank(getRREF(mat)) << endl;

}
