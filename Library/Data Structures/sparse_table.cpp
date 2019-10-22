// https://github.com/radoslav11/Coding-Library/blob/master/data_structures/sparse_table.cpp
struct SparseTable {
  int table[N][LOG];
  int lg2[N], n;

  SparseTable() {
    memset(table, 0, sizeof(table));
    memset(lg2, 0, sizeof(lg2));
    n = 0;
  }

  void init(vector<int> &a) {
    n = a.size();
    for (int i = 2; i < 2 * n; i++)
      lg2[i] = lg2[i >> 1] + 1;
    for (int i = 0; i < n; i++)
      table[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
      for (int i = 0; i < n; i++)
        table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
  }

  int query(int l, int r) {
    int k = lg2[r - l + 1];
    return min(table[l][k], table[r - (1 << k) + 1][k]);
  }
};
