#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct disjointSet {
	vector<int> par, size, rank;
	int numSet;
	disjointSet(int n) {
		par.resize(n), size.resize(n), rank.resize(n);
		for (int i = 0; i < n; ++i)
			par[i] = i, size[i] = 1;
		numSet = n;
	}
//Find 1
	int find(int node) {
		return par[node] = (par[node] == node) ? node : find(par[node]);
	}
//Find 2
	int operator[](int node) {
		return par[node] = (par[node] == node) ? node : (*this)
		                                         [par[node]];
	}
// Join 1
	bool join(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y)
		  return false;
		if (rank[x] < rank[y])
		  swap(x, y);
		if (rank[x] == rank[y])
		  rank[x]++;
		size[x] += size[y];
		numSet--;
		par[y] = x;
		return true;
	}
	// Join 2
	bool operator()(int x, int y) {
		x = (*this)[x];
		y = (*this)[y];
		if (x == y)
		  return false;
		if (rank[x] < rank[y])
		  swap(x, y);
		if (rank[x] == rank[y])
		  rank[x]++;
		size[x] += size[y];
		numSet--;
		par[y] = x;
		return true;
	}
};

struct Edge {
	int f, t;
	int c;
	bool operator<(const Edge& e) const {
		return c < e.c;
	}
};
int edgeCnt, nodeCnt;
const int SZ = 20004;
Edge edges[SZ];
int kruskal(vector<Edge>& res) {
	res.clear();
	int ret = 0;
	disjointSet ds(nodeCnt);
	sort(edges, edges + edgeCnt);
	for (int i = 0; i < edgeCnt; ++i) {
		if (ds(edges[i].f, edges[i].t)) {
			ret += edges[i].c;
			res.push_back(edges[i]);
		}
	}
	return ret;
}
unordered_set<int> adj[SZ];

void addEdge(int u, int v, int c) {
	--u, --v;
	edges[edgeCnt++] = {u,v,c};
	edges[edgeCnt++] = {v,u,c};
	adj[u].insert(v);
	adj[v].insert(u);
}

int grid[101][101];
int h, w;
const int dx[8] = { 1, 1, 1, 0, 0, -1, -1, -1 }, dy[8] = { 1, 0, -1, 1, -1, 1, 0, -1 };

void dfs(int i, int j, int val) {
	if (i < 0 or j < 0 or i == h or j == w or grid[i][j]) return;
	grid[i][j] = val;
	for (int k = 0; k < 8; ++k)
		dfs(i + dx[k], j + dy[k], val);
}

void buildEdges() {
	for (int i = 1; i < h or max(i, h) == 1; ++i) {
		int currNode = -1, lastOcc;
		for (int j = 0; j < w; ++j) {
			int tmpNode = max(grid[i][j], grid[i - 1][j]);
			if (tmpNode != -1 && currNode != tmpNode && currNode != -1)
			  addEdge(currNode, tmpNode, j - lastOcc - 1);

			if (tmpNode != -1) currNode = tmpNode, lastOcc = j;
		}
	}

	for (int i = 1; i < w or max(i, w) == 1; ++i) {
		int currNode = -1, lastOcc;
		for (int j = 0; j < h; ++j) {
			int tmpNode = max(grid[j][i], grid[j][i - 1]);
			if (tmpNode != -1 && currNode != tmpNode && currNode != -1)
			  addEdge(currNode, tmpNode, j - lastOcc - 1);

			if (tmpNode != -1) currNode = tmpNode, lastOcc = j;
		}
	}

}

bool vis[SZ];

void dfs(int node) {
	vis[node] = 1;
	for (auto x : adj[node])
		if (!vis[x]) dfs(x);
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);

#endif

	int cs = 0;

	while (cin >> h >> w, h && w) {
		assert(max(h, w) <= 100);
		nodeCnt = edgeCnt = 0;
		fill(adj, adj + SZ, unordered_set<int>());
		memset(vis, 0, sizeof vis);
		memset(grid, -1, sizeof grid);
		for (int i = 0; i < h; ++i)
			for (int j = 0; j < w; ++j) {
				char c;
				cin >> c;
				grid[i][j] = (c == '#') - 1;
			}

		for (int i = 0; i < h; ++i)
			for (int j = 0; j < w; ++j) {
				nodeCnt += !grid[i][j];
				dfs(i, j, nodeCnt);
			}

		buildEdges();
		vector<Edge> res;
		if (cs) cout << '\n';
		int sum = kruskal(res);

		int cnt = 0;
		for (int i = 0; i < nodeCnt; ++i)
			if (!vis[i]) ++cnt, dfs(i);
		cout << "City " << ++cs << '\n';

		if (res.size() == 0) {
			if (cnt <= 1)
				cout << "No bridges are needed.\n";
			else
				cout << "No bridges are possible.\n";
		}

		else if (res.size() == 1)
			cout << "1 bridge of total length " << sum << '\n';

		else
			cout << res.size() << " bridges of total length " << sum << '\n';

		if (cnt > 1)
		  cout << cnt << " disconnected groups\n";

	}
	return 0;
}
