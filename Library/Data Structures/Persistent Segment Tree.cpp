constexpr int N = 1e5 + 5;

const int kCntNodes = 2 * N * (int) ceil(log2(N) + 2)
  + (1 << ((int) (ceil(log2(N)) + 2)));

struct Node {
  int left_child;
  int right_child;

  int range_begin;
  int range_end; // inclusive

  int cnt_first_occ = 0;

  static int cnt_nodes;

  static int GetNewNode() {
    return ++cnt_nodes;
  }

} nodes[kCntNodes];

int Node::cnt_nodes = 0;

struct PersistentSegmentTree {
  int head;

  PersistentSegmentTree() {
    head = Node::GetNewNode();
  }

  void BuildTree() {
    BuildTree(head, 0, N - 1);
  }

  void BuildTree(int node_id, int left, int right) {
    Node& node = nodes[node_id];
    node.range_begin = left;
    node.range_end = right;

    if (left == right) return;

    node.left_child = Node::GetNewNode();
    node.right_child = Node::GetNewNode();

    int mid = (left + right) / 2;
    BuildTree(node.left_child, left, mid);
    BuildTree(node.right_child, mid + 1, right);
  }

  static void UpdateFromAnotherTree(int other_node_id, int self_node_id,
    int ind, int val) {
    Node& other_node = nodes[other_node_id];
    Node& self_node = nodes[self_node_id];

    self_node = other_node;

    if (self_node.range_begin == self_node.range_end) {
      self_node.cnt_first_occ += val;
      return;
    }

    if (ind <= nodes[self_node.left_child].range_end) {
      self_node.left_child = Node::GetNewNode();

      UpdateFromAnotherTree(other_node.left_child, self_node.left_child, ind,
        val);
    } else {
      self_node.right_child = Node::GetNewNode();

      UpdateFromAnotherTree(other_node.right_child, self_node.right_child, ind,
        val);
    }

    self_node.cnt_first_occ = nodes[self_node.left_child].cnt_first_occ
      + nodes[self_node.right_child].cnt_first_occ;
  }

  static int Query(int curr_node_id, int k) {
    Node& node = nodes[curr_node_id];
    if (node.range_begin == node.range_end) {
      return node.range_begin;
    }
    if (nodes[node.left_child].cnt_first_occ >= k) {
      return Query(node.left_child, k);
    }
    return Query(node.right_child, k - nodes[node.left_child].cnt_first_occ);
  }

  static int GetValue(int curr_node_id, int ind) {
    Node& node = nodes[curr_node_id];
    if (node.range_begin == node.range_end) {
      return node.cnt_first_occ;
    }
    if (ind <= nodes[node.left_child].range_end) {
      return GetValue(node.left_child, ind);
    }
    return GetValue(node.right_child, ind);
  }

} trees[N];
