// https://github.com/radoslav11/Coding-Library/blob/master/data_structures/sparse_table.cpptemplate

template <typename T, class F = function<T(const T&, const T&)>>
struct SparseTable {
  int n;
  vector<vector<T>> sp;
  F func;

  SparseTable() {}

  void init(const vector<T>& a, const F& f) {
    func = f;
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    sp.resize(max_log);
    sp[0] = a;
    for (int j = 1; j < max_log; ++j) {
      sp[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); ++i) {
        sp[j][i] = func(sp[j - 1][i], sp[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T query(int l, int r) const {
    int lg = 32 - __builtin_clz(r - l + 1) - 1;
    return func(sp[lg][l], sp[lg][r - (1 << lg) + 1]);
  }

  // Not quite tested.
  // T query(int l, int r) const {
  //   int lg = 32 - __builtin_clz(r - l + 1) - 1;
  //   if ((1 << lg) == r - l + 1) {
  //     return sp[lg][l];
  //   }
  //   return func(sp[lg][l], query(l + (1 << lg), r));
  // }
};

SparseTable<int> sparse_table;
sparse_table.init(v, [](int x, int y) { return __gcd(x, y); });

///////////////////////////////////////////////////////////
// Source:
// https://github.com/tfg50/Competitive-Programming/blob/master/Biblioteca/Data%20Structures/SparseTable.cpp
template <class T>
struct Minimizer {
  T operator()(T a, T b) { return std::min(a, b); }
};

template <class T, class Merger = Minimizer<T>>
class SparseTable {
 public:
  void init(const std::vector<T>& a) {
    int e = 0;
    int n = a.size();
    while ((1 << e) / 2 < n) {
      e++;
    }
    table.assign(e, std::vector<T>(n));
    get.assign(n + 1, -1);
    for (int i = 0; i < n; i++) {
      table[0][i] = a[i];
      get[i + 1] = get[(i + 1) / 2] + 1;
    }
    for (int i = 0; i + 1 < e; i++) {
      for (int j = 0; j + (1 << i) < n; j++) {
        table[i + 1][j] = merge(table[i][j], table[i][j + (1 << i)]);
      }
    }
  }

  T qry(int l, int r) {
    int e = get[r - l];
    return merge(table[e][l], table[e][r - (1 << e)]);
  }

  int getPos(int x) {
    while (x >= (int)get.size()) get.push_back(get[(int)get.size() / 2] + 1);
    return get[x];
  }

 private:
  std::vector<std::vector<T>> table;
  std::vector<int> get;
  Merger merge;
};

// Source:
// https://github.com/tfg50/Competitive-Programming/blob/master/Biblioteca/Data%20Structures/FastRMQ.cpp
// O(N) preprocessing, O(1) query Range Minimum Query

template <class T>
class FastRMQ {
 public:
  void init(const std::vector<T>& a) {
    original = a;
    int n = (int)a.size();
    if (n == 0) return;
    e = 1;
    while ((1 << e) < n) e++;
    std::vector<T> groups;
    for (int i = 0; i < n; i++) {
      if (i % e == 0) {
        groups.push_back(a[i]);
      } else if (a[i] < groups.back()) {
        groups.back() = a[i];
      }
    }
    table.init(groups);
    mask.resize(n);
    for (int i = 0, curMask = 0; i < n; i++) {
      curMask = (curMask << 1) & ((1 << e) - 1);
      while (curMask) {
        int j = i - table.getPos(curMask & -curMask);
        if (a[i] < a[j]) {
          curMask ^= curMask & -curMask;
        } else {
          break;
        }
      }
      curMask |= 1;
      mask[i] = curMask;
    }
  }

  T qry(int l, int r) {
    // query in [l, r)
    if (r - l <= e) {
      return i_qry(r - 1, r - l);
    } else {
      T ans = std::min(i_qry(l + e - 1, e), i_qry(r - 1, e));
      if (l / e + 1 < r / e) {
        ans = std::min(ans, table.qry(l / e + 1, r / e));
      }
      return ans;
    }
  }

 private:
  int e;
  SparseTable<T> table;
  std::vector<T> original;
  std::vector<int> mask;

  T i_qry(int r, int size) {
    int curMask = mask[r] & ((1 << size) - 1);
    int pos = r - table.getPos(curMask);
    return original[pos];
  }
};

////////////////////////////////////////////////////////////////////////////

struct SparseTable {
  int table[N][LOG];
  int lg2[N], n;

  SparseTable() {
    memset(table, 0, sizeof(table));
    memset(lg2, 0, sizeof(lg2));
    n = 0;
  }

  void init(vector<int>& a) {
    n = a.size();
    for (int i = 2; i < n; i++) lg2[i] = lg2[i >> 1] + 1;
    for (int i = 0; i < n; i++) table[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
      for (int i = 0; i < n; i++) {
        if (i + (1 << (j - 1)) >= n) {
          table[i][j] = table[i][j - 1];
          continue;
        }
        table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
      }
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
    for (int i = 2; i < n; i++) lg2[i] = lg2[i >> 1] + 1;
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
