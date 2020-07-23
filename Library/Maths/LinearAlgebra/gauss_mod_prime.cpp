
int power(int base, int p, int MOD = MOD) {
  if (p == 0) return 1;
  int res = power(base, p / 2);
  res = 1LL * res * res % MOD;
  if (p & 1) {
    res = 1LL * res * base % MOD;
  }
  return res;
}

int modInverse(int x, int MOD = MOD) { return power(x, MOD - 2, MOD); }

using Row = vector<int>;
using Matrix = vector<Row>;

bool isZero(const Row& row) { return *max_element(all(row)) == 0; }

template <class T, class V>
T subMod(T x, V y, int mod) {
  if (x < y) return x - y + mod;
  return x - y;
}

Row subMultiple(const Row& a, const Row& b, int multiple, int mod) {
  Row res = a;
  for (int i = 0; i < sz(a); ++i) {
    res[i] = subMod(res[i], 1LL * b[i] * multiple % mod, mod);
  }
  return res;
}

Matrix getRREF(const Matrix& mat, int mod, int& rank) {
  if (mat.empty()) return mat;
  int n = sz(mat);     // no. of vectors.
  int m = sz(mat[0]);  // no. of columns.

  Matrix res = mat;
  rank = 0;
  for (int row = 0, col = 0; row < n && col < m; ++col) {
    for (int i = row; i < n; ++i) {
      if (res[i][col] != 0) {
        swap(res[row], res[i]);
        break;
      }
    }
    if (res[row][col] == 0) continue;
    ++rank;
    for (int i = row + 1; i < n; ++i) {
      if (res[i][col] == 0) continue;
      auto multiple = 1LL * res[i][col] * modInverse(res[row][col], mod) % mod;
      res[i] = subMultiple(res[i], res[row], multiple, mod);
    }
    ++row;
  }
  return res;
}

bool covered(const Matrix& rref, Row vctr, int mod) {
  int n = sz(rref);
  int m = sz(vctr);
  int curr_col = 0;
  for (int row = 0; row < n && !isZero(rref[row]); ++row) {
    int first_col = 0;
    while (rref[row][first_col] == 0) ++first_col;
    while (curr_col < m && vctr[curr_col] == 0) ++curr_col;
    if (first_col > curr_col) return false;
    if (first_col < curr_col) continue;
    int multiple =
        1LL * vctr[curr_col] * modInverse(rref[row][curr_col], mod) % mod;
    vctr = subMultiple(vctr, rref[row], multiple, mod);
  }
  return isZero(vctr);
}
