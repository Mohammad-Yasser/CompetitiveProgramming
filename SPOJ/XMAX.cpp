#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;
typedef unsigned long long ULong;

// Gaussian elimination.
// I recommend watching this playlist to have good idea about linear algebra:
// https://www.youtube.com/playlist?list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab
// Then you can see this to learn Gaussian elimination:
// https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
// Then you can model each number as a vector, where xor operation is adding 2 vectors modulo 2.
// Then given a set of numbers, you want to get the basis vectors, and don't care for the redundant ones.
// which is done via gaussian elimination.
// If you understand gauss-jordan elimination, you'll easily see why the max xor is the xor of all the rows
// in the final matrix.


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

  while (n--) {
    Long x;
    cin >> x;
    mat.push_back(x);
  }

  auto rref = getRREF(mat);

  Long res = 0;
  for (auto& x : rref) {
    res ^= x;
  }

  cout << res << endl;

}
