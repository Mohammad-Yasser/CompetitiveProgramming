
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

// Source:
// https://github.com/tfg50/Competitive-Programming/blob/master/Biblioteca/Graph/SimpleEulerTourTree.cpp
template <const bool REPEAT = false>
struct SimpleEulerTourTree {
  void init(const std::vector<std::vector<int>>& edges, int root = 0) {
    a.clear();
    in = out = std::vector<int>(edges.size(), 0);
    dfs(root, root, edges, 0);
  }

  void dfs(int on, int par, const std::vector<std::vector<int>>& edges, int h) {
    in[on] = (int)a.size();
    a.emplace_back(h, on);
    for (auto to : edges[on]) {
      if (to == par) continue;
      dfs(to, on, edges, h + 1);
      if (REPEAT) a.emplace_back(h, on);
    }
    out[on] = (int)a.size();
  }

  std::vector<int> in, out;
  std::vector<std::pair<int, int>> a;
};

// Source:
// https://github.com/tfg50/Competitive-Programming/blob/master/Biblioteca/Graph/FastLCA.cpp
class FastLCA {
 public:
  void init(const std::vector<std::vector<int>>& edges, int root) {
    ett.init(edges, root);
    rmq.init(ett.a);
  }

  int lca(int u, int v) {
    if (ett.in[u] > ett.in[v]) std::swap(u, v);
    return rmq.qry(ett.in[u], ett.out[v]).second;
  }

 private:
  SimpleEulerTourTree<true> ett;
  FastRMQ<std::pair<int, int>> rmq;
};
