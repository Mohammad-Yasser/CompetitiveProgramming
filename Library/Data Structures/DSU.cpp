const int N = 1;

struct DSU {
  int parent[N];

  void init() {
    for (int i = 0; i < N; ++i) {
      parent[i] = i;
    }
  }

  int getRoot(int x) {
    if (parent[x] == x) return x;
    return parent[x] = getRoot(parent[x]);
  }

  void join(int x, int y) {
    x = getRoot(x);
    y = getRoot(y);
    parent[x] = y;
  }
};

// DSU where each node has an opposite one
struct DSU {
  int parent[N];

  void init() {
    for (int i = 0; i < N; ++i) {
      parent[i] = i;
    }
  }

  int getSame(int x) { return 2 * x; }

  int getNot(int x) { return 2 * x + 1; }

  int getRoot(int x) {
    if (x == parent[x]) return x;
    return parent[x] = getRoot(parent[x]);
  }

  bool join(int a, int b, bool c) {
    int same_a = getRoot(getSame(a));
    int same_b = getRoot(getSame(b));

    int opp_a = getRoot(getNot(a));
    int opp_b = getRoot(getNot(b));

    if (c) {
      if (same_a == opp_b) return false;
      parent[same_a] = same_b;
      parent[opp_a] = opp_b;
    } else {
      if (same_a == same_b) return false;
      parent[same_a] = opp_b;
      parent[opp_a] = same_b;
    }
    return true;
  }

} dsu;
