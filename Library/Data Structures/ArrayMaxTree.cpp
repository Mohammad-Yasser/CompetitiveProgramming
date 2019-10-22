// https://codeforces.com/group/viIfsUpAco/contest/101801/submission/56179249

#ifndef Local
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma comment(linker, "/STACK:1024000000,1024000000")
#endif

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define popCnt(x) (__builtin_popcountll(x))
typedef long long Long;

const int N = 1e5 + 10;
const int B = 20;

vector<int> available_nodes;

struct Node {
  int cnt = 0;
  int children[2] = { -1, -1 };
  inline int getChild(int child, bool create = true) {
    int& res = children[child];
    if (res == -1 && create) {
      assert(!available_nodes.empty());
      res = available_nodes.back();
      available_nodes.pop_back();
    }
    return res;
  }
};

bool getBit(int x, int b) {
  return (x >> b) & 1;
}

Node nodes[N * B];

void add(int node, int x) {
  ++nodes[node].cnt;
  for (int i = B - 1; i >= 0; --i) {
    node = nodes[node].getChild(getBit(x, i));
    ++nodes[node].cnt;
  }
}

void free(int node_id) {
  for (int& child : nodes[node_id].children) {
    if (child != -1) {
      free(child);
    }
    child = -1;
  }
  nodes[node_id].cnt = 0;
  available_nodes.push_back(node_id);
}

int arr[N];

int first_larger[N][2];

int n;

void buildFirstLarger() {
  arr[0] = arr[n + 1] = 1e6 + 5;
  first_larger[0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    int& curr = first_larger[i][0];
    curr = i - 1;
    while (arr[curr] < arr[i]) {
      curr = first_larger[curr][0];
    }
  }

  first_larger[n + 1][1] = n + 1;
  for (int i = n; i >= 1; --i) {
    int& curr = first_larger[i][1];
    curr = i + 1;
    while (arr[curr] <= arr[i]) {
      curr = first_larger[curr][1];
    }
  }
}

vector<int> children[N]; // MaxTree children (binary tree).

int getParent(int ind) {
  int left = first_larger[ind][0];
  int right = first_larger[ind][1];
  if (arr[left] < arr[right]) return left;
  return right;
}

void init() {
  for (auto& node : nodes) {
    node.children[0] = node.children[1] = -1;
    node.cnt = 0;
  }
  available_nodes.clear();
  for (int i = N; i < N * B; ++i) {
    available_nodes.push_back(i);
  }
  fill(children, children + N, vector<int>());
}

Long solve(int ind) {
  Long res = 0;
  int l = first_larger[ind][0];
  int r = first_larger[ind][1];

  int big_child = -1;
  for (int child : children[ind]) {
    res += getNumberOfMatches(child, arr[ind], arr[ind]);
    if (big_child == -1 || nodes[child].cnt > nodes[big_child].cnt) {
      big_child = child;
    }
  }


  if (big_child != -1) {
    nodes[ind] = nodes[big_child];
    if (big_child > ind) {
// solve and add small child
    } else {
// solve and add small child
    }
  }

// add myself
  add(ind, arr[ind]);


// attach myself to my parent
  children[getParent(ind)].push_back(ind);

  return res * arr[ind];
}

Long solve() {
  buildFirstLarger();
  vector<pair<int, int>> v;
  for (int i = 1; i <= n; ++i) {
    v.emplace_back(arr[i], -i);
  }
  sort(v.begin(), v.end());
  Long res = 0;
  for (auto& x : v) {
    res += solve(-x.second);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cerr.tie(0);
#ifdef Local
  freopen("test.in", "r", stdin);
#else
#define endl '\n'
#endif

  int t;
  cin >> t;

  while (t--) {
    init();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> arr[i];
    }
    cout << solve() << endl;
  }

}
