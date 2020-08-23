
struct Edge {
  int to, weight;
  Edge(int to = 0, int weight = 0) : to(to), weight(weight) {}
};

struct Tree {
  vector<vector<Edge>> adj;
  int max_log;
  vector<Long> dist;
  vector<int> depth, subtree_size;
  vector<int> time_in;
  vector<int> enter_index;  // First index of the node in the euler tour.;
  vector<int> euler_tour;
  vector<int> time_to_node;  // time_to_node[i] is u s.t. time_in[u] == i.
  SparseTable<int> sparse_table;

  Tree(int n)
      : adj(n + 1),
        dist(n + 1),
        depth(n + 1),
        subtree_size(n + 1),
        time_in(n + 1),
        time_to_node(n + 1),
        enter_index(n + 1) {}
  void build() {
    pDFS(1);
    sparse_table.init(euler_tour, [&](int u, int v) {
      return (time_in[u] < time_in[v]) ? u : v;
    });
  }
  void addEdge(int u, int v, int w = 1) {
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  int size() const { return sz(adj); }
  void pDFS(int u, int p = -1, int timer = 0) {
    time_in[u] = timer++;
    time_to_node[time_in[u]] = u;
    subtree_size[u] = 1;
    enter_index[u] = sz(euler_tour);
    euler_tour.emplace_back(u);

    for (auto& edge : adj[u]) {
      int v = edge.to;
      if (v != p) {
        dist[v] = dist[u] + edge.weight;
        depth[v] = depth[u] + 1;
        pDFS(v, u, timer);
        euler_tour.emplace_back(u);
        subtree_size[u] += subtree_size[v];
      }
    }
  }
  int getLCA(int u, int v) {
    int l = enter_index[u];
    int r = enter_index[v];
    if (l > r) swap(l, r);
    return sparse_table.query(l, r);
  }
  Long getDist(int u, int v) {
    return dist[u] + dist[v] - 2 * dist[getLCA(u, v)];
  }
};
