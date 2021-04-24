//  C[a][d] + C[b][c] ≥ C[a][c] + C[b][d] where a < b < c < d.
//  A[i][j] ≤ A[i][j + 1]
void Solve(int curr_i, int k_left, int k_right, int j_left, int j_right) {
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
    Solve(curr_i, k_left, best_k, j_left, j_mid - 1);
  }
  if (j_mid < j_right) {
    Solve(curr_i, best_k, k_right, j_mid + 1, j_right);
  }
}

//  ==========================================  
void solve(bool curr_row, int curr_l, int curr_r, int prev_l, int prev_r) {
  bool prev_row = !curr_row;
  int mid = (curr_l + curr_r) / 2;
  Long& res = dp[curr_row][mid];
  res = LLONG_MAX;
  int a_mid = prev_l;
  for (int i = prev_l; i <= min(mid, prev_r); ++i) {
    if (dp[prev_row][i] == -1) continue;
    Long tmp = (mid - i) * cat_time[mid] + dp[prev_row][i];
    if (tmp < res) {
      res = tmp;
      a_mid = i;
    }
  }
  if (curr_l < mid) {
    solve(curr_row, curr_l, mid - 1, prev_l, a_mid);
  }
  if (mid < curr_r) {
    solve(curr_row, mid + 1, curr_r, a_mid, prev_r);
  }
}
