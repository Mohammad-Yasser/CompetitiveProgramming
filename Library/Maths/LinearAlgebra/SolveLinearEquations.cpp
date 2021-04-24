// Source:
// https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/SolveLinear.h
/**
 * Author: Per Austrin, Simon Lindholm
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $A * x = b$. If there are multiple solutions, an
 * arbitrary one is returned. Returns rank, or -1 if no solutions. Data in $A$
 * and $b$ is lost. Time: O(n^2 m) Status: tested on kattis:equationsolver, and
 * bruteforce-tested mod 3 and 5 for n,m <= 3
 */

using vd = vector<double>;
const double eps = 1e-12;

int solveLinear(vector<vd>& A, vd& b, vd& x) {
  int n = sz(A), m = sz(x), rank = 0, br, bc;
  if (n) assert(sz(A[0]) == m);
  vi col(m);
  iota(all(col), 0);

  rep(i, 0, n) {
    double v, bv = 0;
    rep(r, i, n) rep(c, i, m) if ((v = fabs(A[r][c])) > bv) br = r, bc = c,
                                                            bv = v;
    if (bv <= eps) {
      rep(j, i, n) if (fabs(b[j]) > eps) return -1;
      break;
    }
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    rep(j, 0, n) swap(A[j][i], A[j][bc]);
    bv = 1 / A[i][i];
    rep(j, i + 1, n) {
      double fac = A[j][i] * bv;
      b[j] -= fac * b[i];
      rep(k, i + 1, m) A[j][k] -= fac * A[i][k];
    }
    rank++;
  }

  x.assign(m, 0);
  for (int i = rank; i--;) {
    b[i] /= A[i][i];
    x[col[i]] = b[i];
    rep(j, 0, i) b[j] -= A[j][i] * b[i];
  }
  return rank;  // (multiple solutions if rank < m)
}

// My modified version to work with integers under mod
// Tested through https://codeforces.com/contest/1464/submission/102283694
// For n = m = 512, runs in 233 ms on CF.
int solveLinear(vector<vi>& A, vi& b, vi& x) {
  int n = sz(A), m = sz(x), rank = 0, br, bc;
  if (n) assert(sz(A[0]) == m);
  vi col(m);
  iota(all(col), 0);

  rep(i, 0, n) {
    int v, bv = 0;
    rep(r, i, n) rep(c, i, m) if ((v = abs(A[r][c])) > bv) br = r, bc = c,
                                                           bv = v;
    if (bv == 0) {
      rep(j, i, n) if (abs(b[j]) > 0) return -1;
      break;
    }
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    rep(j, 0, n) swap(A[j][i], A[j][bc]);
    bv = modInverse(A[i][i]);
    rep(j, i + 1, n) {
      int fac = 1LL * A[j][i] * bv % MOD;
      b[j] = (b[j] - 1LL * fac * b[i]) % MOD;
      rep(k, i + 1, m) A[j][k] = (A[j][k] - 1LL * fac * A[i][k]) % MOD;
    }
    ++rank;
  }

  x.assign(m, 0);
  for (int i = rank; i--;) {
    b[i] = 1LL * b[i] * modInverse(A[i][i]) % MOD;
    x[col[i]] = b[i];
    if (x[col[i]] < 0) {
      x += MOD;
    }
    rep(j, 0, i) b[j] = (b[j] - 1LL * A[j][i] * b[i]) % MOD;
  }
  return rank;  // (multiple solutions if rank < m)
}