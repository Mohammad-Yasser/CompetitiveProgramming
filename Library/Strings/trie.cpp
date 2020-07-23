
const int TrieSize = 37777777;
struct Node {
  static int getNewNode() {
    static int nextNodeId = 1;
    assert(nextNodeId + 1 < TrieSize);
    return nextNodeId++;
  }
  static const int DummyNode = 0;
  int cnt = 0;
  int children[2] = {DummyNode, DummyNode};
  int getChild(int ind, bool create_if_not_exist = true) {
    if (children[ind] == DummyNode) {
      if (create_if_not_exist) return children[ind] = getNewNode();
      return DummyNode;
    }
    return children[ind];
  }
} nodes[TrieSize];

struct Trie {
  int root_id = Node::getNewNode();

  void add(uint64_t x, int val) {
    int curr = root_id;
    ++nodes[curr].cnt;
    for (int i = 0; i < B; ++i) {
      curr = nodes[curr].getChild((x >> i) & 1);
      ++nodes[curr].cnt;
    }
    nodes[curr].cnt = val;
  }

} tries[2];