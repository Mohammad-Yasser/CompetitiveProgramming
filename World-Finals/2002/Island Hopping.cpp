#include <bits/stdc++.h> 
using namespace std;
typedef long long ll;

struct Island {
	int x, y, pop;
} island[51];

struct Edge {
	int from, to;
	double dist;
	bool operator <(const Edge & other) const {
		return dist < other.dist;
	}
};

double calc(int i, int j) {
	return sqrt(1LL * (island[i].x - island[j].x) * (island[i].x - island[j].x)
	  + 1LL * (island[i].y - island[j].y) * (island[i].y - island[j].y));
}

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

int n;
vector<int> adj[51];
void kruskal() {
	vector<Edge> all;
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			all.push_back( { i, j, calc(i, j) });

	sort(all.begin(), all.end());

	disjointSet ds(51);

	for (auto &x : all)
		if (ds(x.from, x.to))
		  adj[x.from].push_back(x.to), adj[x.to].push_back(x.from);

}

int parent[51];

void assignParent(int node, int p) {
//	cout << node << ' ' << p << endl;
	for (int &x : adj[node])
		if (x != p) parent[x] = node, assignParent(x, node);
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif

	int cs = 0;
	while (cin >> n, n) {
		fill(adj, adj + 51, vector<int>());
		ll tot = 0;
		for (int i = 0; i < n; ++i)
			cin >> island[i].x >> island[i].y >> island[i].pop, tot += island[i].pop;
		double ans = 0;
		kruskal();
		assignParent(0, -1);
		for (int i = 1; i < n; ++i) {
			double mx = 0;
			int p = i;
			while (p)
				mx = max(mx, calc(p, parent[p])), p = parent[p];
			ans += mx * island[i].pop;
		}
		cout << "Island Group: " << ++cs << " Average " << fixed << setprecision(2)
		  << ans / tot
		  << "\n\n";
	}

}
