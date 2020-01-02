struct DSU {
  int parent[N];

  int getRoot(int x) {
    if (parent[x] == x) return x;
    return parent[x] = getRoot(x);
  }

  void join(int x , int y) {
    x = getRoot(x);
    y = getRoot(y);
    parent[x] = y;
  }
};

