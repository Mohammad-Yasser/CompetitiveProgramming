// https://github.com/kmyk/competitive-programming-library
/**
 * @param g is an adjacent list of a digraph
 * @note $O(V + E)$
 * @see https://en.wikipedia.org/wiki/Transpose_graph
 */
vector<vector<int>> make_transpose_graph(const vector<vector<int>>& g) {
  int n = g.size();
  vector<vector<int>> h(n);
  for (int i = 0; i < n; ++i) {
    for (int j : g[i]) {
      h[j].push_back(i);
    }
  }
  return h;
}

/**
 * @brief strongly connected components decomposition, Kosaraju's algorithm /
 * 強連結成分分解
 * @return the pair (the number k of components, the function from vertices of g
 * to components). The SCCs are sorted topologically.
 * @param g is an adjacent list of a digraph
 * @param g_rev is the transpose graph of g
 * @note $O(V + E)$
 */
pair<int, vector<int>> decompose_to_strongly_connected_components(
    const vector<vector<int>>& g, const vector<vector<int>>& g_rev) {
  int n = g.size();
  vector<int> acc(n);
  {
    vector<bool> used(n);
    function<void(int)> dfs = [&](int i) {
      used[i] = true;
      for (int j : g[i])
        if (not used[j]) dfs(j);
      acc.push_back(i);
    };
    for (int i = 0; i < n; ++i)
      if (not used[i]) dfs(i);
    reverse(all(acc));
  }
  int size = 0;
  vector<int> component_of(n);
  {
    vector<bool> used(n);
    function<void(int)> rdfs = [&](int i) {
      used[i] = true;
      component_of[i] = size;
      for (int j : g_rev[i])
        if (not used[j]) rdfs(j);
    };
    for (int i : acc)
      if (not used[i]) {
        rdfs(i);
        ++size;
      }
  }
  return {size, move(component_of)};
}

pair<int, vector<int>> decompose_to_strongly_connected_components(
    const vector<vector<int>>& g) {
  return decompose_to_strongly_connected_components(g, make_transpose_graph(g));
}

void buildSCCDAG(const vector<vector<int>>& graph, const vector<int>& scc_id) {
  int n = sz(graph);
  scc_dag.resize(n);

  for (int i = 0; i < n; ++i) {
    for (int v : graph[i]) {
      if (scc_id[i] != scc_id[v]) {
        scc_dag[scc_id[i]].emplace_back(scc_id[v]);
      }
    }
  }
}
