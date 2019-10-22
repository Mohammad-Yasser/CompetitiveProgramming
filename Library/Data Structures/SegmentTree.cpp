// =============================================
struct Node {
  int start, end; // The node covers the range [start,end].

  int sum = 0;

  static Node merge(const Node& a, const Node& b) {
    Node res;
    res.start = a.start;
    res.end = b.end;

    res.sum = (a.sum + b.sum) % MOD;

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

  array<Node, kSize> nodes;

  void build(int node_id, int left, int right, const string& s) {
    Node& node = nodes[node_id];
    node.start = left, node.end = right;
    if (left == right) {
      node.sum = getHash(s[left], left);
      return;
    }

    int mid = (left + right) / 2;
    build(node_id * 2, left, mid, s);
    build(node_id * 2 + 1, mid + 1, right, s);
    node = Node::merge(nodes[node_id * 2], nodes[node_id * 2 + 1]);
  }

  void build(const string& s) {
    build(1, 0, s.size() - 1, s);
  }

  void update(int node_id, int ind, char val) {
    auto& node = nodes[node_id];
    if (!node.inRange(ind)) return;
    if (node.start == node.end) {
      node.sum = getHash(val, ind);
      return;
    }
    update(node_id * 2, ind, val);
    update(node_id * 2 + 1, ind, val);
    node = Node::merge(nodes[node_id * 2], nodes[node_id * 2 + 1]);
  }

  int query(int node_id, int l, int r) {
    auto& node = nodes[node_id];
    if (l <= node.start && node.end <= r) {
      return node.sum;
    }
    if (node.end < l || node.start > r) {
      return 0;
    }

    int res = query(node_id * 2, l, r);
    res = (res + query(node_id * 2 + 1, l, r)) % MOD;

    return res;
  }

  int query(int l, int r) {
    int res = query(1, l, r);
    res = 1LL * res * modInv(power(base, l)) % MOD;
    return res;
  }
};
// =============================================

struct Node {
  int start, end; // The node covers the range [start,end].

  int max_suffix_sum = 0;
  int lazy = 0;

  static Node merge(const Node& a, const Node& b) {
    Node res;
    res.start = a.start;
    res.end = b.end;

    res.max_suffix_sum = max(a.max_suffix_sum, b.max_suffix_sum);

    return res;
  }

  bool inRange(int x) const {
    return start <= x && x <= end;
  }

  void print() const {
    cout << start << " " << end << " " << max_suffix_sum << " " << lazy << endl;
  }
};

struct SegmentTree {
  static const int kSize = 1 << int(log2(N) + 2);

  array<Node, kSize> nodes;

  void build(int node_id, int left, int right) {
    Node& node = nodes[node_id];
    node.start = left, node.end = right;
    if (left == right) return;

    int mid = (left + right) / 2;
    build(node_id * 2, left, mid);
    build(node_id * 2 + 1, mid + 1, right);
    node = Node::merge(nodes[node_id * 2], nodes[node_id * 2 + 1]);
  }

  void build() {
    build(1, 0, N - 1);
  }

  void push(int node_id) {
    auto& node = nodes[node_id];
    node.max_suffix_sum += node.lazy;
    if (node.start != node.end) {
      nodes[node_id * 2].lazy += node.lazy;
      nodes[node_id * 2 + 1].lazy += node.lazy;
    }
    node.lazy = 0;
  }

  void update(int node_id, int r, int val) {
    push(node_id);
    auto& node = nodes[node_id];
    if (node.start > r) return;
    if (node.end <= r) {
      node.lazy += val;
      push(node_id);
      return;
    }
    update(node_id * 2, r, val);
    update(node_id * 2 + 1, r, val);
    node = Node::merge(nodes[node_id * 2], nodes[node_id * 2 + 1]);
  }

  int query(int node_id) {
    auto& node = nodes[node_id];
    if (node.start == node.end) return node.start;

    push(node_id * 2 + 1);
    if (nodes[node_id * 2 + 1].max_suffix_sum > 0) {
      return query(node_id * 2 + 1);
    }

    push(node_id * 2);
    if (nodes[node_id * 1].max_suffix_sum > 0) {
      return query(node_id * 2);
    }
    assert(node_id == 1);
    return -1;
  }

} seg_tree;
// ====================================================================
