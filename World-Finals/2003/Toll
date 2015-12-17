#include <bits/stdc++.h> 
using namespace std;
typedef long long ll;

const int N = 128;

vector<char> adj[N];

int p;
char start, ed;

bool vis[N];

int cost(char c, int p) {
	if (islower(c)) return p + 1;

	int x = p;
	while (x - (x + 19) / 20 != p)
		  x += p - x + (x + 19) / 20;
	return x;
}

int dijkstra() {
	priority_queue<pair<int, char>, vector<pair<int, char> >, greater<pair<int, char> > > pq;
	pq.push( { p, ed });
	memset(vis, 0, sizeof vis);

	while (1) {
		auto curr = pq.top();
		pq.pop();
		if (curr.second == start) return curr.first;
		vis[curr.second] = 1;

		for (char c : adj[curr.second])
			if (!vis[c])
			  pq.push( { cost(curr.second, curr.first), c });
	}

}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

#endif

	int n, cs = 0;
	while (cin >> n, n != -1) {
		fill(adj, adj + N, vector<char>());
		while (n--) {
			char u, v;
			cin >> u >> v;
			adj[u].push_back(v), adj[v].push_back(u);
		}

		cin >> p >> start >> ed;

		cout << "Case " << ++cs << ": " << dijkstra() << '\n';

	}
}
