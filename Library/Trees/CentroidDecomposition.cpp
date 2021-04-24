// My modification of Anany's
struct Edge {
  int to, weight;
  Edge(int to = 0, int weight = 0) : to(to), weight(weight) {}
};
struct Tree {
  vector<vector<Edge>> adj;
  Tree(int n) : adj(n + 1) {}

  inline void addEdge(int u, int v, int w = 1) {
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  int size() const { return sz(adj); }
};

// ancestors[] edition
struct CentroidDecomposition {
  Tree tree;
  int n;
  vector<int> sz;
  vector<bool> vis;

  struct AncestorInfo {
    int ancestor;
    Long dist;
    AncestorInfo(int anc, Long dist) : ancestor(anc), dist(dist) {}
  };
  vector<vector<AncestorInfo>> ancestors;

  CentroidDecomposition(const Tree& tree) : tree(tree) {
    n = tree.size();
    sz = vector<int>(n);
    ancestors.resize(n);
    vis.resize(n);
    ConstructTree(1);
  }

  void dfsSize(int u, int p) {
    sz[u] = 1;
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v]) {
        dfsSize(v, u);
        sz[u] += sz[v];
      }
    }
  }

  void dfsAncestor(int u, int p, int ancestor, Long d) {
    ancestors[u].emplace_back(ancestor, d);
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v]) {
        dfsAncestor(v, u, ancestor, d + edge.weight);
      }
    }
  }

  int getCentroid(int u, int p, int max_size) {
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v] && sz[v] > max_size)
        return getCentroid(v, u, max_size);
    }
    return u;
  }

  void ConstructTree(int u) {
    dfsSize(u, u);
    int subtree_size = sz[u];
    int centroid = getCentroid(u, u, subtree_size / 2);
    line_container[centroid].lines.reserve(subtree_size);
    dfsAncestor(centroid, centroid, centroid, 0);
    vis[centroid] = 1;
    for (auto edge : tree.adj[centroid]) {
      int v = edge.to;
      if (!vis[v]) ConstructTree(v);
    }
  }

  void update(int u) {
    for (auto& anc : ancestors[u]) {
      // Update ancestor
      line_container[anc.ancestor].addLine(penalty[u], anc.dist);
    }
  }
  Long query(int u) {
    Long res = LLONG_MAX;
    for (auto& anc : ancestors[u]) {
      // Query ancestor
      res = min(res, line_container[anc.ancestor].query(penalty[u]) + anc.dist);
    }
    return res;
  }
};

// descendants[] edition

struct CentroidDecomposition {
  Tree tree;
  int n;
  vector<int> sz;
  vector<bool> vis;

  struct DescendantInfo {
    int descendant;
    Long dist;
    DescendantInfo(int descendant, Long dist)
        : descendant(descendant), dist(dist) {}
  };
  vector<vector<DescendantInfo>> descendants;

  CentroidDecomposition(const Tree& tree) : tree(tree) {
    n = tree.size();
    sz = vector<int>(n);
    descendants.resize(n);
    vis.resize(n);
    ConstructTree(1);
  }

  void dfsSize(int u, int p) {
    sz[u] = 1;
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v]) {
        dfsSize(v, u);
        sz[u] += sz[v];
      }
    }
  }

  void dfsAncestor(int u, int p, int ancestor, Long d) {
    descendants[ancestor].emplace_back(u, d);
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v]) {
        dfsAncestor(v, u, ancestor, d + edge.weight);
      }
    }
  }

  int getCentroid(int u, int p, int max_size) {
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v] && sz[v] > max_size)
        return getCentroid(v, u, max_size);
    }
    return u;
  }

  void ConstructTree(int u) {
    dfsSize(u, u);
    int subtree_size = sz[u];
    int centroid = getCentroid(u, u, subtree_size / 2);
    dfsAncestor(centroid, centroid, centroid, 0);
    vis[centroid] = 1;
    for (auto edge : tree.adj[centroid]) {
      int v = edge.to;
      if (!vis[v]) ConstructTree(v);
    }
  }

  void process(int centroid) {
    sort(all(descendants[centroid]),
         [&](const DescendantInfo& a, const DescendantInfo& b) {
           return penalty[a.descendant] < penalty[b.descendant];
         });
    static LineContainer line_container;
    line_container.lines.clear();
    // Build
    for (auto& desc : descendants[centroid]) {
      line_container.addLine(penalty[desc.descendant], desc.dist);
    }
    // Query
    for (auto& desc : descendants[centroid]) {
      res[desc.descendant] =
          min(res[desc.descendant],
              line_container.query(penalty[desc.descendant]) + desc.dist);
    }
  }
};

// process descendants on the fly edition

struct CentroidDecomposition {
  Tree tree;
  int n;
  vector<int> sz;
  vector<bool> vis;

  struct DescendantInfo {
    int descendant;
    Long dist;
    DescendantInfo(int descendant, Long dist)
        : descendant(descendant), dist(dist) {}
  };
  vector<DescendantInfo> curr_descendants;

  CentroidDecomposition(const Tree& tree) : tree(tree) {
    n = tree.size();
    sz = vector<int>(n);
    vis.resize(n);
    ConstructTree(1);
  }

  void dfsSize(int u, int p) {
    sz[u] = 1;
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v]) {
        dfsSize(v, u);
        sz[u] += sz[v];
      }
    }
  }

  void dfsAncestor(int u, int p, int ancestor, Long d) {
    curr_descendants.emplace_back(u, d);
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v]) {
        dfsAncestor(v, u, ancestor, d + edge.weight);
      }
    }
  }

  int getCentroid(int u, int p, int max_size) {
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v] && sz[v] > max_size)
        return getCentroid(v, u, max_size);
    }
    return u;
  }

  void ConstructTree(int u) {
    dfsSize(u, u);
    int subtree_size = sz[u];
    int centroid = getCentroid(u, u, subtree_size / 2);
    curr_descendants.clear();
    dfsAncestor(centroid, centroid, centroid, 0);
    process();
    vis[centroid] = 1;
    for (auto edge : tree.adj[centroid]) {
      int v = edge.to;
      if (!vis[v]) ConstructTree(v);
    }
  }

  void process() {
    sort(all(curr_descendants),
         [&](const DescendantInfo& a, const DescendantInfo& b) {
           return penalty[a.descendant] < penalty[b.descendant];
         });
    static LineContainer line_container;
    line_container.lines.clear();
    // Build
    for (auto& desc : curr_descendants) {
      line_container.addLine(penalty[desc.descendant], desc.dist);
    }
    // Query
    for (auto& desc : curr_descendants) {
      res[desc.descendant] =
          min(res[desc.descendant],
              line_container.query(penalty[desc.descendant]) + desc.dist);
    }
  }
};

// maintaining sorted subtree edition

struct CentroidDecomposition {
  Tree tree;
  int n;
  vector<int> sz, subtree_id;
  vector<Long> dist;
  vector<bool> vis;
  vector<vector<int>> sorted_subtree;

  CentroidDecomposition(const Tree& tree, const vector<int>& sorted_nodes)
      : tree(tree) {
    n = tree.size();
    sz.resize(n), vis.resize(n), dist.resize(n);
    subtree_id.resize(n), sorted_subtree.resize(n);
    sorted_subtree[1] = sorted_nodes;
    ConstructTree(1);
  }

  void dfsSize(int u, int p) {
    sz[u] = 1;
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v]) {
        dfsSize(v, u);
        sz[u] += sz[v];
      }
    }
  }

  void dfsAncestor(int u, int p, int st_id, Long d) {
    subtree_id[u] = st_id;
    dist[u] = d;
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v]) {
        dfsAncestor(v, u, (u == p) ? v : st_id, d + edge.weight);
      }
    }
  }

  int getCentroid(int u, int p, int max_size) {
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v] && sz[v] > max_size)
        return getCentroid(v, u, max_size);
    }
    return u;
  }

  void ConstructTree(int u) {
    dfsSize(u, u);
    int subtree_size = sz[u];
    int centroid = getCentroid(u, u, subtree_size / 2);
    sorted_subtree[centroid] = sorted_subtree[u];
    dfsAncestor(centroid, centroid, centroid, 0);
    vis[centroid] = 1;
    process(sorted_subtree[centroid]);
    for (auto edge : tree.adj[centroid]) {
      int v = edge.to;
      if (!vis[v]) {
        sorted_subtree[v].clear();
      }
    }

    for (int node : sorted_subtree[centroid]) {
      if (node == centroid) continue;
      sorted_subtree[subtree_id[node]].emplace_back(node);
    }
    for (auto edge : tree.adj[centroid]) {
      int v = edge.to;
      if (!vis[v]) ConstructTree(v);
    }
  }

  void process(const vector<int>& sorted_nodes) {
    static LineContainer line_container;
    line_container.lines.clear();
    // Build
    for (auto& node : sorted_nodes) {
      line_container.addLine(penalty[node], dist[node]);
    }
    // Query
    for (auto& node : sorted_nodes) {
      res[node] =
          min(res[node], line_container.query(penalty[node]) + dist[node]);
    }
  }
};

// ====================================

// Radoslav
const int MAXN = (1 << 20);

int n;
vector<int> adj[MAXN];

int tr_sz[MAXN], cnt_vers;
bool used[MAXN];

void pre_dfs(int u, int pr) {
  cnt_vers++;
  tr_sz[u] = 1;
  for (int v : adj[u])
    if (!used[v] && v != pr) {
      pre_dfs(v, u);
      tr_sz[u] += tr_sz[v];
    }
}

int centroid(int u, int pr) {
  for (int v : adj[u])
    if (!used[v] && v != pr && tr_sz[v] > cnt_vers / 2) return centroid(v, u);

  return u;
}

int link[MAXN];

void decompose(int u, int pr = -1) {
  cnt_vers = 0;
  pre_dfs(u, u);
  int cen = centroid(u, u);
  link[cen] = pr;

  used[cen] = true;
  for (int v : adj[cen])
    if (!used[v]) decompose(v, cen);
  used[cen] = false;
}
// ===============================

// Anany

struct CentDec {
  vector<vector<int>> adj;
  int n, nn;
  vector<int> sz, lvl, par, vis, d, ans;
  vector<vector<int>> tb;
  CentDec(vector<vector<int>> g) {
    n = g.size() - 1;
    adj = g;
    sz = par = lvl = vis = d = vector<int>(n + 1);
    tb = vector<vector<int>>(18, vector<int>(n + 1));
    ans.assign(n + 1, 1e9);
    pDFS(1, -1);
    ConstructTree(1, -1);
  }
  void pDFS(int u, int p) {
    for (int k = 1; k < 18; k++) tb[k][u] = tb[k - 1][tb[k - 1][u]];
    for (auto v : adj[u])
      if (v != p) {
        d[v] = d[u] + 1;
        tb[0][v] = u;
        pDFS(v, u);
      }
  }
  int getLCA(int u, int v) {
    if (d[u] > d[v]) swap(u, v);
    int k = d[v] - d[u];
    for (int i = 0; i < 17; i++)
      if (k >> i & 1) v = tb[i][v];
    if (u == v) return u;
    for (int i = 17; i >= 0; --i)
      if (tb[i][v] != tb[i][u]) {
        u = tb[i][u];
        v = tb[i][v];
      }
    return tb[0][u];
  }
  int getDist(int u, int v) { return d[u] + d[v] - 2 * d[getLCA(u, v)]; }
  int getSz(int u, int p) {
    sz[u] = 1;
    for (auto v : adj[u])
      if (v != p && !vis[v]) sz[u] += getSz(v, u);
    return sz[u];
  }

  int getCent(int u, int p) {
    for (auto v : adj[u])
      if (v != p && !vis[v])
        if (sz[v] > nn / 2) return getCent(v, u);
    return u;
  }

  void ConstructTree(int u, int p) {
    nn = getSz(u, u);
    int centroid = getCent(u, u);
    vis[centroid] = 1;
    if (p == -1)
      p = centroid;
    else
      lvl[centroid] = lvl[p] + 1;
    par[centroid] = (p == centroid ? -1 : p);
    for (auto v : adj[centroid])
      if (!vis[v]) ConstructTree(v, centroid);
  }

  void upd(int u) {
    int x = u;
    while (~x) {
      ans[x] = min(ans[x], getDist(u, x));
      x = par[x];
    }
  }
  int qry(int u) {
    int x = u;
    int ret = ans[x];
    while (~x) {
      ret = min(ret, getDist(u, x) + ans[x]);
      x = par[x];
    }
    return ret;
  }
};
