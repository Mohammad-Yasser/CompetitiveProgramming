int sz[N];
pair<int, int> ids[N];
int id;

void dfs(int node, int parent, int dist) {
  ids[node].first = ++id;
  sz[node] = 1;
  for (auto& child : adj[node]) {
    if (child.first != parent) {
      dfs(child.first, node, (1LL * dist + child.second) % MOD);
      sz[node] += sz[child.first];
    }
  }
  ids[node].second = id;
}

