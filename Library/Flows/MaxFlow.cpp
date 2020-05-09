const int N = 201;

struct MaxFlowSolver {
  typedef int ct;

  static const ct OO = 1e8;
  static const int kNodes = N + 2;
  static const int kEdges = 4 * kNodes * kNodes;
  static const int INF = 1e9;
  static const int kSource = kNodes - 1, kSink = kNodes - 2;

  struct Edge {
    int nxt;
    int from;
    int to;
    int cap;

    int id;
  } edges[kEdges];

  int head[kNodes];
  int headcpy[kNodes];
  int cnt_edges;

  int Q[kNodes], vis[kNodes], ID = 1;

  void Init() {
    memset(head, -1, sizeof head);
    memset(Q, 0, sizeof Q);
    memset(vis, 0, sizeof vis);
    cnt_edges = 0;
  }

  void AddEdge(int u, int v, int c, int id) {
    Edge edge = {head[u], u, v, c, id};
    head[u] = cnt_edges;
    edges[cnt_edges] = edge;
    ++cnt_edges;
  }

  void AddAugEdge(int u, int v, int c, int id) {
    AddEdge(u, v, c, 0);
    AddEdge(v, u, 0, id);
  }

  int rank[kNodes];
  ct ddfs(int cur = kSource, ct minic = OO) {
    if (cur == kSink) return minic;

    for (int& i = headcpy[cur]; i != -1; i = edges[i].nxt) {
      Edge& edge = edges[i];
      int to = edge.to;

      if (edge.cap == 0 || rank[to] != rank[cur] + 1) continue;

      ct ret = ddfs(to, min(minic, edge.cap));
      edge.cap -= ret;
      edges[i ^ 1].cap += ret;

      if (ret != 0) return ret;
    }
    return 0;
  }

  bool dbfs() {
    ID++;
    int Qi = 0;
    Q[Qi++] = kSource;
    vis[kSource] = ID;
    rank[kSource] = 0;

    for (int in = 0; in < Qi; in++) {
      int cur = Q[in];
      int r = rank[cur];
      for (int i = head[cur]; i != -1; i = edges[i].nxt) {
        Edge& edge = edges[i];
        int to = edge.to;

        if (edge.cap == 0 || vis[to] == ID) continue;

        vis[to] = ID;
        rank[to] = r + 1;
        if (to == kSink) return 1;
        Q[Qi++] = to;
      }
    }
    return 0;
  }

  ct Dinic() {
    ct ret = 0;
    while (dbfs()) {
      ct f;
      memcpy(headcpy, head, sizeof head);
      while (f = ddfs(), f) ret += f;
    }
    return ret;
  }
};

const int MaxFlowSolver::kNodes;
const int MaxFlowSolver::kEdges;
const int MaxFlowSolver::INF;
const int MaxFlowSolver::kSink;
const int MaxFlowSolver::kSource;
const MaxFlowSolver::ct MaxFlowSolver::OO;

MaxFlowSolver solver;
