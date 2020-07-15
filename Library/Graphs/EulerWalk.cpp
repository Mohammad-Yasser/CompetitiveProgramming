// From kactl with minor changes.
/**
 * Author: Simon Lindholm
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 * Input should be a vector of (dest, global edge index), where
 * for undirected graphs, forward/backward edges have the same index.
 * Returns a list of pairs of the nodes in the Eulerian path/cycle with src at
 * both start and end, and the edge indices, or empty list if no cycle/path
 * exists. Time: O(V + E) Status: stress-tested
 */

vector<pii> eulerWalk(const vector<vector<pii>>& gr, int nedges, int src) {
  int n = sz(gr);

  vi D(n), its(n), eu(nedges);
  vector<pii> s = {make_pair(src, -1)};
  vector<pii> ret;
  D[src]++;  // to allow Euler paths, not just cycles
  while (!s.empty()) {
    auto x = s.back();
    int y, e, &it = its[x.first], end = sz(gr[x.first]);
    if (it == end) {
      ret.emplace_back(x);
      s.pop_back();
      continue;
    }
    tie(y, e) = gr[x.first][it++];
    if (!eu[e]) {
      D[x.first]--, D[y]++;
      eu[e] = 1;
      s.emplace_back(y, e);
    }
  }
  for (int x : D)
    if (x < 0) return {};
  if (sz(ret) != nedges + 1) return {};
  reverse(all(ret));
  return ret;
}

vector<pii> eulerPath(const vector<vector<pii>>& gr, int nedges, int src = -1) {
  if (src == -1) {
    src = find_if(all(gr), [](const vi& v) { return sz(v) & 1; }) - begin(gr);
    if (src == n) {
      src =
          find_if(all(gr), [](const vi& v) { return !v.empty(); }) - begin(gr);
    }
    if (src == n) return {};
  }
  return eulerWalk(gr, nedges, src);
}

vector<pii> eulerCycle(const vector<vector<pii>>& gr, int nedges,
                       int src = -1) {
  if (src == -1) {
    src = find_if(all(gr), [](const vi& v) { return !v.empty(); }) - begin(gr);
    if (src == n) return {};
  }
  auto res = eulerWalk(gr, nedges, src);
  if (res.back().first != src) return {};
  return res;
}