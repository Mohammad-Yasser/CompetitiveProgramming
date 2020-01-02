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
    for (int i = 2; i < n; i++)
      lg2[i] = lg2[i >> 1] + 1;
    for (int i = 0; i < n; i++)
      table[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
      for (int i = 0; i < n; i++){
		   if (i + (1 << (j - 1)) >= n) {
          table[i][j] = table[i][j - 1];
          continue;
        }
        table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);}
  }

  int query(int l, int r) {
    int k = lg2[r - l + 1];
    return min(table[l][k], table[r - (1 << k) + 1][k]);
  }
};

// =================================================

struct Elem {
  int a, b;
  int p_prod;
  int cnt;
};
int n;
 
struct SparseTable {
  Elem table[N][LOG];
  int lg2[N];
 
  SparseTable() {
    memset(table, 0, sizeof(table));
    memset(lg2, 0, sizeof(lg2));
    n = 0;
  }
 
  Elem merge(const Elem& x, const Elem& y) {
    Elem res = x;
    res.a = (res.a - 1LL * x.p_prod * x.cnt % MOD + MOD) % MOD;
    res.b = (res.b + 1LL * x.p_prod * y.b) % MOD;
    res.a = (res.a + 1LL * x.cnt * x.p_prod) % MOD;
    res.a = (res.a + 1LL * y.a * x.p_prod) % MOD;
    res.p_prod = 1LL * x.p_prod * y.p_prod % MOD;
    res.cnt = (x.cnt + y.cnt) % MOD;
    return res;
  }
 
  void init() {
    for (int i = 2; i < n; i++)
      lg2[i] = lg2[i >> 1] + 1;
    for (int i = 0; i < n; i++) {
      table[i][0].cnt = 1;
      table[i][0].p_prod = 1LL * p[i] * INV100 % MOD;
      table[i][0].a = 1;
      table[i][0].b = 1LL * (100 - p[i]) * INV100 % MOD;
    }
 
    for (int j = 1; (1 << j) <= n; j++)
      for (int i = 0; i < n; i++) {
        if (i + (1 << (j - 1)) >= n) {
          table[i][j] = table[i][j - 1];
          continue;
        }
        table[i][j] = merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
      }
  }
 
  Elem query(int l, int r) {
    int k = lg2[r - l + 1];
    if ((1 << k) == r - l + 1) {
      return table[l][k];
    }
    return merge(table[l][k], query(l + (1 << k), r));
  }
} sp_table;
