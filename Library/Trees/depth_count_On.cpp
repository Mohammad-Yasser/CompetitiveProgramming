deque<int> dfs(int node, int parent) {
  vector<deque<int>> children_cnt;
  children_cnt.reserve(sz(adj[node]) - (parent != -1));
  int big_child = -1;
  for (int v : adj[node]) {
    if (parent == v) continue;
    children_cnt.emplace_back(dfs(v, node));
    if (big_child == -1 ||
        sz(children_cnt.back()) > sz(children_cnt[big_child])) {
      big_child = sz(children_cnt) - 1;
    }
  }
  if (big_child == -1) {
    children_cnt.emplace_back(deque<int>());
    big_child = 0;
  }
  auto& curr_cnt = children_cnt[big_child];
  curr_cnt.emplace_front(1);
  if (sz(curr_cnt) > k) {
    res += curr_cnt[k];
  }
  for (int i = 0; i < sz(children_cnt); ++i) {
    if (i == big_child) continue;

    for (int j = 0; j < sz(children_cnt[i]); ++j) {
      curr_cnt[j + 1] += children_cnt[i][j];
    }
  }
  return move(children_cnt[big_child]);
}