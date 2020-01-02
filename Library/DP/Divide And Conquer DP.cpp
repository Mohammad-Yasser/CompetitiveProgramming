//  C[a][d] + C[b][c] ≥ C[a][c] + C[b][d] where a < b < c < d.
//  A[i][j] ≤ A[i][j + 1]
void Solve(int curr_i, int k_left, int k_right, int j_left, int j_right,
  int level = 0) {
  int j_mid = (j_left + j_right) / 2;
  int& res = dp[curr_i][j_mid];
  res = OO;
  int best_k = k_left;

  for (int a = k_left; a < min(j_mid, k_right + 1); ++a) {
    int tmp = dp[curr_i - 1][a] + cost[a + 1][j_mid];
    if (tmp < res) {
      res = tmp;
      best_k = a;
    }
  }

  if (curr_i == 1) {
    res = cost[1][j_mid];
  }

  if (j_left < j_mid) {
    Solve(curr_i, k_left, best_k, j_left, j_mid - 1, level + 1);
  }
  if (j_mid < j_right) {
    Solve(curr_i, best_k, k_right, j_mid + 1, j_right, level + 1);
  }
}
