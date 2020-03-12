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

  void join(int x , int y) {
    x = getRoot(x);
    y = getRoot(y);
    parent[x] = y;
  }
};

