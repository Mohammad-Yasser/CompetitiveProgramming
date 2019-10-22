#include <bits/stdc++.h>
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;
typedef unsigned long long ULong;

constexpr int N = 2e5 + 5;
const int MOD = 30013;

struct Node {
  int start, end; // The node covers the range [start,end].

  int mx = 0;
  int no_ways = 0;

  void merge(int other_mx, int other_ways) {
    if (mx > other_mx) return;
    if (mx == other_mx) {
      no_ways = (no_ways + other_ways) % MOD;
      return;
    }
    mx = other_mx;
    no_ways = other_ways;
  }

  void merge(const Node& right) {
    end = right.end;
    merge(right.mx, right.no_ways);
  }

  static Node merge(const Node& a, const Node& b) {
    Node res = a;
    res.merge(b);
    return res;
  }

  bool inRange(int x) const {
    return start <= x && x <= end;
  }

  void print() const {

  }
};

struct SegmentTree {
  static const int kSize = 1 << int(log2(N) + 2);

  Node nodes[kSize];

  void build(int node_id, int left, int right) {
    Node& node = nodes[node_id];
    node.start = left, node.end = right;
    if (left == right) return;

    int mid = (left + right) / 2;
    build(node_id * 2, left, mid);
    build(node_id * 2 + 1, mid + 1, right);
  }

  void update(int node_id, int b, int mx, int ways) {
    auto& node = nodes[node_id];
    if (!node.inRange(b)) return;
    if (node.start == node.end) {
      node.merge(mx, ways);
      return;
    }
    update(node_id * 2, b, mx, ways);
    update(node_id * 2 + 1, b, mx, ways);
    node = Node::merge(nodes[node_id * 2], nodes[node_id * 2 + 1]);
  }

  Node query(int node_id, int r) {
    auto& node = nodes[node_id];
    if (r >= node.end) return node;

    Node a = query(node_id * 2, r);

    if (r <= a.end) return a;

    Node b = query(node_id * 2 + 1, r);

    Node res = Node::merge(a, b);
    return res;
  }

} tree;

map<int, int> comp;

struct Trapezoid {
  int a, b, c, d;
};

void buildComp() {
  int curr = 0;
  for (auto& p : comp) {
    p.second = ++curr;
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  int n;
  cin >> n;
  vector<Trapezoid> traps(n);

  for (auto& trap : traps) {
    cin >> trap.a >> trap.b >> trap.c >> trap.d;
    comp[trap.a], comp[trap.b];
  }

  buildComp();

  sort(traps.begin(), traps.end(), [](const Trapezoid& a , const Trapezoid& b) {
    return a.c < b.c;
  });

  for (auto& trap : traps) {
    trap.a = comp[trap.a], trap.b = comp[trap.b];
  }

  tree.build(1, 1, N - 1);
  set<pair<int, tuple<int, int, int>>> updates;
  for (auto& trap : traps) {
    while (!updates.empty() && updates.begin()->first < trap.c) {
      auto update = *updates.begin();
      updates.erase(updates.begin());
      tree.update(1, get<0>(update.second), get<1>(update.second),
        get<2>(update.second));
    }

    if (trap.a == 1) {
      updates.emplace(trap.d, make_tuple(trap.b, 1, 1));
    } else {
      Node query = tree.query(1, trap.a - 1);
      updates.emplace(trap.d,
        make_tuple(trap.b, query.mx + 1, max(1, query.no_ways)));
    }
  }

  while (!updates.empty()) {
    auto update = *updates.begin();
    updates.erase(updates.begin());
    tree.update(1, get<0>(update.second), get<1>(update.second),
      get<2>(update.second));
  }

  cout << tree.nodes[1].mx << " " << tree.nodes[1].no_ways << endl;

}

