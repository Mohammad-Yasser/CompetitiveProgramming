
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
 * @brief strongly connected components decomposition, Kosaraju's algorithm
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

auto node_ind = [](int x, int n) {
  assert(x != 0 and abs(x) <= n);
  return ((abs(x) - 1) << 1) | (x > 0);
};
auto opposite = [](int x) { return x ^ 1; };

vector<bool> twosat(int n, const vector<pair<int, int>>& cnf,
                    bool convert_to_node_ids = false) {
  // make digraph
  vector<vector<int>> g(2 * n);

  for (auto it : cnf) {
    int x, y;
    tie(x, y) = it;  // x or y
    if (convert_to_node_ids) {
      g[node_ind(-x, n)].push_back(node_ind(y, n));  // not x implies y
      g[node_ind(-y, n)].push_back(node_ind(x, n));  // not y implies x
    } else {
      g[opposite(x)].emplace_back(y);  // not x implies y
      g[opposite(y)].emplace_back(x);  // not y implies x
    }
  }
  // do SCC
  vector<int> component = decompose_to_strongly_connected_components(g).second;
  vector<bool> valuation(n);
  for (int x = 1; x <= n; ++x) {
    if (component[node_ind(x, n)] ==
        component[node_ind(-x, n)]) {  // x iff not x
      return vector<bool>();           // unsat
    }
    valuation[x - 1] =
        component[node_ind(x, n)] >
        component[node_ind(-x, n)];  // use components which indices are large
  }
  return valuation;
}

// https://codeforces.com/contest/568/submission/68095925
