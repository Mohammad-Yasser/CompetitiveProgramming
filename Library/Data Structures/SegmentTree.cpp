
// Modular Segment Tree: https://codeforces.com/blog/entry/20528
template <typename T, typename U>
struct SegmentTree {
  int S, H;

  T zero;
  vector<T> value;

  U noop;
  vector<bool> dirty;
  vector<U> prop;

  void init(int _S = N, T _zero = T(), U _noop = U()) {
    zero = _zero, noop = _noop;
    for (S = 1, H = 1; S < _S;) S *= 2, H++;
    value.clear(), dirty.clear(), prop.clear();
    value.resize(2 * S, zero);
    dirty.resize(2 * S, false);
    prop.resize(2 * S, noop);
  }

  SegmentTree<T, U>(int _S = N, T _zero = T(), U _noop = U()) {
    init(_S, _zero, _noop);
  }

  void set_leaves(vector<T>& leaves) {
    copy(leaves.begin(), leaves.end(), value.begin() + S);

    for (int i = S - 1; i > 0; i--) value[i] = value[2 * i] + value[2 * i + 1];
  }

  void apply(int i, const U& update) {
    value[i] = update(value[i]);
    if (i < S) {
      prop[i] = prop[i] + update;
      dirty[i] = true;
    }
  }

  void rebuild(int i) {
    for (int l = i / 2; l; l /= 2) {
      T combined = value[2 * l] + value[2 * l + 1];
      value[l] = prop[l](combined);
    }
  }

  void propagate(int i) {
    for (int h = H; h > 0; h--) {
      int l = i >> h;

      if (dirty[l]) {
        apply(2 * l, prop[l]);
        apply(2 * l + 1, prop[l]);

        prop[l] = noop;
        dirty[l] = false;
      }
    }
  }

  void upd(int i, int j, const U& update) {
    i += S, j += S;
    propagate(i), propagate(j);

    for (int l = i, r = j; l <= r; l /= 2, r /= 2) {
      if ((l & 1) == 1) apply(l++, update);
      if ((r & 1) == 0) apply(r--, update);
    }

    rebuild(i), rebuild(j);
  }

  T query(int i, int j) {
    i += S, j += S;
    propagate(i), propagate(j);

    T res_left = zero, res_right = zero;
    for (; i <= j; i /= 2, j /= 2) {
      if ((i & 1) == 1) res_left = res_left + value[i++];
      if ((j & 1) == 0) res_right = value[j--] + res_right;
    }
    return res_left + res_right;
  }
};

struct Node {
  Node operator+(const Node& right) const {
    Node res = right;
    return res;
  }
};

// The default value must not change an update when merged.
// I.e. any_update + Update() must be = any_update.
struct Update {
  Update() {}
  Update operator+(const Update& right) const {
    Update res = right;
    return res;
  }
  Node operator()(const Node& node) const {
    Node res = node;
    return res;
  }
};

// =============================================
struct Node {
  int start, end;  // The node covers the range [start,end].

  int sum = 0;

  static Node merge(const Node& a, const Node& b) {
    Node res;
    res.start = a.start;
    res.end = b.end;

    res.sum = (a.sum + b.sum) % MOD;

    return res;
  }

  bool inRange(int x) const { return start <= x && x <= end; }

  void print() const {}
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

  void build(const string& s) { build(1, 0, s.size() - 1, s); }

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
  int start, end;  // The node covers the range [start,end].

  Long min_cost = 0;
  Long lazy = 0;

  static Node merge(const Node& a, const Node& b) {
    Node res;
    res.start = a.start;
    res.end = b.end;

    res.min_cost = min(a.min_cost + a.lazy, b.min_cost + b.lazy);

    return res;
  }

  bool inRange(int x) const { return start <= x && x <= end; }

  void print() const {
    cout << start << " " << end << " " << min_cost << " " << lazy << endl;
  }
};

struct SegmentTree {
  static const int kSize = 1 << int(log2(N) + 2);

  array<Node, kSize> nodes;

  void build(int node_id, int left, int right, const vector<Long>& costs) {
    Node& node = nodes[node_id];
    node.lazy = 0;
    node.start = left, node.end = right;
    if (left == right) {
      node.min_cost = costs[left];
      return;
    }

    int mid = (left + right) / 2;
    build(node_id * 2, left, mid, costs);
    build(node_id * 2 + 1, mid + 1, right, costs);
    node = Node::merge(nodes[node_id * 2], nodes[node_id * 2 + 1]);
  }

  void build(const vector<Long>& costs) {
    build(1, 0, costs.size() - 1, costs);
  }

  void push(int node_id) {
    auto& node = nodes[node_id];
    node.min_cost += node.lazy;
    if (node.start != node.end) {
      nodes[node_id * 2].lazy += node.lazy;
      nodes[node_id * 2 + 1].lazy += node.lazy;
    }
    node.lazy = 0;
  }

  void update(int node_id, int l, int r, Long val) {
    if (r < l) return;
    push(node_id);
    auto& node = nodes[node_id];
    if (node.start > r || node.end < l) return;
    if (l <= node.start && node.end <= r) {
      node.lazy += val;
      push(node_id);
      return;
    }
    update(node_id * 2, l, r, val);
    update(node_id * 2 + 1, l, r, val);
    node = Node::merge(nodes[node_id * 2], nodes[node_id * 2 + 1]);
  }

  Long query() { return nodes[1].min_cost + nodes[1].lazy; }

} seg_tree;
// ====================================================================
