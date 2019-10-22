struct LCAFinder {
  int lvl[N], anc[N][Lg];

  void dfs(int node, int parent) {
    for (int child : adj[node]) {
      if (child == parent) continue;
      anc[child][0] = node;
      lvl[child] = lvl[node] + 1;
      dfs(child, node);
    }
  }

  void buildLCA() {
    dfs(root, -1);
    for (int j = 1; j < Lg; ++j) {
      for (int i = 1; i <= n; ++i) {
        anc[i][j] = anc[anc[i][j - 1]][j - 1];
      }
    }
  }

  int LCA(int i, int j) { // returns node ID (LCA for i, j)
    int st = Lg;
    if (lvl[i] > lvl[j]) swap(i, j);
    int cur = lvl[j];
    for (; st >= 0; st--)
      if (cur - (1 << st) >= lvl[i]) cur -= (1 << st), j = anc[j][st];
    if (i == j) return i;
    cur = lvl[i];
    for (st = Lg; st >= 0; st--)
      if (anc[i][st] != anc[j][st]) cur -= (1 << st), i = anc[i][st], j =
        anc[j][st];
    return anc[i][0];
  }
} lca_finder;
