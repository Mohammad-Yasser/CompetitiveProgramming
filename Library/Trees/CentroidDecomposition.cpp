// My modification of Anany's

struct Edge {
  int to, weight;
  Edge(int to = 0, int weight = 0) : to(to), weight(weight) {}
};

struct Tree {
  vector<vector<Edge>> adj;
  int max_log;
  vector<vector<int>> sparse_table;
  vector<Long> dist;
  vector<int> depth;
  Tree(int n) : adj(n + 1), dist(n + 1), depth(n + 1) {
    max_log = 32 - __builtin_clz(n + 1);
    sparse_table.assign(max_log, vector<int>(n + 1));
  }
  void addEdge(int u, int v, int w = 1) {
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  int size() const { return sz(adj); }
  void pDFS(int u, int p) {
    for (int k = 1; k < max_log; ++k)
      sparse_table[k][u] = sparse_table[k - 1][sparse_table[k - 1][u]];
    for (auto& edge : adj[u]) {
      int v = edge.to;
      if (v != p) {
        dist[v] = dist[u] + edge.weight;
        depth[v] = depth[u] + 1;
        sparse_table[0][v] = u;
        pDFS(v, u);
      }
    }
  }
  int getLCA(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    int k = depth[v] - depth[u];
    for (int i = 0; i < max_log; i++)
      if ((k >> i) & 1) v = sparse_table[i][v];
    if (u == v) return u;
    for (int i = max_log - 1; i >= 0; --i)
      if (sparse_table[i][v] != sparse_table[i][u]) {
        u = sparse_table[i][u];
        v = sparse_table[i][v];
      }
    return sparse_table[0][u];
  }
  Long getDist(int u, int v) {
    return dist[u] + dist[v] - 2 * dist[getLCA(u, v)];
  }
};

struct CentroidDecomposition {
  Tree tree;
  int n;
  vector<int> sz, lvl, par;
  vector<bool> vis;
  CentroidDecomposition(const Tree& tree) : tree(tree) {
    n = tree.size();
    sz = par = lvl = vector<int>(n);
    vis = vector<bool>(n);
    this->tree.pDFS(1, -1);
    ConstructTree(1, -1);
  }

  int getSz(int u, int p) {
    sz[u] = 1;
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v]) sz[u] += getSz(v, u);
    }
    return sz[u];
  }

  int getCentroid(int u, int p, int max_size) {
    for (auto& edge : tree.adj[u]) {
      int v = edge.to;
      if (v != p && !vis[v] && sz[v] > max_size)
        return getCentroid(v, u, max_size);
    }
    return u;
  }

  void ConstructTree(int u, int p) {
    int subtree_size = getSz(u, u);
    int centroid = getCentroid(u, u, subtree_size / 2);
    vis[centroid] = 1;
    if (p == -1)
      p = centroid;
    else
      lvl[centroid] = lvl[p] + 1;
    par[centroid] = (p == centroid ? -1 : p);
    for (auto edge : tree.adj[centroid]) {
      int v = edge.to;
      if (!vis[v]) ConstructTree(v, centroid);
    }
  }

  void update(int u) {
    int x = u;
    while (~x) {
      // Update ancestor
      x = par[x];
    }
  }
  int query(int u) {
    int x = u;
    int ret = 0;
    while (~x) {
      // Query ancestor
      x = par[x];
    }
    return ret;
  }
};

// ===============================================================================

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
